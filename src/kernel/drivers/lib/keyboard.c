
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/keyboard.h"
#include "../include/event.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../libc/include/string.h"

char get_char_from_scancode(uint8_t sc) {
	if(sc <= 0x0B) {
		switch (sc) {
			case KEY_ESCAPE: return UNKNOWN_SCANCODE_CHAR;
			case 0x0B: return '0';
			default: return sc + 48;
		}
	}
	if(sc > 0x81 && sc <= 0x8B) {
		switch (sc) {
			case 0x8B: return '0';
			default: return (sc-0x82) + 49;
		}
	}
	switch (sc) {
		case KEY_A:
		case KEY_RELEASED_A: return 'a';
		case KEY_B:
		case KEY_RELEASED_B: return 'b';
		case KEY_C:
		case KEY_RELEASED_C: return 'c';
		case KEY_D:
		case KEY_RELEASED_D: return 'd';
		case KEY_E:
		case KEY_RELEASED_E: return 'e';
		case KEY_F:
		case KEY_RELEASED_F: return 'f';
		case KEY_G:
		case KEY_RELEASED_G: return 'g';
		case KEY_H:
		case KEY_RELEASED_H: return 'h';
		case KEY_I:
		case KEY_RELEASED_I: return 'i';
		case KEY_J:
		case KEY_RELEASED_J: return 'j';
		case KEY_K:
		case KEY_RELEASED_K: return 'k';
		case KEY_L:
		case KEY_RELEASED_L: return 'l';
		case KEY_M:
		case KEY_RELEASED_M: return 'm';
		case KEY_N:
		case KEY_RELEASED_N: return 'n';
		case KEY_O:
		case KEY_RELEASED_O: return 'o';
		case KEY_P:
		case KEY_RELEASED_P: return 'p';
		case KEY_Q:
		case KEY_RELEASED_Q: return 'q';
		case KEY_R:
		case KEY_RELEASED_R: return 'r';
		case KEY_S:
		case KEY_RELEASED_S: return 's';
		case KEY_T:
		case KEY_RELEASED_T: return 't';
		case KEY_U:
		case KEY_RELEASED_U: return 'u';
		case KEY_V:
		case KEY_RELEASED_V: return 'v';
		case KEY_W:
		case KEY_RELEASED_W: return 'w';
		case KEY_X:
		case KEY_RELEASED_X: return 'x';
		case KEY_Y:
		case KEY_RELEASED_Y: return 'y';
		case KEY_Z:
		case KEY_RELEASED_Z: return 'z';

		case KEY_MINUS:
		case KEY_RELEASED_MINUS:          return '-';
		case KEY_SEMICOLON:
		case KEY_RELEASED_SEMICOLON:      return ';';
		case KEY_COMMA:
		case KEY_RELEASED_COMMA:          return ',';
		case KEY_DOT:
		case KEY_RELEASED_DOT:            return '.';
		case KEY_SINGLE_QUOTE:
		case KEY_RELEASED_SINGLE_QUOTE:   return '\'';
		case KEY_BACKSLASH:
		case KEY_RELEASED_BACKSLASH:      return '\\';
		case KEY_SLASH:
		case KEY_RELEASED_SLASH:          return '/';
		case KEY_LSQARE_BRACKET:
		case KEY_RELEASED_LSQARE_BRACKET: return '[';
		case KEY_RSQUARE_BRACET:
		case KEY_RELEASED_RSQUARE_BRACET: return ']';
		case KEY_EQUALS:
		case KEY_RELEASED_EQUALS:         return '=';
		default:                          return UNKNOWN_SCANCODE_CHAR;
	}
}

static void keyboard_callback(registers_t *regs) {
	uint8_t sc = in_portb(0x60);
	event_t evt;
	evt.type = (sc >= 0x80) ? Key_pressed : Key_released;
	evt.key.key_char = get_char_from_scancode(sc);
	evt.key.scancode = sc;
	create_keyboard_event(evt);
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}
