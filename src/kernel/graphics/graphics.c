

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "graphics.h"
#include "../utils/include/string.h"

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

	return INVALID_IDX;
}

void draw_char(int32_t x, int32_t y, char c, color_t clr) {
	memset_5x7font(((VGA_MEM+x)+(VGA_WIDTH * y)), get_char_idx(c), clr.c);
}

uint8_t * draw_string(int32_t x, int32_t y, char * str, color_t clr) {
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
	return v_ram;
}

void set_last_key(char * key) {
	fill_rect(VGA_WIDTH - (STATUS_BAR_KEY_WIDTH+1), 1, STATUS_BAR_KEY_WIDTH, STATUS_BAR_HEIGHT - 2, COLOR_BACKGROUND);
	draw_string((VGA_WIDTH - (STATUS_BAR_KEY_WIDTH+1)) + 2, 2, key, COLOR_GREEN);
}

void set_last_key_with_trailing(char * key, char c) {
	fill_rect(VGA_WIDTH - (STATUS_BAR_KEY_WIDTH+1), 1, STATUS_BAR_KEY_WIDTH, STATUS_BAR_HEIGHT - 2, COLOR_BACKGROUND);
	uint8_t * v_ram = draw_string((VGA_WIDTH - (STATUS_BAR_KEY_WIDTH+1)) + 2, 2, key, COLOR_GREEN);
	memset_5x7font(v_ram, get_char_idx(c), COLOR_RED.c);
}

void set_os_name(char * name) {
	fill_rect(1, 1, STATUS_BAR_OS_NAME_WIDTH, STATUS_BAR_HEIGHT - 2, COLOR_BACKGROUND);
	draw_string(2, 2, name, COLOR_YELLOW);
}

void display_mouse(char * desc, char * msg) {
	fill_rect(2 + STATUS_BAR_OS_NAME_WIDTH, 1, STATUS_BAR_MESSAGE_WIDTH, STATUS_BAR_HEIGHT - 2, COLOR_BACKGROUND);
	draw_string(3 + STATUS_BAR_OS_NAME_WIDTH, 2, desc, COLOR_RED);
	draw_string(50 + STATUS_BAR_OS_NAME_WIDTH, 2, msg, COLOR_WHITE);
}
void refresh_cursor(int32_t x, int32_t y) {
	update_cursor(((VGA_MEM+x)+(VGA_WIDTH * y)));
}
