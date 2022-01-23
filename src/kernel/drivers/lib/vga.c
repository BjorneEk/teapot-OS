

#ifndef asm
#define asm __asm__ volatile
#endif
#include "../include/vga.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#define VGA_WIDTH  320
#define VGA_HEIGHT 200

uint8_t port_byte_in(uint16_t port) {
	uint8_t result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(uint16_t port, uint8_t data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void put_pixel(uint16_t pos_x, uint16_t pos_y, uint8_t VGA_COLOR) {
	*((uint8_t*)0xA0000 + 320 * pos_y + pos_x) = VGA_COLOR;
}

void clear_pixel(uint16_t pos_x, uint16_t pos_y) {
	*((uint8_t*)0xA0000 + 320 * pos_y + pos_x) = 0;
}
