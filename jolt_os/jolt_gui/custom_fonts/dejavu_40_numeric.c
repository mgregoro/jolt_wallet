
#include "../lv_misc/lv_font.h"

#if USE_LV_FONT_DEJAVU_40_NUMERIC != 0  /*Can be enabled in lv_conf.h*/

/***********************************************************************************
 * DejaVuSans.ttf 40 px Font in U+0020 ( ) .. U+007e (~)  range with 1 bpp
***********************************************************************************/

/*Store the image of the letters (glyph)*/
static const uint8_t lv_font_dejavu_40_glyph_bitmap[] = {
    /*Unicode: U+0030 (0) , Width: 17 */
    0x03, 0xe0, 0x00,  //.....+%@@@%+.....
    0x0f, 0xf8, 0x00,  //...+@@@@@@@@@....
    0x1f, 0xfc, 0x00,  //...@@@@@@@@@@@...
    0x3c, 0x1e, 0x00,  //..@@@@+...+@@@@..
    0x78, 0x0f, 0x00,  //.%@@@.......@@@+.
    0x70, 0x07, 0x00,  //.@@@+.......+@@@.
    0x70, 0x07, 0x00,  //.@@@.........@@@.
    0xf0, 0x07, 0x80,  //%@@%.........%@@+
    0xe0, 0x03, 0x80,  //%@@+.........+@@%
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //%@@+.........+@@%
    0xf0, 0x07, 0x80,  //%@@%.........%@@%
    0x70, 0x07, 0x00,  //+@@@.........@@@.
    0x70, 0x07, 0x00,  //.@@@+.......+@@@.
    0x78, 0x0f, 0x00,  //.%@@@.......@@@+.
    0x3c, 0x1e, 0x00,  //..@@@@+...+@@@@..
    0x1f, 0xfc, 0x00,  //...@@@@@@@@@@@...
    0x0f, 0xf8, 0x00,  //...+@@@@@@@@@....
    0x03, 0xe0, 0x00,  //.....+%@@@%+.....


    /*Unicode: U+0031 (1) , Width: 14 */
    0x1f, 0x80,  //..+%@@@@@.....
    0xff, 0x80,  //@@@@@@@@@.....
    0xff, 0x80,  //@@@@@@@@@.....
    0xe3, 0x80,  //@%%+..@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x03, 0x80,  //......@@@.....
    0x7f, 0xfc,  //.@@@@@@@@@@@@@
    0x7f, 0xfc,  //.@@@@@@@@@@@@@
    0x7f, 0xfc,  //.@@@@@@@@@@@@@


    /*Unicode: U+0032 (2) , Width: 17 */
    0x3f, 0xe0, 0x00,  //.+%%@@@@@@%+.....
    0xff, 0xf8, 0x00,  //@@@@@@@@@@@@@....
    0xff, 0xfc, 0x00,  //@@@@@@@@@@@@@@+..
    0xf0, 0x3e, 0x00,  //@@@%+.....%@@@@..
    0x80, 0x0f, 0x00,  //@+.........+@@@%.
    0x00, 0x07, 0x00,  //............+@@@.
    0x00, 0x07, 0x00,  //.............@@@.
    0x00, 0x07, 0x00,  //.............@@@.
    0x00, 0x07, 0x00,  //.............@@@.
    0x00, 0x0f, 0x00,  //............%@@%.
    0x00, 0x0e, 0x00,  //............@@@..
    0x00, 0x1c, 0x00,  //...........@@@+..
    0x00, 0x3c, 0x00,  //..........@@@%...
    0x00, 0x78, 0x00,  //.........@@@@....
    0x00, 0xf0, 0x00,  //........@@@@.....
    0x01, 0xe0, 0x00,  //.......@@@@......
    0x03, 0xc0, 0x00,  //......@@@@.......
    0x07, 0x80, 0x00,  //.....@@@@........
    0x0f, 0x00, 0x00,  //...+@@@@.........
    0x1e, 0x00, 0x00,  //..+@@@@..........
    0x3c, 0x00, 0x00,  //.+@@@@...........
    0x78, 0x00, 0x00,  //+@@@@............
    0xff, 0xff, 0x00,  //@@@@@@@@@@@@@@@@.
    0xff, 0xff, 0x00,  //@@@@@@@@@@@@@@@@.
    0xff, 0xff, 0x00,  //@@@@@@@@@@@@@@@@.


    /*Unicode: U+0033 (3) , Width: 16 */
    0x1f, 0xe0,  //..+%@@@@@@%.....
    0x7f, 0xf8,  //.@@@@@@@@@@@%...
    0x7f, 0xfc,  //.@@@@@@@@@@@@%..
    0x60, 0x3c,  //.@%+.....+@@@@+.
    0x00, 0x1e,  //...........%@@%.
    0x00, 0x0e,  //............@@@.
    0x00, 0x0e,  //............@@@.
    0x00, 0x0e,  //............@@@.
    0x00, 0x1c,  //...........%@@+.
    0x00, 0x3c,  //.........+@@@@..
    0x0f, 0xf8,  //....@@@@@@@@%...
    0x0f, 0xf0,  //....@@@@@@@%....
    0x0f, 0xf8,  //....@@@@@@@@@+..
    0x00, 0x3e,  //.........+%@@@%.
    0x00, 0x0e,  //...........+@@@+
    0x00, 0x07,  //............+@@%
    0x00, 0x07,  //.............@@@
    0x00, 0x07,  //.............@@@
    0x00, 0x07,  //.............@@@
    0x00, 0x0f,  //............%@@%
    0x00, 0x0e,  //...........+@@@+
    0xc0, 0x3e,  //@%+......+%@@@@.
    0xff, 0xfc,  //@@@@@@@@@@@@@@..
    0xff, 0xf8,  //@@@@@@@@@@@@%...
    0x3f, 0xc0,  //.+%@@@@@@%+.....


    /*Unicode: U+0034 (4) , Width: 19 */
    0x00, 0x3e, 0x00,  //..........%@@@@....
    0x00, 0x3e, 0x00,  //.........+@@@@@....
    0x00, 0x7e, 0x00,  //.........@@@@@@....
    0x00, 0xee, 0x00,  //........%@@.@@@....
    0x00, 0xce, 0x00,  //.......+@@+.@@@....
    0x01, 0xce, 0x00,  //.......@@@..@@@....
    0x03, 0x8e, 0x00,  //......%@@...@@@....
    0x03, 0x0e, 0x00,  //.....+@@+...@@@....
    0x07, 0x0e, 0x00,  //.....@@@....@@@....
    0x0e, 0x0e, 0x00,  //....@@@.....@@@....
    0x0c, 0x0e, 0x00,  //...+@@+.....@@@....
    0x1c, 0x0e, 0x00,  //...@@@......@@@....
    0x38, 0x0e, 0x00,  //..@@@.......@@@....
    0x30, 0x0e, 0x00,  //.+@@+.......@@@....
    0x70, 0x0e, 0x00,  //.@@@........@@@....
    0xe0, 0x0e, 0x00,  //@@@.........@@@....
    0xff, 0xff, 0xe0,  //@@@@@@@@@@@@@@@@@@@
    0xff, 0xff, 0xe0,  //@@@@@@@@@@@@@@@@@@@
    0xff, 0xff, 0xe0,  //@@@@@@@@@@@@@@@@@@@
    0x00, 0x0e, 0x00,  //............@@@....
    0x00, 0x0e, 0x00,  //............@@@....
    0x00, 0x0e, 0x00,  //............@@@....
    0x00, 0x0e, 0x00,  //............@@@....
    0x00, 0x0e, 0x00,  //............@@@....
    0x00, 0x0e, 0x00,  //............@@@....


    /*Unicode: U+0035 (5) , Width: 16 */
    0x7f, 0xfc,  //.@@@@@@@@@@@@@..
    0x7f, 0xfc,  //.@@@@@@@@@@@@@..
    0x7f, 0xfc,  //.@@@@@@@@@@@@@..
    0x70, 0x00,  //.@@@............
    0x70, 0x00,  //.@@@............
    0x70, 0x00,  //.@@@............
    0x70, 0x00,  //.@@@............
    0x70, 0x00,  //.@@@............
    0x70, 0x00,  //.@@@............
    0x7f, 0xc0,  //.@@@%@@@@%+.....
    0x7f, 0xf8,  //.@@@@@@@@@@@%...
    0x7f, 0xfc,  //.@@@@@@@@@@@@@..
    0x60, 0x3e,  //.@%+.....+@@@@%.
    0x00, 0x1e,  //...........%@@@+
    0x00, 0x0f,  //............%@@%
    0x00, 0x07,  //.............@@@
    0x00, 0x07,  //.............@@@
    0x00, 0x07,  //.............@@@
    0x00, 0x07,  //.............@@@
    0x00, 0x0f,  //............%@@%
    0x00, 0x1e,  //...........%@@@+
    0xc0, 0x3e,  //@%+......+@@@@%.
    0xff, 0xfc,  //@@@@@@@@@@@@@@..
    0xff, 0xf8,  //@@@@@@@@@@@@%...
    0x3f, 0xc0,  //.+%@@@@@@%+.....


    /*Unicode: U+0036 (6) , Width: 17 */
    0x01, 0xf8, 0x00,  //......+%@@@@%+...
    0x07, 0xfe, 0x00,  //....+@@@@@@@@@@..
    0x0f, 0xfe, 0x00,  //...+@@@@@@@@@@@..
    0x1e, 0x06, 0x00,  //..+@@@@+....+%@..
    0x3c, 0x00, 0x00,  //..@@@%...........
    0x78, 0x00, 0x00,  //.%@@@............
    0x70, 0x00, 0x00,  //.@@@+............
    0x70, 0x00, 0x00,  //+@@@.............
    0xf0, 0x00, 0x00,  //%@@%.............
    0xe3, 0xf0, 0x00,  //@@@+..%@@@@%+....
    0xe7, 0xfc, 0x00,  //@@@.+@@@@@@@@@...
    0xef, 0xfe, 0x00,  //@@@+@@@@@@@@@@@..
    0xfe, 0x1f, 0x00,  //@@@@@@%....%@@@@.
    0xf8, 0x07, 0x00,  //@@@@@+......+@@@+
    0xf8, 0x07, 0x80,  //@@@@%........%@@%
    0xf0, 0x03, 0x80,  //@@@@..........@@@
    0xf0, 0x03, 0x80,  //%@@@..........@@@
    0x70, 0x03, 0x80,  //+@@@..........@@@
    0x70, 0x03, 0x80,  //.@@@..........@@@
    0x78, 0x07, 0x80,  //.@@@%........%@@%
    0x38, 0x07, 0x00,  //.+@@@+......+@@@+
    0x3e, 0x1f, 0x00,  //..@@@@%....%@@@@.
    0x1f, 0xfe, 0x00,  //...@@@@@@@@@@@@..
    0x0f, 0xfc, 0x00,  //....@@@@@@@@@%...
    0x03, 0xf0, 0x00,  //.....+%@@@@%+....


    /*Unicode: U+0037 (7) , Width: 16 */
    0xff, 0xff,  //@@@@@@@@@@@@@@@@
    0xff, 0xff,  //@@@@@@@@@@@@@@@@
    0xff, 0xff,  //@@@@@@@@@@@@@@@%
    0x00, 0x0e,  //............@@@.
    0x00, 0x1e,  //...........%@@%.
    0x00, 0x1c,  //...........@@@+.
    0x00, 0x1c,  //..........+@@@..
    0x00, 0x38,  //..........@@@+..
    0x00, 0x38,  //..........@@@...
    0x00, 0x78,  //.........%@@%...
    0x00, 0x70,  //.........@@@....
    0x00, 0x70,  //........+@@@....
    0x00, 0xe0,  //........@@@+....
    0x00, 0xe0,  //........@@@.....
    0x01, 0xe0,  //.......%@@%.....
    0x01, 0xc0,  //.......@@@......
    0x01, 0xc0,  //......+@@%......
    0x03, 0x80,  //......@@@+......
    0x03, 0x80,  //.....+@@@.......
    0x07, 0x80,  //.....%@@%.......
    0x07, 0x00,  //.....@@@........
    0x0f, 0x00,  //....%@@%........
    0x0e, 0x00,  //....@@@+........
    0x0e, 0x00,  //...+@@@.........
    0x1c, 0x00,  //...@@@+.........


    /*Unicode: U+0038 (8) , Width: 17 */
    0x07, 0xf0, 0x00,  //.....%@@@@@%.....
    0x1f, 0xfc, 0x00,  //...%@@@@@@@@@%...
    0x3f, 0xfe, 0x00,  //..@@@@@@@@@@@@@..
    0x3c, 0x1e, 0x00,  //.+@@@@+...+@@@@+.
    0x78, 0x0f, 0x00,  //.@@@%.......%@@@.
    0x70, 0x07, 0x00,  //.@@@.........@@@.
    0x70, 0x07, 0x00,  //.@@@.........@@@.
    0x70, 0x07, 0x00,  //.@@@.........@@@.
    0x38, 0x0e, 0x00,  //.+@@%.......%@@+.
    0x3c, 0x1e, 0x00,  //..@@@@+...+@@@@..
    0x1f, 0xfc, 0x00,  //...%@@@@@@@@@%...
    0x0f, 0xf8, 0x00,  //....%@@@@@@@%....
    0x1f, 0xfc, 0x00,  //..+@@@@@@@@@@@+..
    0x7c, 0x1f, 0x00,  //.%@@@%.....%@@@%.
    0x70, 0x07, 0x00,  //.@@@.........@@@.
    0xe0, 0x03, 0x80,  //%@@+.........+@@%
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@...........@@@
    0xe0, 0x03, 0x80,  //@@@+.........+@@@
    0xf0, 0x07, 0x80,  //+@@@.........@@@+
    0x7c, 0x1f, 0x00,  //.@@@@%.....%@@@@.
    0x3f, 0xfe, 0x00,  //.+@@@@@@@@@@@@@+.
    0x1f, 0xfc, 0x00,  //..+@@@@@@@@@@@+..
    0x07, 0xf0, 0x00,  //....+%@@@@@%+....

    /*Unicode: U+0039 (9) , Width: 17 */
    0x07, 0xe0, 0x00,  //....+%@@@@%+.....
    0x1f, 0xf8, 0x00,  //...%@@@@@@@@@....
    0x3f, 0xfc, 0x00,  //..@@@@@@@@@@@@...
    0x7c, 0x3e, 0x00,  //.@@@@%....%@@@@..
    0x70, 0x0e, 0x00,  //+@@@+......+@@@+.
    0xf0, 0x0f, 0x00,  //%@@%........%@@@.
    0xe0, 0x07, 0x00,  //@@@..........@@@.
    0xe0, 0x07, 0x00,  //@@@..........@@@+
    0xe0, 0x07, 0x80,  //@@@..........@@@%
    0xe0, 0x07, 0x80,  //@@@..........@@@@
    0xf0, 0x0f, 0x80,  //%@@%........%@@@@
    0x70, 0x0f, 0x80,  //+@@@........@@@@@
    0x7c, 0x3f, 0x80,  //.@@@@%....%@@@@@@
    0x3f, 0xfb, 0x80,  //..@@@@@@@@@@@+@@@
    0x1f, 0xf3, 0x80,  //...@@@@@@@@@+.@@@
    0x07, 0xe3, 0x80,  //....+%@@@@%..+@@@
    0x00, 0x07, 0x80,  //.............%@@%
    0x00, 0x07, 0x00,  //.............@@@+
    0x00, 0x07, 0x00,  //............+@@@.
    0x00, 0x0f, 0x00,  //............@@@%.
    0x00, 0x1e, 0x00,  //...........%@@@..
    0x30, 0x3c, 0x00,  //..@%+....+@@@@+..
    0x3f, 0xf8, 0x00,  //..@@@@@@@@@@@+...
    0x3f, 0xf0, 0x00,  //..@@@@@@@@@@+....
    0x0f, 0xc0, 0x00,  //...+%@@@@%+......
};


