

#ifndef asm
#define asm __asm__ volatile
#endif
#include "../include/vga.h"
#include "../include/ports.h"
#include "../../libc/include/math.h"
#include "../../graphics/font.h"
#include "../../graphics/cursor.h"
#include "../../graphics/color.h"
#include "../include/mouse.h"
#include "../../libc/include/malloc.h"


////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

cursor_t cursor =
{
	.img={
		{2,0,0,0,0},
		{2,2,0,0,0},
		{2,1,2,0,0},
		{2,1,1,2,0},
		{2,1,1,1,2},
		{2,1,2,2,2},
		{2,2,0,0,0}},
	.prev={
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}}
};
/**
 * position of the cursor
 **/
uint16_t cursor_x;
uint16_t cursor_y;

uint8_t * text_cursor = (uint8_t*)0xA0000;

/**
 *  video memody address of cursor
 **/
uint8_t * prev_c = (uint8_t*)0xA0000;

color_t cursor_color = (color_t){.r=0b111, .g=0b111, .b=0b11};

void vga_init_palette() {
	out_portb(VGA_PALETTE_MASK, 0xFF);
	out_portb(VGA_PALETTE_WRITE, 0);
	for (uint8_t i = 0; i < 0xFF; i++) {
		out_portb(VGA_PALETTE_DATA, (((i >> 5) & 0x07) * (256 / 8)) / 4);
		out_portb(VGA_PALETTE_DATA, (((i >> 2) & 0x07) * (256 / 8)) / 4);
		out_portb(VGA_PALETTE_DATA, (((i >> 0) & 0x03) * (256 / 8)) / 4);
	}
	out_portb(VGA_PALETTE_DATA, 0x3F);
	out_portb(VGA_PALETTE_DATA, 0x3F);
	out_portb(VGA_PALETTE_DATA, 0x3F);
}

void put_pixel(uint16_t pos_x, uint16_t pos_y, uint8_t vga_color) {
	*((VGA_MEM + pos_x) + (pos_y * VGA_HEIGHT)) = vga_color;
}

uint8_t get_pixel(uint16_t pos_x, uint16_t pos_y) {
	return *((VGA_MEM + pos_x) + (pos_y * VGA_HEIGHT));
}

/**
 *   Bresenham's line algorithm
 *   https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 **/
void memset_line(uint8_t * restrict v_mem_start, int16_t w, int16_t h, uint8_t color) {
	uint8_t * v_ram = v_mem_start;
	int32_t x0 = 0;
	int32_t y0 = 0;
	int32_t dx =  abs(w - x0);
	int32_t sx = ( x0 < w ) ? 1 : -1;
	int32_t dy = -abs(h - y0);
	int32_t sy = ( y0 < h ) ? 1 : -1;
	int32_t err = dx + dy;  /* error value e_xy */
	while (!(x0 == w && y0 == h)){  /* loop */
		*(v_ram + x0 + (y0 * 320)) = color;
		int32_t e2 = 2 * err;
		if (e2 >= dy) {/* e_xy + e_x > 0 */
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {/* e_xy + e_y < 0 */
			err += dx;
			y0 += sy;
		}
	}
}

void memset_rect(uint8_t * restrict v_mem_start, int16_t w, int16_t h, uint8_t color) {
	uint8_t * v_ram = v_mem_start;
	for (size_t y = 0; y < h * VGA_WIDTH; y += VGA_WIDTH) {
		for (size_t x = 0; x < w; x++) {
			*(v_ram + x + y) = color;
		}
	}
	update_cursor(prev_c, cursor_x, cursor_y);
}

uint8_t * memset_5x7font(uint8_t * restrict v_mem_start, uint16_t i, uint8_t color) {
	uint8_t * v_ram = v_mem_start;
	size_t x;
	for (size_t y = 0; y < FONT_HEIGHT; y++) {
		for (x = 0; x < FONT_WIDTH; x++) {
			if (font_at(i, x, y))
				*(v_ram + x + (y*VGA_WIDTH)) = color;
				//set_memory_with_curosr((v_ram + x + (y*VGA_WIDTH)), x, y, color);
		}
	}
	update_cursor(prev_c, cursor_x, cursor_y);
	return (uint8_t *)(v_ram + x + 1);
}

/**
 * scrolls entire screen one character height up
 **/
void vga_scroll() {
	uint8_t * v_ram = VGA_MEM;
	uint8_t * v_ram_old = VGA_MEM + ((FONT_HEIGHT+2) * VGA_WIDTH);
	uint8_t * end_of_v_ram = ((VGA_MEM+VGA_WIDTH)+(VGA_WIDTH * VGA_HEIGHT));
	while (v_ram_old != end_of_v_ram) {
		(*v_ram) = (*v_ram_old);
		v_ram++;
		v_ram_old++;
	}
}

void vga_append_char(uint16_t i, uint8_t color) {
	text_cursor = memset_5x7font(text_cursor, i, color);
}

void place_cursor(uint8_t * v_mem_start){
	uint8_t * v_ram = v_mem_start;
	for (size_t y = 0; y < CURSOR_IMG_HEIGHT; y++) {
		for (size_t x = 0; x < CURSOR_IMG_WIDTH; x++) {
			if(cursor.img[y][x] == 2) {
				*(v_ram + x + (y*VGA_WIDTH)) = COLOR_BLACK.c;
			} else if (cursor.img[y][x] == 1) {
				*(v_ram + x + (y*VGA_WIDTH)) = cursor_color.c;
			}
		}
	}
}

void read_cursor(uint8_t * v_mem_start){
	uint8_t * v_ram = v_mem_start;
	for (size_t y = 0; y < CURSOR_IMG_HEIGHT; y++) {
		for (size_t x = 0; x < CURSOR_IMG_WIDTH; x++) {
			if (cursor.img[y][x] != 0) cursor.prev[y][x].c = *(v_ram + x + (y*VGA_WIDTH));
		}
	}
}

void restore_cursor(){
	uint8_t * v_ram = prev_c;
	for (size_t y = 0; y < CURSOR_IMG_HEIGHT; y++) {
		for (size_t x = 0; x < CURSOR_IMG_WIDTH; x++) {
			if (cursor.img[y][x] != 0) *(v_ram + x + (y*VGA_WIDTH)) = cursor.prev[y][x].c;
		}
	}
}

void update_cursor(uint8_t * v_mem_start, uint32_t x, uint32_t y) {
	cursor_x = x;
	cursor_y = y;
	restore_cursor();
	prev_c = v_mem_start;
	read_cursor(prev_c);
	place_cursor(prev_c);
}


void vga_init_cursor(){
	cursor_x = 320;
	cursor_y = 200;
	prev_c = vram_at(320, 200);
	read_cursor(prev_c);
	place_cursor(prev_c);
}

void init_VGA_driver() {
	vga_init_palette();
	vga_init_cursor();
}
