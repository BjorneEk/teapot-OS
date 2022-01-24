#ifndef VGA_H
#define VGA_H

#include "../../utils/include/int.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#define VGA_MEM (uint8_t *) 0xA0000

#define VGA_WIDTH  320
#define VGA_HEIGHT 200

#define VGA_PALETTE_MASK  0x3C6
#define VGA_PALETTE_READ  0x3C7
#define VGA_PALETTE_WRITE 0x3C8
#define VGA_PALETTE_DATA  0x3C9

#define vram_at(_x, _y) (uint8_t *) (((VGA_MEM)+(_x))+((VGA_WIDTH) * (_y)))

void vga_init_palette();

void put_pixel(uint16_t pos_x, uint16_t pos_y, uint8_t vga_color);

uint8_t get_pixel(uint16_t pos_x, uint16_t pos_y);

void clear_pixel(uint16_t pos_x, uint16_t pos_y);

void memset_line(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color);

void memset_rect(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color);

#endif /* VGA_H */
