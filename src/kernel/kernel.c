

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"
#include "drivers/include/keyboard.h"
#include "drivers/include/mouse.h"
#include "utils/include/math.h"
#include "utils/include/string.h"

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
	vga_init_palette();
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_PINK);
	draw_string((VGA_WIDTH / 2) - 7, 60, "    welcome to\n    teapot-os\n\n by gustaf franzen", COLOR_BLACK);
	isr_install();
	draw_string((VGA_WIDTH / 2) -  30, 77, "Installing interrupt service routines (ISRs).", COLOR_BLACK);
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



	float s = sin(PI);
	char rs[10];
	ftoa(s, rs, 5);
	draw_string((VGA_WIDTH / 2), 70, rs, COLOR_BLACK);

	/*
	for (size_t i = 0; i < VGA_WIDTH; i++) {
		float s = sin(i);
		uint16_t y = 60 + (uint16_t) (10);
		fill_rect(i, y, 2, 2, COLOR_RED);
	}*/

	for (size_t i = 0; i < 12; i++) {
		point_t p1 = {.x=tris[i].p1.x, .y=tris[i].p1.y};
		point_t p2 = {.x=tris[i].p2.x, .y=tris[i].p2.y};
		point_t p3 = {.x=tris[i].p3.x, .y=tris[i].p3.y};
		draw_triangle(p1, p2, p3, COLOR_BLUE);
	}



	for(;;){


		/*
		for (size_t o = 0; o < 20; o++) {
			//fill_rect(0, STATUS_BAR_HEIGHT, VGA_WIDTH, VGA_HEIGHT-STATUS_BAR_HEIGHT, COLOR_BACKGROUND);
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
		}*/
	}

	/*for (size_t i = 0; i < 12; i++) {
		draw_triangle((point_t){.x=(int16_t)tris[i].p1.x, .y=(int16_t)tris[i].p1.y},
		(point_t){.x=(int16_t)tris[i].p2.x, .y=(int16_t)tris[i].p2.y},
		(point_t){.x=(int16_t)tris[i].p3.x, .y=(int16_t)tris[i].p3.y}, clr);
	}*/
}
