
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/keyboard.h"
#include "../include/event.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../libc/include/string.h"
uint8_t SHIFT_DOWN = false;
uint8_t ALT_DOWN = false;
uint8_t CTRL_DOWN = false;

char get_char_from_scancode(uint8_t sc) {
	if(sc > 0x81 && sc <= 0x8B) {
		switch (sc) {
			case 0x8B: return '0';
			default: return (sc-0x82) + 49;
		}
	}
	switch (sc) {
		case 0x02: return (SHIFT_DOWN) ? '!' : '1';
		case 0x03: return (SHIFT_DOWN) ? '"' : (ALT_DOWN) ? '@' : '2';
		case 0x04: return (SHIFT_DOWN) ? '#' : '3';
		case 0x05: return '4';
		case 0x06: return (SHIFT_DOWN) ? '%' : '5';
		case 0x07: return (SHIFT_DOWN) ? '&' : '6';
		case 0x08: return (SHIFT_DOWN) ? '/' : (ALT_DOWN) ? '{' : '7';
		case 0x09: return (SHIFT_DOWN) ? '(' : (ALT_DOWN) ? '[' : '8';
		case 0x0a: return (SHIFT_DOWN) ? ')' : (ALT_DOWN) ? ']' : '9';
		case 0x0b: return (SHIFT_DOWN) ? '=' : (ALT_DOWN) ? '}' : '0';
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
		case KEY_SPACE:
		case KEY_RELEASED_SPACE: return ' ';

		case KEY_LESS_THAN:               return (SHIFT_DOWN) ? '>' : '<';
		case KEY_MINUS:
		case KEY_RELEASED_MINUS:          return (ALT_DOWN) ? '?' : (SHIFT_DOWN) ? '+' : '-';
		case KEY_SEMICOLON:
		case KEY_RELEASED_SEMICOLON:      return ';';
		case KEY_COMMA:
		case KEY_RELEASED_COMMA:          return ',';
		case KEY_DOT:
		case KEY_RELEASED_DOT:            return '.';
		case KEY_SINGLE_QUOTE:
		case KEY_RELEASED_SINGLE_QUOTE:   return '\'';
		case KEY_BACKSLASH:
		case KEY_RELEASED_BACKSLASH:      return (SHIFT_DOWN) ? '*' : '\\';
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
	switch (sc) {
		case KEY_LALT:
			ALT_DOWN = true;
			break;
		case KEY_LSHIFT:
		case KEY_RSHIFT:
			SHIFT_DOWN = true;
			break;
		case KEY_LCTRL:
		case KEY_RCTRL:
			CTRL_DOWN = true;
		case KEY_RELEASED_LALT:
			ALT_DOWN = false;
			break;
		case KEY_RELEASED_LSHIFT:
		case KEY_RELEASED_RSHIFT:
			SHIFT_DOWN = false;
			break;
		case KEY_RELEASED_LCTRL:
			CTRL_DOWN = false;
	}
	event_t evt;
	evt.type = (sc >= 0x80) ?  Key_released : Key_pressed;
	evt.key.key_char = get_char_from_scancode(sc);
	evt.key.scancode = sc;
	create_keyboard_event(evt);
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}
