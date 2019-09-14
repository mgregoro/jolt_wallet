#include "stdio.h"
#include "esp_vfs_dev.h"
#include "syscore/cli_helpers.h"
#include "syscore/filesystem.h"
#include "jolt_helpers.h"


int jolt_cmd_touch(int argc, char** argv) {
    int return_code;
    uint8_t files_created = 0;

    /* Input Argument Check */
    if( argc < 2 ) EXIT_PRINT(-1, "Specify at least 1 filename");

    for(uint8_t i=1; i<argc; i++){
        FILE *f = NULL;
        char *fn = BREAK_IF_NULL(jolt_fs_parse(argv[i], NULL));
        f = fopen(fn, "wb");
        if( NULL != f ) jolt_h_fn_home_refresh(fn);
        SAFE_FREE(fn);
        if( NULL == f ) break;
        files_created++;
        SAFE_CLOSE(f);
    }

    if( files_created != argc - 1 ) EXIT(-1);

    EXIT(0); /* Success */

exit:
    return return_code;
}


