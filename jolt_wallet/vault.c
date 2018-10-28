/* Jolt Wallet - Open Source Cryptocurrency Hardware Wallet
 Copyright (C) 2018  Brian Pugh, James Coxon, Michael Smaili
 https://www.joltwallet.com/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esp_system.h>
#include "esp_log.h"
#include "sodium.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "jolttypes.h"
#include "bipmnemonic.h"
#include "jolt_helpers.h"
#include "globals.h"
#include "vault.h"
#include "hal/storage/storage.h"
#include "jolt_gui/jolt_gui.h"

static const char* TAG = "vault";
static const char* TITLE = "Vault Access";

static uint512_t master_seed;
static lv_action_t back_cb;
static lv_action_t enter_cb;


vault_t *vault = NULL;
/* The following semaphores are not part of the vault object so we can use
 * sodium_malloc() */
static SemaphoreHandle_t vault_sem; // Used for general vault access
static SemaphoreHandle_t vault_watchdog_sem; // Used to kick the dog


void vault_sem_take() {
    /* Takes Vault semaphore; restarts device if timesout during take. */
    if( !xSemaphoreTake(vault_sem, pdMS_TO_TICKS(CONFIG_JOLT_TIMEOUT_TIMEOUT_MS) ) ) {
        // Timed out trying to take the semaphore; reset the device
        // And let the bootloader wipe the RAM
        ESP_LOGI(TAG, "Failed taking vault semaphore. Rebooting...");
        esp_restart();
    }
}

void vault_sem_give() {
    xSemaphoreGive(vault_sem);
}

static void vault_watchdog_task() {
    /* Daemon-like task to wipe vault after a configurable timeout.
     * Should be given very high priority to prevent deadlocks. */
	for(;;) {
        if( xSemaphoreTake( vault_watchdog_sem, 
				pdMS_TO_TICKS(CONFIG_JOLT_DEFAULT_TIMEOUT_S * 1000)) ) {
            // Command to reset the private node watchdog;
            // Note, vault_sem is probably taken if in here
            // Do Nothing
        }
        else {
            // WatchDog timeout; wipe the private node
            vault_clear();
        }
	}
}

bool vault_setup() {
    /* Creates the private key object and the watchdog task to monitor it.
     * Also checks to see if there is a stored secret or not.
     *
     * Returns True if a secret (mnemonic) has been previously setup.
     * Returns False if no secret (mnemonic) has been setup.*/
    vault = sodium_malloc(sizeof(vault_t));
    if( NULL==vault ){
        ESP_LOGE(TAG, "Unable to allocate space for the Vault");
        esp_restart();
    }
    sodium_mprotect_readwrite(vault);
    sodium_memzero(vault, sizeof(vault_t));
    sodium_mprotect_readonly(vault);
    vault_sem = xSemaphoreCreateMutex();
    vault_watchdog_sem = xSemaphoreCreateBinary();
    // todo: tweak this memory value
    xTaskCreate(vault_watchdog_task, "VaultWatchDog", 20000, NULL, 16, NULL);

    // Checks if stored secret exists
    return storage_exists_mnemonic();
}

void vault_clear() {
    /* Clears the Vault struct.
     * Does NOT clear the following so that the node can be easily restored:
     *      * purpose
     *      * coin_type
     *      * bip32_key
     */
    if(vault->valid) {
        vault_sem_take();
        ESP_LOGI(TAG, "Clearing Vault.");
        sodium_mprotect_readwrite(vault);
        vault->valid = false;
        sodium_memzero(&(vault->node), sizeof(hd_node_t));
        sodium_mprotect_readonly(vault);
        ESP_LOGI(TAG, "Clearing Vault Complete.");
        vault_sem_give();
    }
}

static lv_action_t cb_vault_set_success = NULL;

static lv_action_t pin_success_cb() {
    /* jolt_gui_store.tmp.mnemonic_bin is populated
     */
    CONFIDENTIAL char passphrase[BM_PASSPHRASE_BUF_LEN] = { 0 };
    CONFIDENTIAL char mnemonic[BM_MNEMONIC_BUF_LEN] = { 0 };
    CONFIDENTIAL uint512_t master_seed;

    // todo: get passphrase here
    strlcpy(passphrase, "", sizeof(passphrase)); // dummy placeholder
    
    bm_bin_to_mnemonic(mnemonic, sizeof(mnemonic),
            jolt_gui_store.tmp.mnemonic_bin, 256);
    // this is a computationally intense operation
    bm_mnemonic_to_master_seed(master_seed, mnemonic, passphrase);

    vault_sem_take();
    bm_master_seed_to_node(&(vault->node), master_seed, vault->bip32_key,
            2, vault->purpose, vault->coin_type);
    vault->valid = true;
    vault_sem_give();

    /* Clear all confidential variables */
    sodium_memzero(jolt_gui_store.tmp.mnemonic_bin,
            sizeof(jolt_gui_store.tmp.mnemonic_bin));
    sodium_memzero(passphrase, sizeof(passphrase));
    sodium_memzero(mnemonic, sizeof(mnemonic));
    sodium_memzero(master_seed, sizeof(master_seed));

    if( NULL != cb_vault_set_success ) {
        cb_vault_set_success(NULL);
        cb_vault_set_success = NULL;
    }

    return 0;
}

