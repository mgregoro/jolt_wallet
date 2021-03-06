// ----------------------------------------------------------------------------
//         ATMEL Crypto-Devices Software Support  -  Colorado Springs, CO -
// ----------------------------------------------------------------------------
// DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/** \file
 *  \brief  This file contains implementations of interface independent functions
 *          for the AES132 device.
 *  \author Atmel Crypto Products
 *  \date   June 08, 2015
 */

#include "aes132_comm.h"
#include <stdint.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "i2c_phys.h"  // todo; interoperability of the return codes

static const char TAG[] = "aes132_comm";

/** \brief This function calculates a 16-bit CRC.
 * \param[in] length number of bytes in data buffer
 * \param[in] data pointer to data
 * \param[out] crc pointer to calculated CRC (high byte at crc[0])
 */
void aes132c_calculate_crc( uint8_t length, uint8_t *data, uint8_t *crc )
{
    uint8_t counter;
    uint8_t crc_low = 0, crc_high = 0, crc_carry;
    uint8_t poly_low = 0x05, poly_high = 0x80;
    uint8_t shift_register;
    uint8_t data_bit, crc_bit;

    for( counter = 0; counter < length; counter++ ) {
        for( shift_register = 0x80; shift_register > 0x00; shift_register >>= 1 ) {
            data_bit = ( data[counter] & shift_register ) ? 1 : 0;
            crc_bit  = crc_high >> 7;

            // Shift CRC to the left by 1.
            crc_carry = crc_low >> 7;
            crc_low <<= 1;
            crc_high <<= 1;
            crc_high |= crc_carry;

            if( ( data_bit ^ crc_bit ) != 0 ) {
                crc_low ^= poly_low;
                crc_high ^= poly_high;
            }
        }
    }
    crc[0] = crc_high;
    crc[1] = crc_low;
}

/** \brief This function resets the command and response buffer address.
 * \return status of the operation
 */
uint8_t aes132c_reset_io_address( void )
{
    ESP_LOGD( TAG, "Reseting command and response buffer address." );
    return aes132p_write_memory_physical( 0, AES132_RESET_ADDR, (void *)0 );
}

/** \brief This function reads the device status register.
 * \param[out] device_status_register pointer to byte where the register value is stored
 * \return status of the operation
 */
uint8_t aes132c_read_device_status_register( uint8_t *device_status_register )
{
    uint8_t aes132_lib_return;
    uint8_t n_retries = AES132_RETRY_COUNT_ERROR;

    do {
        ESP_LOGD( TAG, "Reading Status Register" );
        aes132_lib_return = aes132p_read_memory_physical( 1, AES132_STATUS_ADDR, device_status_register );
        if( !aes132_lib_return ) { ESP_LOGD( TAG, "looping" ); }
        else {
            ESP_LOGD( TAG, "breaking out of loop" );
        }
    } while( ( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) && ( --n_retries > 0 ) );

    return aes132_lib_return;
}

/** \brief This function waits until a bit in the device status register is set or reset.
 *         Reading this register will wake up the device.
 * \param[in] mask contains bit pattern to wait for
 * \param[in] is_set specifies whether to wait until bit is set (#AES132_BIT_SET) or reset (#AES132_BIT_SET)
 * \param[in] n_retries 16-bit number that indicates the number of retries before stopping to poll.
 * \return status of the operation
 */
uint8_t aes132c_wait_for_status_register_bit( uint8_t mask, uint8_t is_set, uint16_t n_retries )
{
    uint8_t device_status_register = 0;
    ESP_LOGD( TAG,
              "aes132c_wait_for_status_register_bit; "
              "target mask %.2X",
              mask );

    do {  // debug: this is looping
        ESP_LOGD( TAG, "Reading Status Register" );
        if( AES132_FUNCTION_RETCODE_SUCCESS !=
            aes132p_read_memory_physical( 1, AES132_STATUS_ADDR, &device_status_register ) ) {
            ESP_LOGD( TAG,
                      "Device busy while trying to read Status Register. "
                      "Continue polling until n_retries (%d) is depleted.",
                      n_retries );
            continue;
        }

        if( is_set == AES132_BIT_SET ) {
            ESP_LOGD( TAG, "Wait for the mask bit(s) being set." );
            if( ( device_status_register & mask ) == mask ) {
                ESP_LOGD( TAG, "Mask pattern has been found in device "
                               "status register." );
                return AES132_FUNCTION_RETCODE_SUCCESS;
            }
        }
        else {
            ESP_LOGD( TAG, "Wait for the mask bit(s) being cleared." );
            if( ( device_status_register & mask ) == 0 ) {
                ESP_LOGD( TAG, "Mask pattern has been found in device "
                               "status register." );
                return AES132_FUNCTION_RETCODE_SUCCESS;
            }
        }
        if( n_retries == 0 ) { ESP_LOGE( TAG, "Ran out of retries waiting for statusbit" ); }
    } while( n_retries-- > 0 );
    return AES132_FUNCTION_RETCODE_TIMEOUT;
}

