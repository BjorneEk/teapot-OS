#ifndef COLOR_H
#define COLOR_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../libc/include/int.h"

/**
 *   bitfield used to represent a single byte color
 *   with 3 red, 3 green and 2 blue bits.
 **/
typedef struct color {
	union{
		uint8_t c;
		struct {
			uint8_t b : 2;
			uint8_t g : 3;
			uint8_t r : 3;
		};
	};
} color_t;

#define COLOR_RED (color_t){.r=0b111, .g=0b000, .b=0b00}
#define COLOR_PINK (color_t){.r=0b111, .g=0b100, .b=0b11}

#define COLOR_GREEN (color_t){.r=0b000, .g=0b111, .b=0b00}
#define COLOR_YELLOW (color_t){.r=0b111, .g=0b111, .b=0b00}

#define COLOR_BLUE (color_t){.r=0b000, .g=0b000, .b=0b11}
#define COLOR_PURPLE (color_t){.r=0b101, .g=0b001, .b=0b11}

#define COLOR_WHITE (color_t){.r=0b111, .g=0b111, .b=0b11}
#define COLOR_BLACK (color_t){.r=0b000, .g=0b000, .b=0b00}

#define COLOR_STATBAR (color_t){.r=0b100, .g=0b100, .b=0b10}
#define COLOR_BACKGROUND (color_t){.r=0b000, .g=0b100, .b=0b01}


/**
 *   used to create rainbow effects.
 **/
color_t from_radian(float r);

/**
 *  create a new color from another color but at a certain brightness.
 **/
color_t with_brightness(color_t color, float brightness);

#endif /* GRAPHICS_H */
