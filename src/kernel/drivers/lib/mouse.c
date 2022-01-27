
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/mouse.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../graphics/cursor.h"
#include "../../libc/include/string.h"

#include "../../libc/include/math.h"

#include "../../lin-alg/triangle.h"

#define WAIT_FOR_READ_OK 0
#define WAIT_FOR_WRITE_OK 1

triangle3d_t cube[] = {
	{.p1={-0.5f, -0.5f, -0.5f,  1.0f}, .p2={-0.5f,  0.5f, -0.5f,  1.0f}, .p3={ 0.5f, -0.5f, -0.5f,  1.0f}},
	{.p1={-0.5f,  0.5f, -0.5f,  1.0f}, .p2={ 0.5f,  0.5f, -0.5f,  1.0f}, .p3={ 0.5f, -0.5f, -0.5f,  1.0f}},
	{.p1={ 0.5f, -0.5f, -0.5f,  1.0f}, .p2={ 0.5f,  0.5f, -0.5f,  1.0f}, .p3={ 0.5f, -0.5f,  0.5f,  1.0f}},
	{.p1={ 0.5f,  0.5f, -0.5f,  1.0f}, .p2={ 0.5f,  0.5f,  0.5f,  1.0f}, .p3={ 0.5f, -0.5f,  0.5f,  1.0f}},
	{.p1={ 0.5f, -0.5f,  0.5f,  1.0f}, .p2={ 0.5f,  0.5f,  0.5f,  1.0f}, .p3={-0.5f, -0.5f,  0.5f,  1.0f}},
	{.p1={ 0.5f,  0.5f,  0.5f,  1.0f}, .p2={-0.5f,  0.5f,  0.5f,  1.0f}, .p3={-0.5f, -0.5f,  0.5f,  1.0f}},
	{.p1={-0.5f, -0.5f,  0.5f,  1.0f}, .p2={-0.5f,  0.5f,  0.5f,  1.0f}, .p3={-0.5f, -0.5f, -0.5f,  1.0f}},
	{.p1={-0.5f,  0.5f,  0.5f,  1.0f}, .p2={-0.5f,  0.5f, -0.5f,  1.0f}, .p3={-0.5f, -0.5f, -0.5f,  1.0f}},
	{.p1={-0.5f,  0.5f, -0.5f,  1.0f}, .p2={-0.5f,  0.5f,  0.5f,  1.0f}, .p3={ 0.5f,  0.5f,  0.5f,  1.0f}},
	{.p1={ 0.5f,  0.5f,  0.5f,  1.0f}, .p2={ 0.5f,  0.5f, -0.5f,  1.0f}, .p3={-0.5f,  0.5f, -0.5f,  1.0f}},
	{.p1={-0.5f, -0.5f,  0.5f,  1.0f}, .p2={-0.5f, -0.5f, -0.5f,  1.0f}, .p3={ 0.5f, -0.5f, -0.5f,  1.0f}},
	{.p1={ 0.5f, -0.5f, -0.5f,  1.0f}, .p2={ 0.5f, -0.5f,  0.5f,  1.0f}, .p3={-0.5f, -0.5f,  0.5f,  1.0f}},
};



typedef struct mouse_event {
	union {
		uint8_t b;
		struct {
			uint8_t left_btn   : 1;
			uint8_t right_btn  : 1;
			uint8_t middle_btn : 1;
			uint8_t always_one : 1;
			uint8_t x_overflow : 1;
			uint8_t y_overflow : 1;
			uint8_t x_sign     : 1;
			uint8_t y_sign     : 1;
		};
	};
} mouse_evt_t;

float NEAR = 0.1f;
float FAR  = 1000.0f;
float FOV  = 90.0f;
float ASPECT_RATIO = 200.0f / 320.0f;

int32_t __mouse_x = 0;
int32_t __mouse_y = 0;

int32_t prev_mx = 0;
int32_t prev_my = 0;
uint8_t mouse_cycle = 0;
int8_t  _dx = 0;
mouse_evt_t last_evt;

float x_angle = 0.0;
float y_angle = 0.0;

uint8_t LEFT_BUTTON = 0;
uint8_t RIGHT_BUTTON = 0;