/** \brief This function waits for the Write-In-Progress (WIP) bit in the device status register to be cleared.
 * \return status of the operation
 */
uint8_t aes132c_wait_for_device_ready( void )
{
    uint8_t response;
    ESP_LOGD( TAG, "Waiting For Device Ready......................." );
    response = aes132c_wait_for_status_register_bit( AES132_WIP_BIT, AES132_BIT_CLEARED,
                                                     AES132_RETRY_COUNT_DEVICE_READY );
    if( response ) { ESP_LOGW( TAG, "Failed to read status register: %02X", response ); }
    else {
        ESP_LOGD( TAG, "Device is Ready................................" );
    }
    return response;
}

/** \brief This function waits for the Response-Ready (RRDY) bit in the device status register to be set.
 * \ return status of the operation
 */
uint8_t aes132c_wait_for_response_ready( void )
{
    uint8_t response;
    ESP_LOGD( TAG, "Waiting For Response Ready......................." );
    response = aes132c_wait_for_status_register_bit( AES132_RESPONSE_READY_BIT, AES132_BIT_SET,
                                                     AES132_RETRY_COUNT_RESPONSE_READY );
    ESP_LOGD( TAG, "Response is Ready................................" );
    return response;
}

/** \brief This function sends a Sleep command to the device.
 * \param[in] standby mode (0: sleep, non-zero: standby)
 * \return status of the operation
 */
uint8_t aes132c_send_sleep_command( uint8_t standby )
{
    // command buffer fields:
    // <count = 0x09><op code = 0x11><mode = 0x00 (sleep)><param1 = 0x0000><param2 = 0x0000><CRC = 0x7181>
    const uint8_t command_sleep[] = {AES132_COMMAND_SIZE_MIN, 0x11, AES132_COMMAND_MODE_SLEEP, 0, 0, 0, 0, 0x71, 0x81};
    const uint8_t command_standby[] = {
            AES132_COMMAND_SIZE_MIN, 0x11, AES132_COMMAND_MODE_STANDBY, 0, 0, 0, 0, 0xEF, 0x82};

    // Disable reading the device status register after sending the command and disable appending the CRC.
    const uint8_t options = ( AES132_OPTION_NO_APPEND_CRC | AES132_OPTION_NO_STATUS_READ );

    // We reset the IO buffer address as a precaution.
    // Since we cannot read the device status register after sending the Sleep command
    // without waking up the device again, we cannot know whether the command failed.
    uint8_t aes132_lib_return = aes132c_reset_io_address();
    if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) return aes132_lib_return;

    if( standby == AES132_COMMAND_MODE_SLEEP ) return aes132c_send_command( (uint8_t *)command_sleep, options );

    return aes132c_send_command( (uint8_t *)command_standby, options );
}

/** \brief This function wakes up a device.
 *
 * It takes about 1.5 ms for the device to wake up when in Sleep mode, and
 * about 0.3 ms when in Standby mode.
 * \return status of the operation
 */
uint8_t aes132c_wakeup( void ) { return aes132c_wait_for_device_ready(); }

/** \brief This function puts a device into Sleep mode.
 * \return status of the operation
 * */
uint8_t aes132c_sleep( void ) { return aes132c_send_sleep_command( AES132_COMMAND_MODE_SLEEP ); }

/** \brief This function puts a device into Standby mode.
 * \return status of the operation
 * */
uint8_t aes132c_standby( void ) { return aes132c_send_sleep_command( AES132_COMMAND_MODE_STANDBY ); }

/** \brief This function writes to or reads from memory with retries.
 * \param[in] count number of bytes to send
 * \param[in] word_address word address
 * \param[in, out] data pointer to tx or rx data
 * \param[in] read flag indicating whether to read (#AES132_READ) or write (#AES132_WRITE)
 * \return status of the operation or response return code
 * */
