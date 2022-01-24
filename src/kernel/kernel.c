

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"

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
	color_t clr = COLOR_GREEN;
	/*point_t p1 = {.x=160, .y=70};
	point_t p2 = {.x=190, .y=140};
	point_t p3 = {.x=130, .y=140};
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
	fill_rect(30, 30, VGA_WIDTH-60, VGA_HEIGHT-60, COLOR_BLUE);
	draw_triangle(p1, p2, p3, clr);*/
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_PINK);
	draw_string((VGA_WIDTH / 2) - 7, 60, "    welcome to\n    teapot-os\n\n by gustaf franzen", COLOR_BLACK);
	delay(0xFFFFFFF);
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
	draw_string(1, 1, "teapot-os", COLOR_YELLOW);
	for(;;){
		for (size_t o = 0; o < 20; o++) {
			fill_rect(0, 8, VGA_WIDTH, VGA_HEIGHT-8, COLOR_BLACK);
			for (size_t i = 0; i < 16; i++) {
				draw_line(((i * 20) + o),     8, ((i * 20) + o), VGA_HEIGHT, COLOR_BLUE.c);
				draw_line(((i * 20) + (o+1)), 8, ((i * 20) + (o+1)), VGA_HEIGHT, COLOR_BLUE.c);
				draw_line(((i * 20) + (o+2)), 8, ((i * 20) + (o+2)), VGA_HEIGHT, COLOR_RED.c);
				draw_line(((i * 20) + (o+3)), 8, ((i * 20) + (o+3)), VGA_HEIGHT, COLOR_RED.c);
				draw_line(((i * 20) + (o+4)), 8, ((i * 20) + (o+4)), VGA_HEIGHT, COLOR_GREEN.c);
				draw_line(((i * 20) + (o+5)), 8, ((i * 20) + (o+5)), VGA_HEIGHT, COLOR_GREEN.c);
			}
			for (size_t i = 0; i < 10; i++) {
				draw_line(0,   (8 + ((i * 20) + (o))), VGA_WIDTH,   (8 + ((i * 20) + (o))), COLOR_WHITE.c);
				draw_line(0, (8 + ((i * 20) + (o+1))), VGA_WIDTH, (8 + ((i * 20) + (o+1))), COLOR_WHITE.c);
				draw_line(0, (8 + ((i * 20) + (o+2))), VGA_WIDTH, (8 + ((i * 20) + (o+2))), COLOR_PINK.c);
				draw_line(0, (8 + ((i * 20) + (o+3))), VGA_WIDTH, (8 + ((i * 20) + (o+3))), COLOR_PINK.c);
				draw_line(0, (8 + ((i * 20) + (o+4))), VGA_WIDTH, (8 + ((i * 20) + (o+4))), COLOR_PURPLE.c);
				draw_line(0, (8 + ((i * 20) + (o+5))), VGA_WIDTH, (8 + ((i * 20) + (o+5))), COLOR_PURPLE.c);
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
