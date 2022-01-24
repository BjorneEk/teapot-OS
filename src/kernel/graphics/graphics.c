#include "graphics.h"



color_t DRAW_COLOR = (color_t){.r=0b111, .g=0b111, .b=0b11};

void set_color(color_t color) {
	DRAW_COLOR = color;
}

color_t get_color(uint16_t x, uint16_t y) {
	return (color_t) { .c = get_pixel(x, y)};
}

void draw_triangle(point_t p1, point_t p2, point_t p3, color_t clr) {
	draw_line(p1.x, p1.y, p2.x, p2.y, clr.c);
	draw_line(p1.x, p1.y, p3.x, p3.y, clr.c);
	draw_line(p3.x, p3.y, p2.x, p2.y, clr.c);
}

void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, color_t clr) {
	memset_rect(((VGA_MEM+x)+(VGA_WIDTH * y)), w, h, clr.c);
}