uint8_t aes132c_access_memory( uint8_t count, uint16_t word_address, uint8_t *data, uint8_t read )
{
    uint8_t aes132_lib_return;
    uint8_t n_retries_memory_access = AES132_RETRY_COUNT_ERROR;
    uint8_t response_buffer[AES132_RESPONSE_SIZE_MIN];

    do {
        aes132_lib_return = aes132c_wait_for_device_ready();
        if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
            ESP_LOGW( TAG, "Lost communication with device; need to resync." );
            break;
        }

        if( read == 0 ) {
            ESP_LOGD( TAG, "Writing to the device" );
            aes132_lib_return = aes132p_write_memory_physical( count, word_address, data );
            if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
                ESP_LOGW( TAG, "Communcation failed. Retry..." );
                continue;
            }
            ESP_LOGD( TAG, "Communication Succeeded" );

            if( word_address >= AES132_IO_ADDR ) {
                // Return success and do not read response buffer
                // if we wrote to the I/O buffer
                // or to the address used to reset the I/O buffer index.
                return aes132_lib_return;
            }

            // Read response buffer when writing to device memory to
            // check for write success.
            aes132c_wait_for_response_ready();

            aes132_lib_return = aes132c_receive_response( sizeof( response_buffer ), response_buffer );
            if( aes132_lib_return == AES132_FUNCTION_RETCODE_SUCCESS ) {
                ESP_LOGD( TAG, "Reading the return code from the I/O buffer "
                               "succeeded. Return the code byte." );
                return response_buffer[AES132_RESPONSE_INDEX_RETURN_CODE];
            }
            else {
                ESP_LOGD( TAG, "Reading the return code from the I/O buffer "
                               "failed. Return the error code that "
                               "aes132c_receive_response returned." );
                return aes132_lib_return;
            }
        }
        else {
            ESP_LOGD( TAG, "Reading from the device" );
            aes132_lib_return = aes132p_read_memory_physical( count, word_address, data );
            if( aes132_lib_return == AES132_FUNCTION_RETCODE_SUCCESS ) {
                ESP_LOGD( TAG, "aes132p_read_memory_physical succeess!" );
                return aes132_lib_return;
            }
            else {
                ESP_LOGW( TAG, "aes132p_read_memory_physical did not succeed." );
            }
        }
    } while( --n_retries_memory_access > 0 );

    return aes132_lib_return;
}

/** \brief This function writes a command into the I/O buffer of the device.
 *
 * The fields of the command buffer are described below:\n
 * <count, 1 byte> <op-code, 1 byte> <mode, 1 byte>
 * <param1, 2 bytes> <param2, 2 bytes> <data, n bytes (optional)> <crc, 2 bytes)>\n
 * The "count" field and size of the command buffer has to include the
 * two CRC bytes independent from the #AES132_OPTION_NO_APPEND_CRC flag in the
 * options parameter.\n
 * The function retries sending the command if the device indicates a CRC error.
 * \param[in] command pointer to command buffer
 * \param[in] options flags for communication behavior
 * \return status of the operation
 */
uint8_t aes132c_send_command( uint8_t *command, uint8_t options )
{
    uint8_t aes132_lib_return;
    uint8_t n_retries = AES132_RETRY_COUNT_ERROR;
    uint8_t device_status_register;
    uint8_t count = command[AES132_COMMAND_INDEX_COUNT];  // command length

    /* Compute CRC */
    if( ( options & AES132_OPTION_NO_APPEND_CRC ) == 0 ) {
        ESP_LOGD( TAG, "Computing CRC for command opcode %.2X, length %d", command[1], command[0] );
        aes132c_calculate_crc( count - AES132_CRC_SIZE, command, &command[count - AES132_CRC_SIZE] );
    }

    do {
        // Attempt to write the command buffer
        aes132_lib_return = aes132c_access_memory( count, AES132_IO_ADDR, command, AES132_WRITE );
        if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
            ESP_LOGE( TAG, "Writing to the I/O buffer failed. Retry." );
            continue;
        }

        if( ( options & AES132_OPTION_NO_STATUS_READ ) != 0 ) {
            // We don't read device status register when sending a Sleep command.
            return aes132_lib_return;
        }

        // Try to read the device status register.
        // If it fails with an I2C nack of the I2C write address,
        // we know that the device is busy.
        aes132_lib_return = aes132c_read_device_status_register( &device_status_register );
        if( I2C_FUNCTION_RETCODE_SUCCESS == aes132_lib_return ) {
            ESP_LOGD( TAG, "Checking the CRC bit of status register response." );
            if( ( device_status_register & AES132_CRC_ERROR_BIT ) != 0 ) {
                ESP_LOGW( TAG, "The device has calculated a not-matching CRC, "
                               "which indicates a flawed communication." );
                // Retry sending the command.
                aes132_lib_return = AES132_FUNCTION_RETCODE_BAD_CRC_TX;
            }
        }
        else if( aes132_lib_return == I2C_FUNCTION_RETCODE_NACK ) {
            // Receiving a nack to a I2C address write
            // indicates that the device is busy executing the command.
            // We therefore return success.
            ESP_LOGD( TAG, "Device busy executing command (good thing)" );
            return AES132_FUNCTION_RETCODE_SUCCESS;
        }
        else {
            // In case of read-device-status-register failure,
            // we do not send the command again because we do not want certain
            // commands being repeated, e.g. the Counter command.
            ESP_LOGE( TAG, "Read Device Status Failure: %02X", aes132_lib_return );
            return aes132_lib_return;
        }
    } while( ( aes132_lib_return != I2C_FUNCTION_RETCODE_SUCCESS ) && ( --n_retries > 0 ) );

    // We did not succeed sending a command.
    return aes132_lib_return;
}

