#include "jolt_lib.h"
#include "syscore/launcher.h"
#include "unity.h"

static const char MODULE_NAME[] = "[test_contacts]";

TEST_CASE( "general contact test", MODULE_NAME )
{
    jolt_launch_set_name( "test" );
    jolt_json_del_app();

    /* Standard Usage, first contact */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "add", "Bob Jones", "crypto_address"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, jolt_app_cmd_contact( argcount( argv ), argv ) );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );

        uint8_t expected_scr_data[] = {
                0x05, 0x20, 0xF8, 0x20, 0x00, 0xC0, 0x83, 0xA0, 0x03, 0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00,
                0x20, 0xF8, 0x20, 0x83, 0x00, 0x01, 0xF0, 0x83, 0x08, 0x03, 0x10, 0x00, 0xC0, 0x83, 0x20, 0x04, 0xC0,
                0x00, 0xE0, 0x40, 0x82, 0x20, 0x05, 0xC0, 0x00, 0x20, 0xF8, 0x20, 0x82, 0x00, 0x83, 0xA0, 0x03, 0xC0,
                0x00, 0xC0, 0x83, 0x20, 0x06, 0x00, 0x20, 0xF8, 0x20, 0x00, 0x40, 0x83, 0xA0, 0x01, 0x20, 0xC0, 0x00,
                0x07, 0x08, 0x09, 0x8A, 0x48, 0x49, 0x4A, 0x8A, 0x82, 0x0A, 0x01, 0x08, 0x82, 0x0A, 0x03, 0xCA, 0x0A,
                0x09, 0x82, 0x08, 0x02, 0x09, 0xCA, 0x83, 0x08, 0x01, 0x09, 0x83, 0x0A, 0x03, 0x09, 0x08, 0x09, 0x83,
                0x0A, 0x03, 0x09, 0x08, 0x0B, 0x83, 0x08, 0x07, 0x0B, 0x08, 0xC8, 0x09, 0x0A, 0x08, 0x09, 0x83, 0x0A,
                0x03, 0x0B, 0x08, 0x09, 0x83, 0x0A, 0x05, 0x08, 0xC8, 0x09, 0x0A, 0x88, 0x84, 0x0A, 0x01, 0x09, 0xC0,
                0x08, 0x82, 0x00, 0x01, 0x9F, 0x83, 0x02, 0x03, 0x9F, 0x00, 0x0E, 0x82, 0x11, 0x04, 0x12, 0x1F, 0x00,
                0x0E, 0x82, 0x11, 0x02, 0x12, 0x1F, 0x83, 0x00, 0x01, 0x0E, 0x83, 0x11, 0x02, 0x00, 0x0E, 0x82, 0x11,
                0x05, 0x91, 0x8E, 0x80, 0x9F, 0x02, 0x82, 0x01, 0x07, 0x1E, 0x00, 0x01, 0x0F, 0x11, 0x80, 0x08, 0x83,
                0x15, 0x03, 0x1E, 0x00, 0x0E, 0x82, 0x11, 0x07, 0x91, 0x80, 0x81, 0x0F, 0x11, 0x00, 0x08, 0xC7, 0x00,
                0x07, 0x3F, 0x02, 0x04, 0x08, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x09, 0x3C, 0x00, 0x3E, 0x02, 0x0C, 0x02,
                0x3C, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x11, 0x83, 0x00, 0x01, 0x3F, 0x83, 0x24, 0x03, 0x1B,
                0x00, 0x1C, 0x83, 0x22, 0x04, 0x1C, 0x00, 0x3F, 0x24, 0x82, 0x22, 0x01, 0x1C, 0x83, 0x00, 0x01, 0x10,
                0x82, 0x20, 0x01, 0x1F, 0x82, 0x00, 0x01, 0x1C, 0x83, 0x22, 0x04, 0x1C, 0x00, 0x3E, 0x04, 0x82, 0x02,
                0x03, 0x3C, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x24, 0x83, 0x2A, 0x01, 0x12, 0xB3, 0x00, 0x01,
                0x7E, 0x83, 0x09, 0x03, 0x7E, 0x00, 0x38, 0x82, 0x44, 0x04, 0x48, 0x7F, 0x00, 0x38, 0x82, 0x44, 0x05,
                0x48, 0x7F, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x03, 0x08, 0x00, 0x38, 0x83, 0x54, 0x03, 0x58, 0x00, 0x48,
                0x83, 0x54, 0x03, 0x24, 0x00, 0x48, 0x83, 0x54, 0x03, 0x24, 0x00, 0x22, 0xD5, 0x00, 0x01, 0x70, 0x83,
                0x88, 0x01, 0x50, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x38, 0x83, 0x40, 0x01,
                0xF8, 0x82, 0x00, 0x01, 0xF8, 0x83, 0x48, 0x01, 0x30, 0x82, 0x00, 0x02, 0x08, 0x7E, 0x82, 0x88, 0x01,
                0x40, 0x82, 0x00, 0x01, 0x70, 0x83, 0x88, 0x01, 0x70, 0x89, 0x00, 0x01, 0x40, 0x83, 0xA8, 0x01, 0xF0,
                0x82, 0x00, 0x01, 0x70, 0x83, 0x88, 0x01, 0xFE, 0x82, 0x00, 0x01, 0x70, 0x83, 0x88, 0x01, 0xFE, 0x82,
                0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x70, 0x83, 0xA8, 0x01, 0x30, 0x82, 0x00, 0x01,
                0x90, 0x83, 0xA8, 0x01, 0x48, 0x82, 0x00, 0x01, 0x90, 0x83, 0xA8, 0x01, 0x48, 0xAF, 0x00, 0x83, 0x01,
                0x83, 0x00, 0x01, 0x01, 0x94, 0x00, 0x85, 0x01, 0xFF, 0x00, 0xD0, 0x00};
        jolt_display_t expected_scr = {
                .encoding = JOLT_ENCODING_JRLE,
                .len      = sizeof( expected_scr_data ),
                .data     = expected_scr_data,
        };
        TEST_ASSERT_EQUAL_DISPLAY( &expected_scr, NULL );
        JOLT_ENTER;  // Confirm screen

        TEST_ASSERT_EQUAL_INT( 0, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "{\"exit_code\":0}", buf );
    }
    {
        /* Read back to make sure it's correct */
        char *buf;
        cJSON *json, *contacts, *contact;
        json = jolt_json_read_app();
        TEST_ASSERT_NOT_NULL( json );
        TEST_ASSERT_NOT_NULL( contacts = cJSON_Get( json, "contacts" ) );
        TEST_ASSERT_EQUAL_INT( 1, cJSON_GetArraySize( contacts ) );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 0 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Bob Jones\",\"address\":\"crypto_address\"}", buf );
        cJSON_Delete( json );
        free( buf );
    }

    /* Standard Usage, second contact */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "add", "Madam MeowMeow", "Some arbitrary crypto address"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, jolt_app_cmd_contact( argcount( argv ), argv ) );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );

        uint8_t expected_scr_data[] = {
                0x05, 0x20, 0xF8, 0x20, 0x00, 0xC0, 0x83, 0xA0, 0x03, 0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00,
                0x20, 0xF8, 0x20, 0x83, 0x00, 0x01, 0xF0, 0x83, 0x08, 0x03, 0x10, 0x00, 0xC0, 0x83, 0x20, 0x04, 0xC0,
                0x00, 0xE0, 0x40, 0x82, 0x20, 0x05, 0xC0, 0x00, 0x20, 0xF8, 0x20, 0x82, 0x00, 0x83, 0xA0, 0x03, 0xC0,
                0x00, 0xC0, 0x83, 0x20, 0x06, 0x00, 0x20, 0xF8, 0x20, 0x00, 0x40, 0x83, 0xA0, 0x01, 0x20, 0xC0, 0x00,
                0x07, 0x08, 0x09, 0x8A, 0x48, 0x49, 0x4A, 0x8A, 0x82, 0x0A, 0x01, 0x08, 0x82, 0x0A, 0x03, 0xCA, 0x0A,
                0x09, 0x82, 0x08, 0x02, 0x09, 0xCA, 0x83, 0x08, 0x01, 0x09, 0x83, 0x0A, 0x03, 0x09, 0x08, 0x09, 0x83,
                0x0A, 0x03, 0x09, 0x08, 0x0B, 0x83, 0x08, 0x07, 0x0B, 0x08, 0xC8, 0x09, 0x0A, 0x08, 0x09, 0x83, 0x0A,
                0x03, 0x0B, 0x08, 0x09, 0x83, 0x0A, 0x05, 0x08, 0xC8, 0x09, 0x0A, 0x88, 0x84, 0x0A, 0x01, 0x09, 0xC0,
                0x08, 0x82, 0x00, 0x01, 0x9F, 0x83, 0x02, 0x03, 0x9F, 0x00, 0x0E, 0x82, 0x11, 0x04, 0x12, 0x1F, 0x00,
                0x0E, 0x82, 0x11, 0x02, 0x12, 0x1F, 0x83, 0x00, 0x01, 0x0E, 0x83, 0x11, 0x02, 0x00, 0x0E, 0x82, 0x11,
                0x05, 0x91, 0x0E, 0x00, 0x1F, 0x82, 0x82, 0x01, 0x07, 0x1E, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x08, 0x82,
                0x15, 0x04, 0x95, 0x1E, 0x00, 0x0E, 0x83, 0x11, 0x06, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x08, 0x83, 0x00,
                0x01, 0x80, 0x83, 0x00, 0x01, 0x80, 0x93, 0x00, 0x01, 0x80, 0x83, 0x00, 0x01, 0x80, 0xA7, 0x00, 0x07,
                0x3F, 0x02, 0x04, 0x08, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x09, 0x3C, 0x00, 0x3E, 0x02, 0x0C, 0x02, 0x3C,
                0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x11, 0x83, 0x00, 0x07, 0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00,
                0x10, 0x83, 0x2A, 0x03, 0x3C, 0x00, 0x1C, 0x82, 0x22, 0x04, 0x24, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x07,
                0x3C, 0x00, 0x3E, 0x02, 0x0C, 0x02, 0x3C, 0x83, 0x00, 0x07, 0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00, 0x1C,
                0x83, 0x2A, 0x03, 0x2C, 0x00, 0x1C, 0x83, 0x22, 0x0F, 0x1C, 0x00, 0x1E, 0x20, 0x18, 0x20, 0x1E, 0x00,
                0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x1C, 0x83, 0x22, 0x07, 0x1C,
                0x00, 0x1E, 0x20, 0x18, 0x20, 0x1E, 0x95, 0x00, 0x01, 0x7E, 0x83, 0x09, 0x03, 0x7E, 0x00, 0x38, 0x82,
                0x44, 0x04, 0x48, 0x7F, 0x00, 0x38, 0x82, 0x44, 0x05, 0x48, 0x7F, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x03,
                0x08, 0x00, 0x38, 0x83, 0x54, 0x03, 0x58, 0x00, 0x48, 0x83, 0x54, 0x03, 0x24, 0x00, 0x48, 0x83, 0x54,
                0x03, 0x24, 0x00, 0x22, 0xD5, 0x00, 0x01, 0x4C, 0x84, 0x92, 0x01, 0x64, 0x82, 0x00, 0x01, 0x70, 0x83,
                0x88, 0x01, 0x70, 0x82, 0x00, 0x05, 0xF8, 0x08, 0xF0, 0x08, 0xF0, 0x82, 0x00, 0x01, 0x70, 0x83, 0xA8,
                0x01, 0x30, 0x84, 0x00, 0x01, 0x40, 0x83, 0xA8, 0x01, 0xF0, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08,
                0x82, 0x00, 0x01, 0xFE, 0x83, 0x88, 0x01, 0x70, 0x82, 0x00, 0x03, 0x88, 0xFA, 0x80, 0x82, 0x00, 0x02,
                0x08, 0x7E, 0x82, 0x88, 0x01, 0x40, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x40,
                0x83, 0xA8, 0x01, 0xF0, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x38, 0x83, 0x40,
                0x01, 0xF8, 0xA6, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xA0, 0x82, 0x00, 0x02, 0xF0, 0x20, 0x83, 0x10,
                0x82, 0x00, 0x01, 0x70, 0x83, 0x80, 0x01, 0xF0, 0x82, 0x00, 0x01, 0xF0, 0x83, 0x90, 0x01, 0x60, 0x82,
                0x00, 0x02, 0x10, 0xFC, 0x82, 0x10, 0x01, 0x80, 0x82, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xE0, 0x84,
                0x00, 0x01, 0x80, 0x83, 0x50, 0x01, 0xE0, 0x82, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xFC, 0x82, 0x00,
                0x01, 0xE0, 0x83, 0x10, 0x01, 0xFC, 0x82, 0x00, 0x02, 0xF0, 0x20, 0x83, 0x10, 0x82, 0x00, 0x01, 0xE0,
                0x83, 0x50, 0x01, 0x60, 0x82, 0x00, 0x01, 0x20, 0x83, 0x50, 0x01, 0x90, 0x82, 0x00, 0x01, 0x21, 0x82,
                0x51, 0x02, 0x50, 0x90, 0xA6, 0x00, 0x83, 0x01, 0x83, 0x00, 0x01, 0x01, 0x87, 0x00, 0x83, 0x02, 0x01,
                0x01, 0x82, 0x00, 0x01, 0x03, 0x88, 0x00, 0x82, 0x01, 0x84, 0x00, 0x83, 0x01, 0x86, 0x00, 0x84, 0x01,
                0x83, 0x00, 0x84, 0x01, 0x83, 0x00, 0x84, 0x01, 0x82, 0x00, 0x01, 0x01, 0x87, 0x00, 0x83, 0x01, 0x83,
                0x00, 0x84, 0x01, 0x83, 0x00, 0x84, 0x01, 0xA4, 0x00};
        jolt_display_t expected_scr = {
                .encoding = JOLT_ENCODING_JRLE,
                .len      = sizeof( expected_scr_data ),
                .data     = expected_scr_data,
        };
        TEST_ASSERT_EQUAL_DISPLAY( &expected_scr, NULL );
        JOLT_ENTER;  // Confirm screen

        TEST_ASSERT_EQUAL_INT( 0, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "{\"exit_code\":0}", buf );
    }
    {
        /* Read back to make sure it's correct */
        char *buf;
        cJSON *json, *contacts, *contact;
        json = jolt_json_read_app();
        TEST_ASSERT_NOT_NULL( json );
        TEST_ASSERT_NOT_NULL( contacts = cJSON_Get( json, "contacts" ) );
        TEST_ASSERT_EQUAL_INT( 2, cJSON_GetArraySize( contacts ) );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 0 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Bob Jones\",\"address\":\"crypto_address\"}", buf );
        free( buf );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 1 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Madam MeowMeow\",\"address\":\"Some arbitrary crypto address\"}", buf );
        free( buf );
        cJSON_Delete( json );
    }

    /* User declines an Add */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "add", "Madam MeowMeow", "Some arbitrary crypto address"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, jolt_app_cmd_contact( argcount( argv ), argv ) );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );

        uint8_t expected_scr_data[] = {
                0x05, 0x20, 0xF8, 0x20, 0x00, 0xC0, 0x83, 0xA0, 0x03, 0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00,
                0x20, 0xF8, 0x20, 0x83, 0x00, 0x01, 0xF0, 0x83, 0x08, 0x03, 0x10, 0x00, 0xC0, 0x83, 0x20, 0x04, 0xC0,
                0x00, 0xE0, 0x40, 0x82, 0x20, 0x05, 0xC0, 0x00, 0x20, 0xF8, 0x20, 0x82, 0x00, 0x83, 0xA0, 0x03, 0xC0,
                0x00, 0xC0, 0x83, 0x20, 0x06, 0x00, 0x20, 0xF8, 0x20, 0x00, 0x40, 0x83, 0xA0, 0x01, 0x20, 0xC0, 0x00,
                0x07, 0x08, 0x09, 0x8A, 0x48, 0x49, 0x4A, 0x8A, 0x82, 0x0A, 0x01, 0x08, 0x82, 0x0A, 0x03, 0xCA, 0x0A,
                0x09, 0x82, 0x08, 0x02, 0x09, 0xCA, 0x83, 0x08, 0x01, 0x09, 0x83, 0x0A, 0x03, 0x09, 0x08, 0x09, 0x83,
                0x0A, 0x03, 0x09, 0x08, 0x0B, 0x83, 0x08, 0x07, 0x0B, 0x08, 0xC8, 0x09, 0x0A, 0x08, 0x09, 0x83, 0x0A,
                0x03, 0x0B, 0x08, 0x09, 0x83, 0x0A, 0x05, 0x08, 0xC8, 0x09, 0x0A, 0x88, 0x84, 0x0A, 0x01, 0x09, 0xC0,
                0x08, 0x82, 0x00, 0x01, 0x9F, 0x83, 0x02, 0x03, 0x9F, 0x00, 0x0E, 0x82, 0x11, 0x04, 0x12, 0x1F, 0x00,
                0x0E, 0x82, 0x11, 0x02, 0x12, 0x1F, 0x83, 0x00, 0x01, 0x0E, 0x83, 0x11, 0x02, 0x00, 0x0E, 0x82, 0x11,
                0x05, 0x91, 0x0E, 0x00, 0x1F, 0x82, 0x82, 0x01, 0x07, 0x1E, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x08, 0x82,
                0x15, 0x04, 0x95, 0x1E, 0x00, 0x0E, 0x83, 0x11, 0x06, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x08, 0x83, 0x00,
                0x01, 0x80, 0x83, 0x00, 0x01, 0x80, 0x93, 0x00, 0x01, 0x80, 0x83, 0x00, 0x01, 0x80, 0xA7, 0x00, 0x07,
                0x3F, 0x02, 0x04, 0x08, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x09, 0x3C, 0x00, 0x3E, 0x02, 0x0C, 0x02, 0x3C,
                0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x11, 0x83, 0x00, 0x07, 0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00,
                0x10, 0x83, 0x2A, 0x03, 0x3C, 0x00, 0x1C, 0x82, 0x22, 0x04, 0x24, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x07,
                0x3C, 0x00, 0x3E, 0x02, 0x0C, 0x02, 0x3C, 0x83, 0x00, 0x07, 0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00, 0x1C,
                0x83, 0x2A, 0x03, 0x2C, 0x00, 0x1C, 0x83, 0x22, 0x0F, 0x1C, 0x00, 0x1E, 0x20, 0x18, 0x20, 0x1E, 0x00,
                0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x1C, 0x83, 0x22, 0x07, 0x1C,
                0x00, 0x1E, 0x20, 0x18, 0x20, 0x1E, 0x95, 0x00, 0x01, 0x7E, 0x83, 0x09, 0x03, 0x7E, 0x00, 0x38, 0x82,
                0x44, 0x04, 0x48, 0x7F, 0x00, 0x38, 0x82, 0x44, 0x05, 0x48, 0x7F, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x03,
                0x08, 0x00, 0x38, 0x83, 0x54, 0x03, 0x58, 0x00, 0x48, 0x83, 0x54, 0x03, 0x24, 0x00, 0x48, 0x83, 0x54,
                0x03, 0x24, 0x00, 0x22, 0xD5, 0x00, 0x01, 0x4C, 0x84, 0x92, 0x01, 0x64, 0x82, 0x00, 0x01, 0x70, 0x83,
                0x88, 0x01, 0x70, 0x82, 0x00, 0x05, 0xF8, 0x08, 0xF0, 0x08, 0xF0, 0x82, 0x00, 0x01, 0x70, 0x83, 0xA8,
                0x01, 0x30, 0x84, 0x00, 0x01, 0x40, 0x83, 0xA8, 0x01, 0xF0, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08,
                0x82, 0x00, 0x01, 0xFE, 0x83, 0x88, 0x01, 0x70, 0x82, 0x00, 0x03, 0x88, 0xFA, 0x80, 0x82, 0x00, 0x02,
                0x08, 0x7E, 0x82, 0x88, 0x01, 0x40, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x40,
                0x83, 0xA8, 0x01, 0xF0, 0x82, 0x00, 0x02, 0xF8, 0x10, 0x83, 0x08, 0x82, 0x00, 0x01, 0x38, 0x83, 0x40,
                0x01, 0xF8, 0xA6, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xA0, 0x82, 0x00, 0x02, 0xF0, 0x20, 0x83, 0x10,
                0x82, 0x00, 0x01, 0x70, 0x83, 0x80, 0x01, 0xF0, 0x82, 0x00, 0x01, 0xF0, 0x83, 0x90, 0x01, 0x60, 0x82,
                0x00, 0x02, 0x10, 0xFC, 0x82, 0x10, 0x01, 0x80, 0x82, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xE0, 0x84,
                0x00, 0x01, 0x80, 0x83, 0x50, 0x01, 0xE0, 0x82, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xFC, 0x82, 0x00,
                0x01, 0xE0, 0x83, 0x10, 0x01, 0xFC, 0x82, 0x00, 0x02, 0xF0, 0x20, 0x83, 0x10, 0x82, 0x00, 0x01, 0xE0,
                0x83, 0x50, 0x01, 0x60, 0x82, 0x00, 0x01, 0x20, 0x83, 0x50, 0x01, 0x90, 0x82, 0x00, 0x01, 0x21, 0x82,
                0x51, 0x02, 0x50, 0x90, 0xA6, 0x00, 0x83, 0x01, 0x83, 0x00, 0x01, 0x01, 0x87, 0x00, 0x83, 0x02, 0x01,
                0x01, 0x82, 0x00, 0x01, 0x03, 0x88, 0x00, 0x82, 0x01, 0x84, 0x00, 0x83, 0x01, 0x86, 0x00, 0x84, 0x01,
                0x83, 0x00, 0x84, 0x01, 0x83, 0x00, 0x84, 0x01, 0x82, 0x00, 0x01, 0x01, 0x87, 0x00, 0x83, 0x01, 0x83,
                0x00, 0x84, 0x01, 0x83, 0x00, 0x84, 0x01, 0xA4, 0x00};
        jolt_display_t expected_scr = {
                .encoding = JOLT_ENCODING_JRLE,
                .len      = sizeof( expected_scr_data ),
                .data     = expected_scr_data,
        };
        TEST_ASSERT_EQUAL_DISPLAY( &expected_scr, NULL );
        JOLT_BACK;  // Deny confirm screen

        TEST_ASSERT_EQUAL_INT( JOLT_APP_CMD_CONTACT_DECLINED, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "{\"exit_code\":4}", buf );
    }
    {
        /* Read back to make sure it's correct */
        char *buf;
        cJSON *json, *contacts, *contact;
        json = jolt_json_read_app();
        TEST_ASSERT_NOT_NULL( json );
        TEST_ASSERT_NOT_NULL( contacts = cJSON_Get( json, "contacts" ) );
        TEST_ASSERT_EQUAL_INT( 2, cJSON_GetArraySize( contacts ) );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 0 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Bob Jones\",\"address\":\"crypto_address\"}", buf );
        free( buf );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 1 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Madam MeowMeow\",\"address\":\"Some arbitrary crypto address\"}", buf );
        free( buf );
        cJSON_Delete( json );
    }

    /* Print out the current contact book */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "read"};
        TEST_ASSERT_EQUAL_INT( 0, jolt_app_cmd_contact( argcount( argv ), argv ) );
        TEST_ASSERT_EQUAL_STRING( "{\"contacts\":[{\"name\":\"Bob Jones\",\"address\":\"crypto_address\"},"
                                  "{\"name\":\"Madam MeowMeow\",\"address\":\"Some arbitrary crypto address\"}]}",
                                  buf );
    }

    /* Update the first contact */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "update", "0", "Finn Mertens", "dosh"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, jolt_app_cmd_contact( argcount( argv ), argv ) );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );

        uint8_t expected_scr_data[] = {
                0x05, 0x20, 0xF8, 0x20, 0x00, 0xC0, 0x83, 0xA0, 0x03, 0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00,
                0x20, 0xF8, 0x20, 0x83, 0x00, 0x01, 0xF0, 0x83, 0x08, 0x03, 0x10, 0x00, 0xC0, 0x83, 0x20, 0x04, 0xC0,
                0x00, 0xE0, 0x40, 0x82, 0x20, 0x05, 0xC0, 0x00, 0x20, 0xF8, 0x20, 0x82, 0x00, 0x83, 0xA0, 0x03, 0xC0,
                0x00, 0xC0, 0x83, 0x20, 0x06, 0x00, 0x20, 0xF8, 0x20, 0x00, 0x40, 0x83, 0xA0, 0x01, 0x20, 0xC0, 0x00,
                0x07, 0x08, 0x09, 0xCA, 0x08, 0x09, 0x0A, 0xCA, 0x82, 0x0A, 0x01, 0x08, 0x84, 0x0A, 0x01, 0x09, 0x82,
                0x08, 0x02, 0x09, 0xCA, 0x83, 0x08, 0x01, 0x09, 0x83, 0x0A, 0x03, 0x09, 0xC8, 0x09, 0x83, 0x0A, 0x03,
                0x09, 0x08, 0x0B, 0x83, 0x08, 0x01, 0x0B, 0x82, 0x08, 0x04, 0x09, 0x0A, 0x08, 0x09, 0x83, 0x0A, 0x03,
                0x0B, 0x08, 0x09, 0x83, 0x0A, 0x82, 0x08, 0x03, 0xC9, 0x0A, 0x08, 0x84, 0x0A, 0x01, 0x09, 0x87, 0x08,
                0x01, 0xC8, 0x84, 0x08, 0x01, 0xC8, 0x83, 0x48, 0x01, 0x88, 0x87, 0x08, 0x01, 0xC8, 0xA7, 0x08, 0x82,
                0x00, 0x02, 0x0F, 0x10, 0x82, 0x90, 0x03, 0x8F, 0x00, 0x3F, 0x83, 0x09, 0x03, 0x06, 0x00, 0x0E, 0x82,
                0x11, 0x04, 0x12, 0x1F, 0x00, 0x08, 0x83, 0x15, 0x07, 0x1E, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x0E, 0x83,
                0x15, 0x02, 0x16, 0x80, 0x82, 0x00, 0x01, 0x0E, 0x83, 0x11, 0x02, 0x00, 0x0E, 0x83, 0x11, 0x04, 0x0E,
                0x00, 0x1F, 0x02, 0x82, 0x01, 0x07, 0x1E, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x08, 0x83, 0x15, 0x03, 0x1E,
                0x00, 0x0E, 0x83, 0x11, 0x04, 0x00, 0x01, 0x0F, 0x11, 0x83, 0x00, 0x01, 0x1F, 0x83, 0x12, 0x03, 0x0D,
                0x00, 0x0E, 0x83, 0x11, 0x04, 0x0E, 0x00, 0x1F, 0x12, 0x82, 0x11, 0x01, 0x0E, 0xA5, 0x00, 0x01, 0x10,
                0x82, 0x20, 0x01, 0x1F, 0x82, 0x00, 0x01, 0x1C, 0x83, 0x22, 0x04, 0x1C, 0x00, 0x3E, 0x04, 0x82, 0x02,
                0x03, 0x3C, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x24, 0x83, 0x2A, 0x01, 0x12, 0x83, 0x00, 0x05,
                0x02, 0x1F, 0x22, 0x00, 0x1C, 0x83, 0x22, 0x03, 0x1C, 0x00, 0x11, 0xD5, 0x00, 0x07, 0x7F, 0x04, 0x08,
                0x10, 0x7F, 0x00, 0x20, 0x83, 0x54, 0x09, 0x78, 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, 0x38, 0x83,
                0x54, 0x03, 0x58, 0x00, 0x22, 0x83, 0x00, 0x01, 0x7F, 0x83, 0x09, 0x07, 0x00, 0x44, 0x7D, 0x40, 0x00,
                0x7C, 0x08, 0x82, 0x04, 0x04, 0x78, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x01, 0x78, 0x83, 0x00, 0x07, 0x7F,
                0x02, 0x0C, 0x02, 0x7F, 0x00, 0x38, 0x83, 0x54, 0x04, 0x58, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x07, 0x08,
                0x00, 0x04, 0x3F, 0x44, 0x00, 0x38, 0x83, 0x54, 0x04, 0x58, 0x00, 0x7C, 0x08, 0x82, 0x04, 0x03, 0x78,
                0x00, 0x48, 0x83, 0x54, 0x01, 0x24, 0xA6, 0x00, 0x01, 0xFC, 0x83, 0x12, 0x03, 0xFC, 0x00, 0x70, 0x82,
                0x88, 0x04, 0x90, 0xFE, 0x00, 0x70, 0x82, 0x88, 0x05, 0x90, 0xFE, 0x00, 0xF8, 0x10, 0x82, 0x08, 0x03,
                0x10, 0x00, 0x70, 0x83, 0xA8, 0x03, 0xB0, 0x00, 0x90, 0x83, 0xA8, 0x03, 0x48, 0x00, 0x90, 0x83, 0xA8,
                0x03, 0x48, 0x00, 0x44, 0xD5, 0x00, 0x01, 0xE0, 0x83, 0x10, 0x01, 0xFC, 0x82, 0x00, 0x01, 0xE0, 0x83,
                0x10, 0x01, 0xE0, 0x82, 0x00, 0x01, 0x20, 0x83, 0x50, 0x01, 0x90, 0x82, 0x00, 0x01, 0xFC, 0x83, 0x10,
                0x01, 0xE0, 0xE7, 0x00, 0x84, 0x01, 0x83, 0x00, 0x83, 0x01, 0x83, 0x00, 0x84, 0x01, 0x83, 0x00, 0x01,
                0x01, 0x83, 0x00, 0x01, 0x01, 0xE4, 0x00};

        jolt_display_t expected_scr = {
                .encoding = JOLT_ENCODING_JRLE,
                .len      = sizeof( expected_scr_data ),
                .data     = expected_scr_data,
        };
        TEST_ASSERT_EQUAL_DISPLAY( &expected_scr, NULL );
        JOLT_ENTER;  // Confirm screen

        TEST_ASSERT_EQUAL_INT( 0, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "{\"exit_code\":0}", buf );
        TEST_ASSERT_BLANK_DISPLAY( NULL );
    }
    {
        /* Read back to make sure it's correct */
        char *buf;
        cJSON *json, *contacts, *contact;
        json = jolt_json_read_app();
        TEST_ASSERT_NOT_NULL( json );
        TEST_ASSERT_NOT_NULL( contacts = cJSON_Get( json, "contacts" ) );
        TEST_ASSERT_EQUAL_INT( 2, cJSON_GetArraySize( contacts ) );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 0 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Finn Mertens\",\"address\":\"dosh\"}", buf );
        free( buf );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 1 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Madam MeowMeow\",\"address\":\"Some arbitrary crypto address\"}", buf );
        free( buf );
        cJSON_Delete( json );
    }

    /* Delete first contact */
    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        char *argv[] = {"contact", "delete", "0"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, jolt_app_cmd_contact( argcount( argv ), argv ) );
        vTaskDelay( pdMS_TO_TICKS( 50 ) );

        uint8_t expected_scr_data[] = {
                0x05, 0x20, 0xF8, 0x20, 0x00, 0xC0, 0x83, 0xA0, 0x03, 0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00,
                0x20, 0xF8, 0x20, 0x83, 0x00, 0x01, 0xF0, 0x83, 0x08, 0x03, 0x10, 0x00, 0xC0, 0x83, 0x20, 0x04, 0xC0,
                0x00, 0xE0, 0x40, 0x82, 0x20, 0x05, 0xC0, 0x00, 0x20, 0xF8, 0x20, 0x82, 0x00, 0x83, 0xA0, 0x03, 0xC0,
                0x00, 0xC0, 0x83, 0x20, 0x06, 0x00, 0x20, 0xF8, 0x20, 0x00, 0x40, 0x83, 0xA0, 0x01, 0x20, 0xC0, 0x00,
                0x07, 0x08, 0x09, 0xCA, 0x48, 0x49, 0x4A, 0x8A, 0x82, 0x0A, 0x01, 0x08, 0x84, 0x0A, 0x05, 0x49, 0xC8,
                0x08, 0x09, 0x0A, 0x83, 0x08, 0x01, 0x09, 0x82, 0x0A, 0x04, 0xCA, 0x09, 0x08, 0x09, 0x83, 0x0A, 0x03,
                0x09, 0x08, 0x0B, 0x83, 0x08, 0x01, 0x0B, 0x82, 0x08, 0x04, 0x09, 0x0A, 0x08, 0x09, 0x83, 0x0A, 0x03,
                0x0B, 0x08, 0x09, 0x83, 0x0A, 0x05, 0xC8, 0x08, 0x09, 0x0A, 0x08, 0x84, 0x0A, 0x01, 0x09, 0x85, 0x08,
                0x01, 0xC8, 0x82, 0x08, 0x01, 0x88, 0xB7, 0x08, 0x82, 0x00, 0x01, 0x9F, 0x83, 0x10, 0x03, 0x8F, 0x00,
                0x0E, 0x83, 0x15, 0x07, 0x16, 0x00, 0x10, 0x1F, 0x10, 0x00, 0x0E, 0x83, 0x15, 0x08, 0x16, 0x00, 0x01,
                0x0F, 0x11, 0x00, 0x0E, 0x15, 0x82, 0x95, 0x02, 0x96, 0x80, 0x82, 0x00, 0x01, 0x8E, 0x83, 0x11, 0x02,
                0x00, 0x0E, 0x83, 0x11, 0x04, 0x0E, 0x00, 0x1F, 0x02, 0x82, 0x01, 0x07, 0x1E, 0x00, 0x81, 0x0F, 0x11,
                0x00, 0x88, 0x83, 0x15, 0x03, 0x1E, 0x00, 0x0E, 0x83, 0x11, 0x06, 0x00, 0x01, 0x0F, 0x11, 0x00, 0x88,
                0xB9, 0x00, 0x07, 0x3F, 0x02, 0x04, 0x08, 0x3F, 0x00, 0x10, 0x83, 0x2A, 0x09, 0x3C, 0x00, 0x3E, 0x02,
                0x0C, 0x02, 0x3C, 0x00, 0x1C, 0x83, 0x2A, 0x03, 0x2C, 0x00, 0x11, 0x83, 0x00, 0x01, 0x3F, 0x83, 0x04,
                0x07, 0x00, 0x22, 0x3E, 0x20, 0x00, 0x3E, 0x04, 0x82, 0x02, 0x04, 0x3C, 0x00, 0x3E, 0x04, 0x82, 0x02,
                0x01, 0x3C, 0x83, 0x00, 0x07, 0x3F, 0x01, 0x06, 0x01, 0x3F, 0x00, 0x1C, 0x83, 0x2A, 0x04, 0x2C, 0x00,
                0x3E, 0x04, 0x82, 0x02, 0x07, 0x04, 0x00, 0x02, 0x1F, 0x22, 0x00, 0x1C, 0x83, 0x2A, 0x04, 0x2C, 0x00,
                0x3E, 0x04, 0x82, 0x02, 0x03, 0x3C, 0x00, 0x24, 0x83, 0x2A, 0x01, 0x12, 0xA6, 0x00, 0x01, 0x7E, 0x83,
                0x09, 0x03, 0x7E, 0x00, 0x38, 0x82, 0x44, 0x04, 0x48, 0x7F, 0x00, 0x38, 0x82, 0x44, 0x05, 0x48, 0x7F,
                0x00, 0x7C, 0x08, 0x82, 0x04, 0x03, 0x08, 0x00, 0x38, 0x83, 0x54, 0x03, 0x58, 0x00, 0x48, 0x83, 0x54,
                0x03, 0x24, 0x00, 0x48, 0x83, 0x54, 0x03, 0x24, 0x00, 0x22, 0xD5, 0x00, 0x01, 0x70, 0x83, 0x88, 0x01,
                0xFE, 0x82, 0x00, 0x01, 0x70, 0x83, 0x88, 0x01, 0x70, 0x82, 0x00, 0x01, 0x90, 0x83, 0xA8, 0x01, 0x48,
                0x82, 0x00, 0x01, 0xFE, 0x83, 0x08, 0x01, 0xF0, 0xFF, 0x00, 0xFF, 0x00, 0xE6, 0x00};
        jolt_display_t expected_scr = {
                .encoding = JOLT_ENCODING_JRLE,
                .len      = sizeof( expected_scr_data ),
                .data     = expected_scr_data,
        };
        TEST_ASSERT_EQUAL_DISPLAY( &expected_scr, NULL );
        JOLT_ENTER;  // Confirm screen

        TEST_ASSERT_EQUAL_INT( 0, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "{\"exit_code\":0}", buf );
        TEST_ASSERT_BLANK_DISPLAY( NULL );
    }
    {
        /* Read back to make sure it's correct */
        char *buf;
        cJSON *json, *contacts, *contact;
        json = jolt_json_read_app();
        TEST_ASSERT_NOT_NULL( json );
        TEST_ASSERT_NOT_NULL( contacts = cJSON_Get( json, "contacts" ) );
        TEST_ASSERT_EQUAL_INT( 1, cJSON_GetArraySize( contacts ) );
        TEST_ASSERT_NOT_NULL( contact = cJSON_GetArrayItem( contacts, 0 ) );
        TEST_ASSERT_NOT_NULL( buf = cJSON_PrintUnformatted( contact ) );
        TEST_ASSERT_EQUAL_STRING( "{\"name\":\"Madam MeowMeow\",\"address\":\"Some arbitrary crypto address\"}", buf );
        free( buf );
        cJSON_Delete( json );
    }

    jolt_json_del_app();
}
