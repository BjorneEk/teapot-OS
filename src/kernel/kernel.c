

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


uint8_t SHELL_MODE = true;
uint8_t DRAW_MODE = false;

char cmd[100];
uint8_t cmd_len = 0;

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
void animate() {
	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
		for (float x = 0; x < VGA_WIDTH + 70; x++) {
			for (size_t y_off = 0; y_off < 54; y_off++) {
				float y;
				if(x < VGA_WIDTH) {
					y =2.0f + ((sin(x/30) + sin(x/15)) * 30);
						fill_rect((uint32_t)x, (uint32_t)y + (y_off*5), 1, 1, from_radian(x/2));
				}
				if (x >= 70) {
					y =2.0f + ((sin((x-150)/30) + sin((x-150)/15)) * 30);
						fill_rect((uint32_t)(x-70), (uint32_t)y + (y_off*5), 1, 1, COLOR_BLACK);
				}
			}

		delay(0x4FFFFF);
	}
	SHELL_MODE = true;
	clear();
}

void handle_event(event_t evt) {
	switch (evt.type) {
		case Mouse_moved:
			if (DRAW_MODE) {
				if (MOUSE1)
					repaint(__slow_safe_int_to_float(evt.mouse.x), __slow_safe_int_to_float(evt.mouse.y));
				prev_x = evt.mouse.x;
				prev_y = evt.mouse.y;
			}
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
		case Key_pressed:
			if(SHELL_MODE) {
				switch (evt.key.scancode) {
					case KEY_ENTER:
						cmd[cmd_len] = '\0';
						cmd_len++;
						new_line();
						if(!strcmp(cmd, "draw")) {

							print(cmd, COLOR_GREEN);
							delay(0x4FFFFFF);
							DRAW_MODE = true;
							SHELL_MODE = false;
							fill_rect(0, STATUS_BAR_HEIGHT, VGA_WIDTH, VGA_HEIGHT-STATUS_BAR_HEIGHT, (color_t){.r=0b101, .g=0b111, .b=0b11});
							new_line();

						} else if (!strcmp(cmd, "ls")){

							print("draw  ", COLOR_PURPLE);
							print("help  ", COLOR_WHITE);
							print("ls  ", COLOR_WHITE);
							print("clear  ", COLOR_WHITE);
							print("scroll  ", COLOR_WHITE);
							print("animate  ", COLOR_PURPLE);
							new_line();

						} else if (!strcmp(cmd, "clear")){

							clear();

						} else if (!strcmp(cmd, "debug")){

							debug();

						} else if (!strcmp(cmd, "animate")){

							SHELL_MODE = false;
							animate();

						} else if (!strcmp(cmd, "scroll")){

							scroll();

						} else if (!strcmp(cmd, "help")){

							print("teapot-os help menu:", COLOR_YELLOW);
							new_line();
							print("type : ", COLOR_WHITE);
							print("ls   ", COLOR_GREEN);
							print("to list available commands", COLOR_WHITE);
							new_line();

						} else {
							print("tea-shell: ", COLOR_WHITE);
							print(cmd, COLOR_RED);
							print(", unrecognized command", COLOR_WHITE);
							new_line();
						}
						prompt();
						cmd_len = 0;
						break;
					case KEY_BACKSPACE:
						cmd_len--;
						print_backspace();
						break;
					default:
						char str[5];
						itoa(evt.key.scancode, str);
						set_last_key(str);
						break;
				}
				if(evt.key.key_char != UNKNOWN_SCANCODE_CHAR) {
					cmd[cmd_len] = evt.key.key_char;
					cmd_len++;
					append_char(evt.key.key_char, COLOR_WHITE);
				}

			} else {
				if (evt.key.scancode == KEY_ESCAPE) {
					SHELL_MODE = true;
					DRAW_MODE = false;
					fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
					set_cursor(2, 2);
					print("Welcome to teapot-OS\n -", COLOR_WHITE);
				}
			}
			break;
		case Key_released:
			break;
	}
}

void main() {
	malloc_init();
	init_listener(handle_event, GLOBAL_LISTENER);
	init_VGA_driver();
	isr_install();
	__asm__ __volatile__("sti");
	init_keyboard();
	init_mouse();
	proj_mat = projection_matrix(NEAR, FAR, FOV, ASPECT_RATIO);

	fill_rect(0, 0, VGA_WIDTH, VGA_HEIGHT, COLOR_BLACK);
	set_os_name("teapot-os");
	set_cursor(2, 2);
	print("Welcome to teapot-OS\n -", COLOR_WHITE);
}