void repaint(){
	fill_rect(0, STATUS_BAR_HEIGHT, VGA_WIDTH, VGA_HEIGHT-STATUS_BAR_HEIGHT, COLOR_BLACK);
	x_angle += ((float)__mouse_x - (float)prev_mx) / 100.0f;
	y_angle += ((float)__mouse_y - (float)prev_my) / 100.0f;
	float cos_x = cos(x_angle);
	float sin_x = sin(x_angle);
	float cos_y = cos(y_angle);
	float sin_y = sin(y_angle);
	prev_my = __mouse_y;
	prev_mx = __mouse_x;
	matrix4x4_t rx = (matrix4x4_t) {
		.m[0] = {1.0f,  0.0f,   0.0f, 0.0f},
		.m[1] = {0.0f, cos_y, -sin_y, 0.0f},
		.m[2] = {0.0f, sin_y,  cos_y, 0.0f},
		.m[3] = {0.0f,   0.0f,  0.0f, 1.0f}
	};
	matrix4x4_t ry = (matrix4x4_t) {
		.m[0] = { cos_x, 0.0f, sin_x, 0.0f},
		.m[1] = {  0.0f, 1.0f,  0.0f, 0.0f},
		.m[2] = {-sin_x, 0.0f, cos_x, 0.0f},
		.m[3] = {  0.0f, 0.0f,  0.0f, 1.0f}
	};
	matrix4x4_t scale_mat = (matrix4x4_t) {
		.m[0] = {70.0f, 0.0, 0.0f, 0.0f},
		.m[1] = {0.0,  70.0f, 0.0f, 0.0f},
		.m[2] = {0.0f, 0.0f, 70.0f, 0.0f},
		.m[3] = {0.0f, 0.0f, 0.0f, 1.0f}
	};
	matrix4x4_t c_mat = mat4x4_mult(rx, ry);
	c_mat = mat4x4_mult(c_mat, scale_mat);
	for (size_t i = 0; i < 12; i++) {
		triangle3d_t transformed = triangle_mult_matrix(cube[i], c_mat);
		transformed.p1.x += 160;
		transformed.p2.x += 160;
		transformed.p3.x += 160;
		transformed.p1.y += 100;
		transformed.p2.y += 100;
		transformed.p3.y += 100;

		tri_set_normal(&transformed);
		draw_triangle(transformed, COLOR_BLUE);
	}
}

void update_mouse_pos(int8_t dx, int8_t dy) {
	if ((__mouse_x + dx) > VGA_WIDTH) __mouse_x = VGA_WIDTH;
	else if ((__mouse_x + dx) < 0) __mouse_x = 0;
	else __mouse_x += dx;
	if ((__mouse_y + dy) > VGA_HEIGHT) __mouse_y = VGA_HEIGHT;
	else if ((__mouse_y + dy) < 0) __mouse_y = 0;
	else __mouse_y += dy;
	__mouse_x = __mouse_x;
	__mouse_y = __mouse_y;
	if(LEFT_BUTTON) {
		repaint();
	} else {
		prev_my = __mouse_y;
		prev_mx = __mouse_x;
	}
}


//Mouse functions
void mouse_callback(registers_t *regs) {
	switch(mouse_cycle) {
		case 0:
			last_evt.b = in_portb(0x60);
			mouse_cycle++;
			break;
		case 1:
			_dx = in_portb(0x60);
			mouse_cycle++;
			break;
		case 2:
			update_mouse_pos(_dx, -in_portb(0x60));
			mouse_cycle=0;
			if(last_evt.right_btn) {
				display_mouse("mouse: ", "right-btn");
				RIGHT_BUTTON = 1;
			} else if(last_evt.left_btn) {
				display_mouse("mouse: ", "left-btn");
				LEFT_BUTTON = 1;
			}else if(last_evt.middle_btn) {
				display_mouse("mouse: ", "middle-btn");
			} else {
				display_mouse("mouse: ", "no-btn");
				LEFT_BUTTON = 0;
				RIGHT_BUTTON = 0;
			}

			refresh_cursor(__mouse_x, __mouse_y);
			break;
	}
}

void mouse_wait(uint8_t a_type) {
	uint32_t _time_out = 100000; //unsigned int
	if(a_type==0) {
		while(_time_out--)
			if((in_portb(0x64) & 1)==1) return;
		return;
	} else {
		while(_time_out--) //Signal
			if((in_portb(0x64) & 2)==0) return;
		return;
	}
}


void mouse_write(uint8_t a_write) {
	//Wait to be able to send a command
	mouse_wait(WAIT_FOR_WRITE_OK);
	//Tell the mouse we are sending a command
	out_portb(0x64, 0xD4);
	//Wait for the final part
	mouse_wait(WAIT_FOR_WRITE_OK);
	//Finally write
	out_portb(0x60, a_write);
}

uint8_t mouse_read() {
	//Get's response from mouse
	mouse_wait(WAIT_FOR_READ_OK);
	return in_portb(0x60);
}

void init_mouse() {
	uint8_t _status;  //unsigned char

	//Enable the auxiliary mouse device
	mouse_wait(WAIT_FOR_WRITE_OK);
	out_portb(0x64, 0xA8);

	//Enable the interrupts
	mouse_wait(WAIT_FOR_WRITE_OK);
	out_portb(0x64, 0x20);
	mouse_wait(WAIT_FOR_READ_OK);
	_status = (in_portb(0x60) | 2);
	mouse_wait(WAIT_FOR_WRITE_OK);
	out_portb(0x64, 0x60);
	mouse_wait(WAIT_FOR_WRITE_OK);
	out_portb(0x60, _status);

	//Tell the mouse to use default settings
	mouse_write(0xF6);
	mouse_read();  //Acknowledge

	//Enable the mouse
	mouse_write(0xF4);
	mouse_read();  //Acknowledge

	//Setup the mouse handler
	register_interrupt_handler(IRQ12, mouse_callback);
}
