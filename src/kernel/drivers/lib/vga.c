

#ifndef asm
#define asm __asm__ volatile
#endif
#include "../include/vga.h"
#include "../../utils/include/math.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

uint8_t in_portb(uint16_t port) {
	uint8_t res;
	__asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
	return res;
}

void out_portb(uint16_t port, uint8_t data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

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
	*((uint8_t*)0xA0000 + 320 * pos_y + pos_x) = vga_color;
}

uint8_t get_pixel(uint16_t pos_x, uint16_t pos_y) {
	return *((uint8_t*)0xA0000 + 320 * pos_y + pos_x);
}

void clear_pixel(uint16_t pos_x, uint16_t pos_y) {
	*((uint8_t*)0xA0000 + 320 * pos_y + pos_x) = 0;
}

///
///  Bresenham's line algorithm
///  https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
///
void memset_line(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color) {
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
		if (e2 >= dy) {/* e_xy+e_x > 0 */
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {/* e_xy+e_y < 0 */
			err += dx;
			y0 += sy;
		}
	}
}


void memset_rect(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color) {
	uint8_t * v_ram = v_mem_start;
	for (size_t y = 0; y < h * VGA_WIDTH; y += VGA_WIDTH) {
		for (size_t x = 0; x < w; x++) {
			*(v_ram + x + y) = color;
		}
	}
}
