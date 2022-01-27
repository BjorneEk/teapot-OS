#ifndef VGA_H
#define VGA_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../../libc/include/int.h"

#define VGA_MEM (uint8_t *) 0xA0000

#define VGA_WIDTH  320
#define VGA_HEIGHT 200

#define VGA_PALETTE_MASK  0x3C6
#define VGA_PALETTE_READ  0x3C7
#define VGA_PALETTE_WRITE 0x3C8
#define VGA_PALETTE_DATA  0x3C9

#define vram_at(_x, _y) (uint8_t *) (((VGA_MEM)+(_x))+((VGA_WIDTH) * (_y)))



/**
 *  a struct used for drawing images onto the screen;
 **/
typedef struct VGA_image {

	uint8_t ** image;  /**
                       *  pointer to image 2d array
                       **/

	uint16_t w;   /**
                  *  width of the image
                  **/

	uint16_t h;   /**
                  *  height of the image
                  **/

	uint8_t transparrent;   /**
                            *  if true white pixels are not colored;
                            **/
} vga_image_t;

void vga_init_palette();

void put_pixel(uint16_t pos_x, uint16_t pos_y, uint8_t vga_color);

uint8_t get_pixel(uint16_t pos_x, uint16_t pos_y);

void clear_pixel(uint16_t pos_x, uint16_t pos_y);

void memset_line(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color);

void memset_rect(uint8_t * v_mem_start, int16_t w, int16_t h, uint8_t color);

///
/// put a character from the font in font.h: FONT5X7[i] on the screen
/// @param i The index within the font character array
/// returns pointer to video ram where potential following characters should be places
///
uint8_t * memset_5x7font(uint8_t * v_mem_start, uint16_t i, uint8_t color);

uint8_t * memset_image(uint8_t * v_mem_start,  vga_image_t img);

void vga_init_cursor();

void update_cursor(uint8_t * v_mem_start);

#endif /* VGA_H */