/** \brief This function reads a response from the I/O buffer of the device.
 * \param[in] size number of bytes to retrieve (<= response buffer size allocated by caller)
 * \param[out] response pointer to retrieved response
 * \return status of the operation
 */
uint8_t aes132c_receive_response( uint8_t size, uint8_t *response )
{
    uint8_t aes132_lib_return;
    uint8_t n_retries = AES132_RETRY_COUNT_ERROR;
    uint8_t crc[AES132_CRC_SIZE];
    uint8_t crc_index;
    uint8_t count_byte;

    do {
        aes132_lib_return = aes132c_wait_for_response_ready();
        if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
            // Waiting for the Response-Ready bit timed out.
            // We might have lost communication.
            continue;
        }

        // Read count byte from response buffer.
        aes132_lib_return = aes132p_read_memory_physical( 1, AES132_IO_ADDR, &response[AES132_COMMAND_INDEX_COUNT] );
        if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
            // Reading the count byte failed. We might have lost communication.
            // Re-synchronize and retry.
            continue;
        }

        count_byte = response[AES132_RESPONSE_INDEX_COUNT];
        if( count_byte > size ) {
            // The buffer provided by the caller is not big enough to store the entire response,
            // or the count value got corrupted due to a bad communication channel.
            // Re-synchronize and retry.
            aes132_lib_return = AES132_FUNCTION_RETCODE_SIZE_TOO_SMALL;
            continue;
        }

        if( ( count_byte < AES132_RESPONSE_SIZE_MIN ) || ( count_byte > AES132_RESPONSE_SIZE_MAX ) ) {
            // A response has to be between #AES132_RESPONSE_SIZE_MIN
            // and #AES132_RESPONSE_SIZE_MAX bytes long to be valid.
            aes132_lib_return = AES132_FUNCTION_RETCODE_COUNT_INVALID;
            continue;
        }

        // Read remainder of response.
        ESP_LOGD( TAG, "Reading the rest of the response" );
        aes132_lib_return = aes132p_read_memory_physical( count_byte - 1, AES132_IO_ADDR,
                                                          &response[AES132_RESPONSE_INDEX_RETURN_CODE] );
        if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
            // Reading the remainder of the response failed. We might have lost communication.
            continue;
        }

        // Check CRC.
        crc_index = count_byte - AES132_CRC_SIZE;
        aes132c_calculate_crc( crc_index, response, crc );
        if( ( crc[0] == response[crc_index] ) && ( crc[1] == response[crc_index + 1] ) )
            // We received a consistent response packet.
            return response[AES132_RESPONSE_INDEX_RETURN_CODE];

        // Received and calculated CRC do not match.
        // Retry reading the response buffer.
        aes132_lib_return = AES132_FUNCTION_RETCODE_BAD_CRC_RX;

        // Retry if communication failed, or CRC did not match.
    } while( ( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) && ( --n_retries > 0 ) );

    return aes132_lib_return;
}

/** \brief This function sends a command and reads its response.
 * \param[in] command pointer to command buffer
 * \param[in] size size of response buffer
 * \param[out] response pointer to response buffer
 * \param[in] options flags for communication behavior
 * \return status of the operation
 */
uint8_t aes132c_send_and_receive( uint8_t *command, uint8_t size, uint8_t *response, uint8_t options )
{
    uint8_t aes132_lib_return = aes132c_send_command( command, options );
    if( aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS ) {
        ESP_LOGE( TAG, "Send Error %02X", aes132_lib_return );
        return aes132_lib_return;
    }

    return aes132c_receive_response( size, response );
}
