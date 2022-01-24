#ifndef GRAPHICS_H
#define GRAPHICS_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#include "../drivers/include/vga.h"
#include "font.h"
#include "color.h"

typedef struct point {
	int16_t x;
	int16_t y;
} point_t;

#define draw_line(x1, y1, x2, y2, c) memset_line(((VGA_MEM+x1)+(VGA_WIDTH * y1)), x2 - x1, y2 - y1, c)

void set_color(color_t color);

color_t get_color(uint16_t x, uint16_t y);

void draw_triangle(point_t p1, point_t p2, point_t p3, color_t clr);

void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, color_t clr);

void draw_char(int32_t x, int32_t y, char c, color_t clr);


///
/// draw a string to the screen.
/// use \n for newline
///
void draw_string(int32_t x, int32_t y, char * str, color_t clr);

#endif /* GRAPHICS_H */
