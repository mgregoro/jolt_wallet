#ifndef JELFLOADER_H__
#define JELFLOADER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "jolttypes.h"
#include "sodium.h"

#define LOADER_FD_T FILE *

#ifndef CONFIG_JOLT_APP_SIG_CHECK_EN
#define CONFIG_JOLT_APP_SIG_CHECK_EN 1
#endif

#ifndef CONFIG_JOLT_APP_KEY_DEFAULT
#define CONFIG_JOLT_APP_KEY_DEFAULT "03a107bff3ce10be1d70dd18e74bc09967e4d6309ba50d5f1ddc8664125531b8"
#endif


typedef struct {
    const void **exported;            /*!< Pointer to exported symbols array */
    unsigned int exported_size; /*!< Elements on exported symbol array */
} jelfLoaderEnv_t;

/* LRU cache to read larger chunks of data from flash to memory */
#if CONFIG_JELFLOADER_CACHE_LOCALITY
typedef struct jelfLoader_locality_cache_t {
    char *data;
    uint8_t age; // lower number means more recently used
    size_t offset;
    bool valid;
} jelfLoader_locality_cache_t;
#endif

/* Singly Linked List Used to cache sections needed at runtime */
typedef struct jelfLoaderSection_t {
    void *data;
    uint16_t secIdx;
    size_t size;
    off_t relSecIdx;                  
    struct jelfLoaderSection_t* next; // Next Header in Singly Linked List
} jelfLoaderSection_t;

typedef struct jelfLoaderContext_t {
    LOADER_FD_T fd;
    void* exec;
    const jelfLoaderEnv_t *env;

    uint16_t entry_index;
    uint16_t e_shnum;
    off_t e_shoff;

    size_t symtab_count;
    off_t symtab_offset;

    jelfLoaderSection_t *section; // First element of singly linked list sections.

    /* Coin Derivation Data */
    uint32_t coin_purpose;
    uint32_t coin_path;
    char bip32_key[33];

    /* Data Structs For Checking App Signature */
#if CONFIG_JOLT_APP_SIG_CHECK_EN
    crypto_hash_sha512_state *hs;
    uint8_t hash[BIN_512];
    uint8_t app_public_key[BIN_256];
    uint8_t app_signature[BIN_512];
#endif

#if CONFIG_JELFLOADER_CACHE_LOCALITY
    jelfLoader_locality_cache_t locality_cache[CONFIG_JELFLOADER_CACHE_LOCALITY_CHUNK_N];
#endif
} jelfLoaderContext_t;


int jelfLoaderRun(jelfLoaderContext_t *ctx, int argc, char **argv);
int jelfLoaderRunAppMain(jelfLoaderContext_t *ctx);
int jelfLoaderRunConsole(jelfLoaderContext_t *ctx, int argc, char **argv);

jelfLoaderContext_t *jelfLoaderInit(LOADER_FD_T fd, const char *name, const jelfLoaderEnv_t *env);
jelfLoaderContext_t *jelfLoaderLoad(jelfLoaderContext_t *ctx);
jelfLoaderContext_t *jelfLoaderRelocate(jelfLoaderContext_t *ctx);

void jelfLoaderFree( jelfLoaderContext_t *ctx );

bool jelfLoaderSigCheck(jelfLoaderContext_t *ctx); // can only be called after relocating
uint8_t *jelfLoaderGetHash(jelfLoaderContext_t *ctx); // return hash (in bytes, 64 long)

#if CONFIG_JELFLOADER_PROFILER_EN
/* Sets all profiler variables to 0 */
void jelfLoaderProfilerReset();

/* Prints the profiler results to uart console */
void jelfLoaderProfilerPrint();
#endif // CONFIG_ELFLOADER_PROFILER_EN

#endif
