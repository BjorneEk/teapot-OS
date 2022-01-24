

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"

typedef struct vec3d {
	float x;
	float y;
	float z;
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
	{.p1={10.0, 10.0, 10.0}, .p2={10.0, 80.0, 10.0}, .p3={80.0, 10.0, 10.0}},
	{.p1={10.0, 80.0, 10.0}, .p2={80.0, 80.0, 10.0}, .p3={80.0, 10.0, 10.0}},
	{.p1={80.0, 10.0, 10.0}, .p2={80.0, 80.0, 10.0}, .p3={80.0, 10.0, 80.0}},
	{.p1={80.0, 80.0, 10.0}, .p2={80.0, 80.0, 80.0}, .p3={80.0, 10.0, 80.0}},
	{.p1={80.0, 10.0, 80.0}, .p2={80.0, 80.0, 80.0}, .p3={10.0, 10.0, 80.0}},
	{.p1={80.0, 80.0, 80.0}, .p2={10.0, 80.0, 80.0}, .p3={10.0, 10.0, 80.0}},
	{.p1={10.0, 10.0, 80.0}, .p2={10.0, 80.0, 80.0}, .p3={10.0, 10.0, 10.0}},
	{.p1={10.0, 80.0, 80.0}, .p2={10.0, 80.0, 10.0}, .p3={10.0, 10.0, 10.0}},
	{.p1={10.0, 80.0, 10.0}, .p2={10.0, 80.0, 80.0}, .p3={80.0, 80.0, 80.0}},
	{.p1={80.0, 80.0, 80.0}, .p2={80.0, 80.0, 10.0}, .p3={10.0, 80.0, 10.0}},
	{.p1={10.0, 10.0, 80.0}, .p2={10.0, 10.0, 10.0}, .p3={80.0, 10.0, 10.0}},
	{.p1={80.0, 10.0, 10.0}, .p2={80.0, 10.0, 80.0}, .p3={10.0, 10.0, 80.0}},
};


void main() {
	vga_init_palette();
	color_t clr = COLOR_GREEN;
	point_t p1 = {.x=160, .y=70};
	point_t p2 = {.x=190, .y=140};
	point_t p3 = {.x=130, .y=140};

	fill_rect(30, 30, VGA_WIDTH-60, VGA_HEIGHT-60, COLOR_BLUE);
	draw_triangle(p1, p2, p3, clr);
	/*
	for (size_t i = 0; i < 12; i++) {
		point_t p1 = {.x=(int16_t)tris[i].p1.x, .y=(int16_t)tris[i].p1.y};
		point_t p2 = {.x=(int16_t)tris[i].p2.x, .y=(int16_t)tris[i].p2.y};
		point_t p3 = {.x=(int16_t)tris[i].p3.x, .y=(int16_t)tris[i].p3.y};
		draw_triangle(p1, p2, p3, clr);
	}*/
}
