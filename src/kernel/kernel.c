

///
/// @author Gustaf Franzén :: https://github.com/BjorneEk
/// main teapot-OS kernel
///

#include "graphics/graphics.h"
#include "drivers/include/keyboard.h"
#include "drivers/include/mouse.h"
#include "drivers/include/event.h"
#include "libc/include/math.h"
#include "libc/include/string.h"
#include "libc/include/malloc.h"
#include "lin-alg/triangle.h"
#include "cpu/idt.h"
#include "cpu/isr.h"

#define TEAPOT_LENGTH 20

extern triangle3d_t cube[];

float NEAR = 0.1f;
float FAR  = 1000.0f;
float FOV  = 90.0f;
float ASPECT_RATIO = 200.0f / 320.0f;

float x_angle = 0.0f;
float y_angle = 0.0f;

uint32_t prev_x = 0;
uint32_t prev_y = 0;
matrix4x4_t rx;
matrix4x4_t ry;

vec3d_t camera = (vec3d_t){
	.x = 160.0f,
	.y = 100.0f,
	.z = -90000.0f
};
vec3d_t light_dir = (vec3d_t){
	.x = 0,
	.y = 0.0,
	.z = -1.0
};

uint8_t MOUSE1 = 0;

matrix4x4_t proj_mat;

static float __slow_safe_int_to_float(uint32_t i) {
	float res = 0;
	for (; i > 0; i--) res += 1.0;
	return res;
}

void repaint(float x, float y){
	/**
	 *   increment angles depending on mouse movment
	 **/
	x_angle += (x - (float) __slow_safe_int_to_float(prev_x)) / 100.0f;
	y_angle -= (y - (float)__slow_safe_int_to_float(prev_y)) / 100.0f;

	/**
	 *   calculate cos and sin beforehand so it
	 *   only needs to be done once for each;
	 **/
	float cos_x = cos(x_angle);
	float sin_x = sin(x_angle);
	float cos_y = cos(y_angle);
	float sin_y = sin(y_angle);

	/**
	 *  create x and y rotation matricies;
	 **/
	 rx = (matrix4x4_t) {
 		.m[0] = {1.0f,  0.0f,   0.0f, 0.0f},
 		.m[1] = {0.0f, cos_y, -sin_y, 0.0f},
 		.m[2] = {0.0f, sin_y,  cos_y, 0.0f},
 		.m[3] = {0.0f,   0.0f,  0.0f, 1.0f}
 	};
 	ry = (matrix4x4_t) {
 		.m[0] = { cos_x, 0.0f, sin_x, 0.0f},
 		.m[1] = {  0.0f, 1.0f,  0.0f, 0.0f},
 		.m[2] = {-sin_x, 0.0f, cos_x, 0.0f},
 		.m[3] = {  0.0f, 0.0f,  0.0f, 1.0f}
 	};

	fill_rect(0, STATUS_BAR_HEIGHT, VGA_WIDTH, VGA_HEIGHT-STATUS_BAR_HEIGHT, (color_t){.r=0b101, .g=0b111, .b=0b11});
	for (size_t i = 0; i < TEAPOT_LENGTH; i++) {
		/**
		 *  create new triangle rotated and scaled;
		 **/
		triangle3d_t t = cube[i];

		t.p1 = mat4x4_vec_mult(t.p1, rx);
		t.p2 = mat4x4_vec_mult(t.p2, rx);
		t.p3 = mat4x4_vec_mult(t.p3, rx);

		t.p1 = mat4x4_vec_mult(t.p1, ry);
		t.p2 = mat4x4_vec_mult(t.p2, ry);
		t.p3 = mat4x4_vec_mult(t.p3, ry);

		t.p1 = scale_vec3d(t.p1, 70);
		t.p2 = scale_vec3d(t.p2, 70);
		t.p3 = scale_vec3d(t.p3, 70);
		/**
		 *  set the normal of the triangle;
		 **/
		tri_set_normal(&t);


		/**
		 *  move the triangle into the center of the screen
		 **/

		t.p1.x += 160;
		t.p2.x += 160;
		t.p3.x += 160;
		t.p1.y += 100;
		t.p2.y += 100;
		t.p3.y += 100;
		t.p1.z += 100;
		t.p2.z += 100;
		t.p3.z += 100;

		/**
		 *	calculate vector between point on triangle and the camera;
		 **/
		vec3d_t v_view = sub_vec3d(t.p1, camera);
		v_view = normalized(v_view);

		/**
		 *   check how this vector projects onto the
		 *   normal to the triangle;
		 **/

		if (dot_prod(t.normal, v_view) < 0.0) {
			float light = dot_prod(t.normal, normalized(light_dir));
			fill_triangle(t, with_brightness((color_t){.r=0b111, .g=0, .b=0b11}, light));
			//draw_triangle(t, COLOR_PURPLE);
		}

	}
}

void delay(uint32_t t) {
	for (size_t i = 0; i < t; i++) {
		__asm__ __volatile__("nop");
	}
}

void handle_event(event_t evt) {
	switch (evt.type) {
		case Mouse_moved:
			if (MOUSE1)
				repaint(__slow_safe_int_to_float(evt.mouse.x), __slow_safe_int_to_float(evt.mouse.y));
			prev_x = evt.mouse.x;
			prev_y = evt.mouse.y;
			break;
		case Mouse_pressed:
			switch (evt.mouse.button) {
				case MOUSE_LEFT_BUTTON:
					MOUSE1 = 1;
					display_mouse("mouse: ", "left-btn down");
					break;
				case MOUSE_RIGHT_BUTTON:
					display_mouse("mouse: ", "right-btn down");
					break;
				case MOUSE_MIDDLE_BUTTON:
					display_mouse("mouse: ", "middle-btn down");
					break;
			}
			break;
		case Mouse_released:
			switch (evt.mouse.button) {
				case MOUSE_LEFT_BUTTON:
					MOUSE1 = 0;
					display_mouse("mouse: ", "left-btn up");
					break;
				case MOUSE_RIGHT_BUTTON:
					display_mouse("mouse: ", "right-btn up");
					break;
				case MOUSE_MIDDLE_BUTTON:
					display_mouse("mouse: ", "middle-btn up");
					break;
			}
			break;
	}

}

void main() {
	//malloc_init();
	init_listener(handle_event, MOUSE_LISTENER);
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
	proj_mat = projection_matrix(NEAR, FAR, FOV, ASPECT_RATIO);

	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, (color_t){.r=0b101, .g=0b111, .b=0b11});
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
