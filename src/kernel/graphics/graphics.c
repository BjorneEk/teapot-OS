

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "graphics.h"
#include "../libc/include/string.h"
#include "../libc/include/malloc.h"

color_t DRAW_COLOR = (color_t){.r=0b111, .g=0b111, .b=0b11};

void set_color(color_t color) {
	DRAW_COLOR = color;
}

color_t get_color(uint16_t x, uint16_t y) {
	return (color_t) { .c = get_pixel(x, y)};
}

void fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, color_t clr) {
	memset_rect(((VGA_MEM+x)+(VGA_WIDTH * y)), w, h, clr.c);
}

void draw_char(int32_t x, int32_t y, char c, color_t clr) {
	memset_5x7font(((VGA_MEM+x)+(VGA_WIDTH * y)), get_idx_from_char(c), clr.c);
}

uint8_t * draw_string(int32_t x, int32_t y, char * str, color_t clr) {
	uint8_t line = 0;
	uint8_t * v_ram = memset_5x7font(((VGA_MEM+x)+(VGA_WIDTH * y)), get_idx_from_char(*str), clr.c);
	//uint8_t * v_ram = memset_image(((VGA_MEM+x)+(VGA_WIDTH * y)), (uint8_t **)FONT5X7[get_char_idx(*str)], FONT_WIDTH, FONT_HEIGHT, clr.c);
	str++;
	while(*str) {
		if (*str == ' ') v_ram = v_ram + FONT_WIDTH;
		else if (*str == '\n'){
			v_ram = ((VGA_MEM + x) + (VGA_WIDTH * (y + FONT_HEIGHT + 1))) + (line * VGA_WIDTH * (FONT_HEIGHT+2));
			line++;
		} else {
			uint16_t idx = get_idx_from_char(*(uint8_t*)str);
			if (idx != INVALID_IDX) v_ram = memset_5x7font(v_ram, idx, clr.c);
			//if (idx != INVALID_IDX) v_ram = memset_image(v_ram, (uint8_t **)FONT5X7[idx], FONT_WIDTH, FONT_HEIGHT, clr.c);
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
	memset_5x7font(v_ram, get_idx_from_char(c), COLOR_RED.c);
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
