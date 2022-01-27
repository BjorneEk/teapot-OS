

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
	{.p1={30,  30,  30}, .p2={ 30, 120,  30}, .p3={120,  30,  30}},
	{.p1={ 30, 120,  30}, .p2={120, 120,  30}, .p3={120,  30,  30}},
	{.p1={120,  30,  30}, .p2={120, 120,  30}, .p3={120,  30, 120}},
	{.p1={120, 120,  30}, .p2={120, 120, 120}, .p3={120,  30, 120}},
	{.p1={120,  30, 120}, .p2={120, 120, 120}, .p3={ 30,  30, 120}},
	{.p1={120, 120, 120}, .p2={ 30, 120, 120}, .p3={ 30,  30, 120}},
	{.p1={ 30,  30, 120}, .p2={ 30, 120, 120}, .p3={ 30,  30,  30}},
	{.p1={ 30, 120, 120}, .p2={ 30, 120,  30}, .p3={ 30,  30,  30}},
	{.p1={ 30, 120,  30}, .p2={ 30, 120, 120}, .p3={120, 120, 120}},
	{.p1={120, 120, 120}, .p2={120, 120,  30}, .p3={ 30, 120,  30}},
	{.p1={ 30,  30, 120}, .p2={ 30,  30,  30}, .p3={120,  30,  30}},
	{.p1={120,  30,  30}, .p2={120,  30, 120}, .p3={ 30,  30, 120}},
};

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
	delay(0x5FFFFFFF);


	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BACKGROUND);
	fill_rect(0, 0, VGA_WIDTH, STATUS_BAR_HEIGHT, COLOR_STATBAR);
	set_os_name("teapot-os");

	/*
	for (size_t i = 0; i < VGA_WIDTH; i++) {
		float s = sin(i);
		uint16_t y = 60 + (uint16_t) (10);
		fill_rect(i, y, 2, 2, COLOR_RED);
	}*/
	fill_rect(50, 50, 50, 50, COLOR_RED);

	fill_rect(100, 100, 50, 50, COLOR_PURPLE);
	/*
	for (size_t i = 0; i < 12; i++) {
		point_t p1 = {.x=tris[i].p1.x, .y=tris[i].p1.y};
		point_t p2 = {.x=tris[i].p2.x, .y=tris[i].p2.y};
		point_t p3 = {.x=tris[i].p3.x, .y=tris[i].p3.y};
		draw_triangle(p1, p2, p3, COLOR_BLUE);
	}
	*/
}
