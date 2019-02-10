#include "jolt_gui/jolt_gui.h"
#include "hal/storage/storage.h"

static lv_res_t factory_reset_back( lv_obj_t *btn ) {
    jolt_gui_scr_del();
    return LV_RES_INV;
}

static lv_res_t factory_reset_enter( lv_obj_t *btn ) {
    storage_factory_reset( true, NULL );
    return LV_RES_OK;
}

lv_res_t menu_factory_reset_create(lv_obj_t *btn) {
    lv_obj_t *scr = jolt_gui_scr_menu_create(gettext(JOLT_TEXT_FACTORY_RESET));
    jolt_gui_scr_menu_add(scr, NULL, gettext(JOLT_TEXT_NO), factory_reset_back);
    jolt_gui_scr_menu_add(scr, NULL, gettext(JOLT_TEXT_YES), factory_reset_enter);
    return LV_RES_OK;
}
