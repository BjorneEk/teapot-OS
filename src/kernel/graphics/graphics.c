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

///
/// functions used for drawing text
///

uint16_t get_char_idx(uint8_t c) {
	if(c <= 0x40) {
		switch (c) {
			case ';': return SEMICOLON_IDX;
			case ':': return COLON_IDX;
			case '.': return DOT_IDX;
			case ',': return COMMA_IDX;
			case '?': return QUESTION_MARK_IDX;
			case '!': return EXCLAMATION_MARK_IDX;
			case ')': return PARANTHESIS_R_IDX;
			case '(': return PARANTHESIS_L_IDX;
			case '-': return DASH_IDX;
			default:
				if (c <= NUM_END && c >= NUM_START)
					return ((uint8_t)c - NUM_START) + NUM_IDX_START;
				return INVALID_IDX;
		}
	}
	if (c <= ALPH_END) return (uint8_t)c - ALPH_START;
	/// (0x61 - 0x41):  0x61: lower case a, 0x41 upper case a
	if(c >= 0x61 && c <= 0x7a) return (((uint8_t)c - (0x61 - 0x41)) - ALPH_START);
	if(c == ']') return SQ_BRACET_R_IDX;
	if(c == '[') return SQ_BRACET_L_IDX;

	if((uint8_t)c == 0xE5 || (uint8_t)c == 0xC5) return NUM_IDX_START - 3;
	if((uint8_t)c == 0xE4 || (uint8_t)c == 0xC4 || (uint8_t)c == 0xC3) return NUM_IDX_START - 2;
	if((uint8_t)c == 0xF6 || (uint8_t)c == 0xD6) return NUM_IDX_START - 1;
	return INVALID_IDX;
}

void draw_char(int32_t x, int32_t y, char c, color_t clr) {
	memset_5x7font(((VGA_MEM+x)+(VGA_WIDTH * y)), get_char_idx(c), clr.c);
}

void draw_string(int32_t x, int32_t y, char * str, color_t clr) {
	uint8_t * v_ram = memset_5x7font(((VGA_MEM+x)+(VGA_WIDTH * y)), get_char_idx(*str), clr.c);
	str++;
	while(*str) {
		if (*str == ' ') v_ram = v_ram + FONT_WIDTH;
		else if (*str == '\n') v_ram = ((VGA_MEM + x) + (VGA_WIDTH * (y + FONT_HEIGHT + 1)));
		else {
			uint16_t idx = get_char_idx(*(uint8_t*)str);
			if (idx != INVALID_IDX) v_ram = memset_5x7font(v_ram, idx, clr.c);
		}
		str++;
	}
}
