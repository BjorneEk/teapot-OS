#ifndef GRAPHICS_H
#define GRAPHICS_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#include "../drivers/include/vga.h"
#include "font.h"
#include "color.h"

#define STATUS_BAR_HEIGHT 11
#define STATUS_BAR_KEY_WIDTH 54
#define STATUS_BAR_OS_NAME_WIDTH 56
#define STATUS_BAR_MESSAGE_WIDTH (VGA_WIDTH - (STATUS_BAR_KEY_WIDTH + STATUS_BAR_OS_NAME_WIDTH + 4))

typedef struct point {
	int32_t x;
	int32_t y;
} point_t;

#define draw_line(x1, y1, x2, y2, c) memset_line(((VGA_MEM+x1)+(VGA_WIDTH * y1)), x2 - x1, y2 - y1, c)

void set_color(color_t color);

color_t get_color(uint16_t x, uint16_t y);

void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, color_t clr);

void draw_char(int32_t x, int32_t y, char c, color_t clr);

///
/// draw a string to the screen.
/// use \n for newline
///
uint8_t * draw_string(int32_t x, int32_t y, char * str, color_t clr);

void set_last_key(char * key);
void set_last_key_with_trailing(char * key, char c);
void set_os_name(char * name);
void display_mouse(char * desc, char * msg);

void refresh_cursor(int32_t x, int32_t y);

#endif /* GRAPHICS_H */