/*Store the glyph descriptions*/
static const lv_font_glyph_dsc_t lv_font_dejavu_40_glyph_dsc[] = {
    {.w_px = 17,  .glyph_index = 0},   /*Unicode: U+0030 (0)*/
    {.w_px = 14,  .glyph_index = 75},   /*Unicode: U+0031 (1)*/
    {.w_px = 17,  .glyph_index = 125},   /*Unicode: U+0032 (2)*/
    {.w_px = 16,  .glyph_index = 200},   /*Unicode: U+0033 (3)*/
    {.w_px = 19,  .glyph_index = 250},  /*Unicode: U+0034 (4)*/
    {.w_px = 16,  .glyph_index = 325},  /*Unicode: U+0035 (5)*/
    {.w_px = 17,  .glyph_index = 375},  /*Unicode: U+0036 (6)*/
    {.w_px = 16,  .glyph_index = 450},  /*Unicode: U+0037 (7)*/
    {.w_px = 17,  .glyph_index = 500},  /*Unicode: U+0038 (8)*/
    {.w_px = 17,  .glyph_index = 575},  /*Unicode: U+0039 (9)*/
};

lv_font_t lv_font_dejavu_40_numeric = {
    .unicode_first = 0x30,    /*First Unicode letter in this font*/
    .unicode_last = 0x39,    /*Last Unicode letter in this font*/
    .h_px = 25,             /*Font height in pixels*/
    .glyph_bitmap = lv_font_dejavu_40_glyph_bitmap, /*Bitmap of glyphs*/
    .glyph_dsc = lv_font_dejavu_40_glyph_dsc,       /*Description of glyphs*/
    .glyph_cnt = 10,            /*Number of glyphs in the font*/
    .unicode_list = NULL,   /*Every character in the font from 'unicode_first' to 'unicode_last'*/
    .get_bitmap = lv_font_get_bitmap_continuous,    /*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_continuous,  /*Function pointer to get glyph's width*/
    .bpp = 1,               /*Bit per pixel*/
    .monospace = 0,
    .next_page = NULL,      /*Pointer to a font extension*/
};

#endif /*USE_LV_FONT_DEJAVU_40*/