void vault_set(uint32_t purpose, uint32_t coin_type, const char *bip32_key,
        lv_action_t failure_cb, lv_action_t success_cb) {
    /* 
     * To only be called before launching an app, or when changing firmware
     * settings.
     * Since this *may* prompt the user for a PIN, it must be non-blocking
     * to agree with the GUI.
     *
     * If the vault is successfully set, the success callback will be executed.
     * On failure to set the vault, the failure callback will be executed.
     *
     * SIGNATURE COMPLETED; CONTENTS INCOMPLETE
     */
    //
    // Inside this function (really inside get_master_seed()),
    // the GUI is invoked for PIN and Passphrase.
    CONFIDENTIAL uint512_t master_seed;

    // todo: check if vault is valid and has same params

    vault_sem_take();
    sodium_mprotect_readwrite(vault);
    vault->valid = false; // probably redundant
    vault->purpose = purpose;
    vault->coin_type = coin_type;
    strlcpy( vault->bip32_key, bip32_key, sizeof(vault->bip32_key) );
    sodium_mprotect_readonly(vault);
    vault_sem_give();

    jolt_gui_scr_pin_create(failure_cb, success_cb);
    return;
#if 0
    bool res;

    // Inside get_master_seed(), PIN and passphrase are prompted for
    if(!get_master_seed(master_seed)) {
        ESP_LOGI(TAG, "Failed to retrieve master seed");
        res = false;
        goto exit;
    }
    strlcpy( vault->bip32_key, bip32_key, sizeof(vault->bip32_key) );
    vault->purpose = purpose;
    vault->coin_type = coin_type;
    bm_master_seed_to_node(&(vault->node), master_seed, vault->bip32_key,
            2, vault->purpose, vault->coin_type);
    vault->valid = true;
    res = true;

exit:
    sodium_memzero(master_seed, sizeof(master_seed));
    return res;
#endif
}

bool vault_refresh() {
    /* Kicks dog if vault is valid.
     * Repopulates node (therefore prompting user for PIN otherwise
     *
     * To be called within an app right before a private key is to be used.
     *
     * Returns true on success,
     * false if user cancels (if node needs restored)
     */
    bool res;
    vault_sem_take();
    ESP_LOGI(TAG, "Refreshing Vault");
    if( vault->valid ) {
        // Kick the dog
        ESP_LOGI(TAG, "Vault is valid; kicking the dog.");
        xSemaphoreGive(vault_watchdog_sem);
        vault_sem_give();
        return true;
    }
    else {
        // Give up semaphore while prompt using for PIN/Passphrase
        vault_sem_give();
        ESP_LOGI(TAG, "Vault is invalid, prompting user for PIN.");
        CONFIDENTIAL uint512_t master_seed;
        // Inside get_master_seed(), PIN and passphrase are prompted for
#if 0
        if(!get_master_seed(master_seed)) {
            return false;
        }
#endif

        vault_sem_take();
        // Kick the dog first to avoid a potential race condition where the 
        // watchdog resets a just-set node.
        xSemaphoreGive(vault_watchdog_sem);

        bm_master_seed_to_node(&(vault->node), master_seed, vault->bip32_key,
            2, vault->purpose, vault->coin_type);
        vault->valid = true;
        vault_sem_give();
        sodium_memzero(master_seed, sizeof(master_seed));
        return true;
    }
}

#if 0
//CONFIDENTIAL static uint512_t master_seed = { 0 };
static void get_master_seed(lv_action_t failure_cb, lv_action_t success_cb) {
    CONFIDENTIAL char passphrase[BM_PASSPHRASE_BUF_LEN] = "";
    CONFIDENTIAL char mnemonic[BM_MNEMONIC_BUF_LEN];
}
#endif

#if 0
static bool get_master_seed(uint512_t master_seed) {
    // Command-level function to get the user's mnemonic
    // WILL prompt user for PIN and/or passphrase
    //
    // Internally saves/restores display since PIN/Passphrase prompt
    // overwrites screen buffer.
    //
    // Returns True if user successfully entered PIN/Passphrase
    // Returns False if user cancels
    bool res;
    CONFIDENTIAL char passphrase[BM_PASSPHRASE_BUF_LEN] = "";
    CONFIDENTIAL char mnemonic[BM_MNEMONIC_BUF_LEN];
    
    // storage_get_mnemonic prompts user for PIN
    if( !storage_get_mnemonic(mnemonic, sizeof(mnemonic)) ) {
        res = false;
        goto exit;
    }

    // todo: fetch passphrase
    strlcpy(passphrase, "", sizeof(passphrase)); // dummy placeholder

    // Derive master seed
    res = (E_SUCCESS == bm_mnemonic_to_master_seed(master_seed, mnemonic, passphrase));

exit:
    sodium_memzero(mnemonic, sizeof(mnemonic));
    sodium_memzero(passphrase, sizeof(passphrase));

    return res;
}
#endif
