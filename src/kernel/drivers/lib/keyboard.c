
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/keyboard.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../libc/include/string.h"


void print_letter(uint8_t scancode) {
	switch (scancode) {
		case 0x0:
			set_last_key("ERROR");
			break;
		case 0x1:
			set_last_key("ESC");
			__asm__ __volatile__("hlt");
			break;
		case 0x2:
			set_last_key("1");
			break;
		case 0x3:
			set_last_key("2");
			break;
		case 0x4:
			set_last_key("3");
			break;
		case 0x5:
			set_last_key("4");
			break;
		case 0x6:
			set_last_key("5");
			break;
		case 0x7:
			set_last_key("6");
			break;
		case 0x8:
			set_last_key("7");
			break;
		case 0x9:
			set_last_key("8");
			break;
		case 0x0A:
			set_last_key("9");
			break;
		case 0x0B:
			set_last_key("0");
			break;
		case 0x0C:
			set_last_key("-");
			break;
		case 0x0D:
			set_last_key("pluss");
			break;
		case 0x0E:
			set_last_key("Bspce");
			break;
		case 0x0F:
			set_last_key("Tab");
			break;
		case 0x10:
			set_last_key("Q");
			break;
		case 0x11:
			set_last_key("W");
			break;
		case 0x12:
			set_last_key("E");
			break;
		case 0x13:
			set_last_key("R");
			break;
		case 0x14:
			set_last_key("T");
			break;
		case 0x15:
			set_last_key("Y");
			break;
		case 0x16:
			set_last_key("U");
			break;
		case 0x17:
			set_last_key("I");
			break;
		case 0x18:
			set_last_key("O");
			break;
		case 0x19:
			set_last_key("P");
			break;
		case 0x1A:
			set_last_key("[");
			break;
		case 0x1B:
			set_last_key("]");
			break;
		case 0x1C:
			set_last_key("ENTER");
			break;
		case 0x1D:
			set_last_key("LCtrl");
			break;
		case 0x1E:
			set_last_key("A");
			break;
		case 0x1F:
			set_last_key("S");
			break;
		case 0x20:
			set_last_key("D");
			break;
		case 0x21:
			set_last_key("F");
			break;
		case 0x22:
			set_last_key("G");
			break;
		case 0x23:
			set_last_key("H");
			break;
		case 0x24:
			set_last_key("J");
			break;
		case 0x25:
			set_last_key("K");
			break;
		case 0x26:
			set_last_key("L");
			break;
		case 0x27:
			set_last_key(";");
			break;
		case 0x28:
			set_last_key("tic");
			break;
		case 0x29:
			set_last_key("btic");
			break;
		case 0x2A:
			set_last_key("LShift");
			break;
		case 0x2B:
			set_last_key("bslsh");
			break;
		case 0x2C:
			set_last_key("Z");
			break;
		case 0x2D:
			set_last_key("X");
			break;
		case 0x2E:
			set_last_key("C");
			break;
		case 0x2F:
			set_last_key("V");
			break;
		case 0x30:
			set_last_key("B");
			break;
		case 0x31:
			set_last_key("N");
			break;
		case 0x32:
			set_last_key("M");
			break;
		case 0x33:
			set_last_key(",");
			break;
		case 0x34:
			set_last_key(".");
			break;
		case 0x35:
			set_last_key("slsh");
			break;
		case 0x36:
			set_last_key("Rshift");
			break;
		case 0x37:
			set_last_key("Kpd *");
			break;
		case 0x38:
			set_last_key("LAlt");
			break;
		case 0x39:
			set_last_key("Space");
			break;
		default:
			/* 'keuyp' event corresponds to the 'keydown' + 0x80
			 * it may still be a scancode we haven't implemented yet, or
			 * maybe a control/escape sequence */
			if (scancode <= 0x7f) {
				set_last_key("Unkno kd");
			} else if (scancode <= 0x39 + 0x80) {
				set_last_key("key up");
				print_letter(scancode - 0x80);
			} else set_last_key("Unkno ku");
			break;
	}
}

static void keyboard_callback(registers_t *regs) {
	uint8_t scancode = in_portb(0x60);
	print_letter(scancode);
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}
