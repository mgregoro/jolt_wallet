#ifndef __AES132_JOLT_H__
#define __AES132_JOLT_H__

/* Creates a new key in the stretch slot. Will cause loss of mnemonic */
uint8_t aes132_create_stretch_key();

/* Should be first thing called after setting up i2c */
uint8_t aes132_jolt_setup();

/* Only attempts key and returns the cumulative counter */
uint8_t aes132_pin_attempt(const uint8_t *key, uint32_t *counter, uint8_t *secret);

uint8_t aes132_pin_load_keys(const uint8_t *key);

/* Stores the value (key ^ secret) into each user zone */
uint8_t aes132_pin_load_zones(const uint8_t *key, const uint8_t *secret);

/* Populates counter value from ataes132a */
uint8_t aes132_pin_counter(uint32_t *counter);

/* Takes and returns data, encrypted n_iter times by the key in the stretch 
 * slot */
uint8_t aes132_stretch(uint8_t *data, const uint8_t data_len, uint32_t n_iter);

#endif