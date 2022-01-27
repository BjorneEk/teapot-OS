

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"
#include "drivers/include/keyboard.h"
#include "drivers/include/mouse.h"
#include "libc/include/math.h"
#include "libc/include/string.h"
#include "libc/include/malloc.h"

#include "lin-alg/triangle.h"

#include "cpu/idt.h"
#include "cpu/isr.h"



void delay(uint32_t t) {
	for (size_t i = 0; i < t; i++) {
		__asm__ __volatile__("nop");
	}
}
void main() {
	//malloc_init();
	vga_init_palette();
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_PINK);
	draw_string((VGA_WIDTH / 2) - 7, 60, "    welcome to\n    teapot-os\n\n by gustaf franzen", COLOR_BLACK);
	isr_install();
	//draw_string((VGA_WIDTH / 2) -  30, 77, "Installing interrupt service routines (ISRs).", COLOR_BLACK);
	__asm__ __volatile__("sti");
	//draw_string((VGA_WIDTH / 2) - 15, 83, "Enabeling interrupts", COLOR_BLACK);
	init_keyboard();
	init_mouse();
	vga_init_cursor();
	//draw_string((VGA_WIDTH / 2) - 15, 83, "initializing keyboard drivers", COLOR_BLACK);


	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
	fill_rect(0, 0, VGA_WIDTH, STATUS_BAR_HEIGHT, COLOR_STATBAR);
	set_os_name("teapot-os");

	/*
	for(;;){
		for (float x = 0; x < VGA_WIDTH + 70; x++) {
			for (size_t y_off = 0; y_off < 34; y_off++) {
				float y;
				if(x < VGA_WIDTH) {
					y =2.0f + (sin(x/30) * 30);
					if((uint32_t)y + (y_off*5) > STATUS_BAR_HEIGHT)
						fill_rect((uint32_t)x, (uint32_t)y + (y_off*5), 1, 1, from_radian(x/2));
				}
				if (x >= 70) {
					y =2.0f + (sin((x-70)/30) * 30);
					if((uint32_t)y + (y_off*5) > STATUS_BAR_HEIGHT)
						fill_rect((uint32_t)(x-70), (uint32_t)y + (y_off*5), 1, 1, COLOR_BLACK);
				}
			}

		delay(0x4FFFFF);
		}
	}
	*/
}
