

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"
#include "drivers/include/keyboard.h"
#include "drivers/include/mouse.h"
#include "cpu/idt.h"
#include "cpu/isr.h"

typedef struct vec3d {
	int32_t x;
	int32_t y;
	int32_t z;
} vec3d_t;

typedef struct triangle {
	union {
		struct {
			vec3d_t p1;
			vec3d_t p2;
			vec3d_t p3;
		};
		vec3d_t p[3];
	};
} triangle_t;

triangle_t tris[] = {
	{.p1={10, 10, 10}, .p2={10, 80, 10}, .p3={80, 10, 10}},
	{.p1={10, 80, 10}, .p2={80, 80, 10}, .p3={80, 10, 10}},
	{.p1={80, 10, 10}, .p2={80, 80, 10}, .p3={80, 10, 80}},
	{.p1={80, 80, 10}, .p2={80, 80, 80}, .p3={80, 10, 80}},
	{.p1={80, 10, 80}, .p2={80, 80, 80}, .p3={10, 10, 80}},
	{.p1={80, 80, 80}, .p2={10, 80, 80}, .p3={10, 10, 80}},
	{.p1={10, 10, 80}, .p2={10, 80, 80}, .p3={10, 10, 10}},
	{.p1={10, 80, 80}, .p2={10, 80, 10}, .p3={10, 10, 10}},
	{.p1={10, 80, 10}, .p2={10, 80, 80}, .p3={80, 80, 80}},
	{.p1={80, 80, 80}, .p2={80, 80, 10}, .p3={10, 80, 10}},
	{.p1={10, 10, 80}, .p2={10, 10, 10}, .p3={80, 10, 10}},
	{.p1={80, 10, 10}, .p2={80, 10, 80}, .p3={10, 10, 80}},
};

void delay(uint32_t t) {
	for (size_t i = 0; i < t; i++) {
		__asm__ __volatile__("nop");
	}
}
void main() {
	vga_init_palette();
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_PINK);
	draw_string((VGA_WIDTH / 2) - 7, 60, "    welcome to\n    teapot-os\n\n by gustaf franzen", COLOR_BLACK);
	isr_install();
	draw_string((VGA_WIDTH / 2) - 30, 77, "Installing interrupt service routines (ISRs).", COLOR_BLACK);
	__asm__ __volatile__("sti");
	draw_string((VGA_WIDTH / 2) - 15, 83, "Enabeling interrupts", COLOR_BLACK);
	init_keyboard();

	vga_init_cursor();
	draw_string((VGA_WIDTH / 2) - 15, 83, "initializing keyboard drivers", COLOR_BLACK);
	delay(0xFFFFFFF);


	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BACKGROUND);
	fill_rect(0, 0, VGA_WIDTH, STATUS_BAR_HEIGHT, COLOR_STATBAR);
	set_os_name("teapot-os");
	init_mouse();
	for(;;){
		for (size_t o = 0; o < 20; o++) {
			fill_rect(0, STATUS_BAR_HEIGHT, VGA_WIDTH, VGA_HEIGHT-STATUS_BAR_HEIGHT, COLOR_BACKGROUND);
			for (size_t i = 0; i < 16; i++) {
				draw_line(((i * 20) + o),     STATUS_BAR_HEIGHT, ((i * 20) + o), VGA_HEIGHT, COLOR_BLUE.c);
				draw_line(((i * 20) + (o+1)), STATUS_BAR_HEIGHT, ((i * 20) + (o+1)), VGA_HEIGHT, COLOR_BLUE.c);
				draw_line(((i * 20) + (o+2)), STATUS_BAR_HEIGHT, ((i * 20) + (o+2)), VGA_HEIGHT, COLOR_RED.c);
				draw_line(((i * 20) + (o+3)), STATUS_BAR_HEIGHT, ((i * 20) + (o+3)), VGA_HEIGHT, COLOR_RED.c);
				draw_line(((i * 20) + (o+4)), STATUS_BAR_HEIGHT, ((i * 20) + (o+4)), VGA_HEIGHT, COLOR_GREEN.c);
				draw_line(((i * 20) + (o+5)), STATUS_BAR_HEIGHT, ((i * 20) + (o+5)), VGA_HEIGHT, COLOR_GREEN.c);
			}
			for (size_t i = 0; i < 10; i++) {
				draw_line(0,   (STATUS_BAR_HEIGHT + ((i * 20) + (o))), VGA_WIDTH,   (STATUS_BAR_HEIGHT + ((i * 20) + (o))), COLOR_WHITE.c);
				draw_line(0, (STATUS_BAR_HEIGHT + ((i * 20) + (o+1))), VGA_WIDTH, (STATUS_BAR_HEIGHT + ((i * 20) + (o+1))), COLOR_WHITE.c);
				draw_line(0, (STATUS_BAR_HEIGHT + ((i * 20) + (o+2))), VGA_WIDTH, (STATUS_BAR_HEIGHT + ((i * 20) + (o+2))), COLOR_PINK.c);
				draw_line(0, (STATUS_BAR_HEIGHT + ((i * 20) + (o+3))), VGA_WIDTH, (STATUS_BAR_HEIGHT + ((i * 20) + (o+3))), COLOR_PINK.c);
				draw_line(0, (STATUS_BAR_HEIGHT + ((i * 20) + (o+4))), VGA_WIDTH, (STATUS_BAR_HEIGHT + ((i * 20) + (o+4))), COLOR_PURPLE.c);
				draw_line(0, (STATUS_BAR_HEIGHT + ((i * 20) + (o+5))), VGA_WIDTH, (STATUS_BAR_HEIGHT + ((i * 20) + (o+5))), COLOR_PURPLE.c);
			}
			delay(0xFFFFFF);
		}
	}

	/*for (size_t i = 0; i < 12; i++) {
		draw_triangle((point_t){.x=(int16_t)tris[i].p1.x, .y=(int16_t)tris[i].p1.y},
		(point_t){.x=(int16_t)tris[i].p2.x, .y=(int16_t)tris[i].p2.y},
		(point_t){.x=(int16_t)tris[i].p3.x, .y=(int16_t)tris[i].p3.y}, clr);
	}*/
}
