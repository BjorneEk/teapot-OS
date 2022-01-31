
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/mouse.h"
#include "../include/event.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../graphics/cursor.h"
#include "../../libc/include/string.h"

#include "../../libc/include/math.h"

#include "../../lin-alg/triangle.h"

#define WAIT_FOR_READ_OK 0
#define WAIT_FOR_WRITE_OK 1

uint32_t __mouse_x = 0;
uint32_t __mouse_y = 0;

uint8_t mouse_cycle = 0;
int8_t  _dx = 0;
_internal_mouse_evt_t last_evt;

uint8_t LEFT_BUTTON = 0;
uint8_t RIGHT_BUTTON = 0;
uint8_t MIDDLE_BUTTON = 0;


void update_mouse_pos(int8_t dx, int8_t dy) {

	if (__mouse_x < abs(dx) && dx < 0) __mouse_x = 0;
	else if (__mouse_x + dx > VGA_WIDTH - CURSOR_IMG_WIDTH) __mouse_x = VGA_WIDTH-CURSOR_IMG_WIDTH;
	else __mouse_x += dx;

	if (__mouse_y < abs(dy) && dy < 0) __mouse_y = 0;
	else if (__mouse_y + dy > VGA_HEIGHT - CURSOR_IMG_HEIGHT) __mouse_y = VGA_HEIGHT-CURSOR_IMG_HEIGHT;
	else __mouse_y += dy;

	event_t evt;
	evt.mouse.x = __mouse_x;
	evt.mouse.y = __mouse_y;


	if(last_evt.left_btn && !LEFT_BUTTON) {
		evt.mouse.button = MOUSE_LEFT_BUTTON;
		evt.type = Mouse_pressed;
	}
	else if (last_evt.right_btn && !RIGHT_BUTTON) {
		evt.mouse.button = MOUSE_RIGHT_BUTTON;
		evt.type = Mouse_pressed;
	}
	else if (last_evt.middle_btn && !MIDDLE_BUTTON) {
		evt.mouse.button = MOUSE_MIDDLE_BUTTON;
		evt.type = Mouse_pressed;
	}
	else if(LEFT_BUTTON && !last_evt.left_btn) {
		evt.mouse.button = MOUSE_LEFT_BUTTON;
		evt.type = Mouse_released;
	}
	else if(RIGHT_BUTTON && !last_evt.right_btn) {
		evt.mouse.button = MOUSE_RIGHT_BUTTON;
		evt.type = Mouse_released;
	}
	else if(MIDDLE_BUTTON && !last_evt.middle_btn) {
		evt.mouse.button = MOUSE_MIDDLE_BUTTON;
		evt.type = Mouse_released;
	} else
		evt.type = Mouse_moved;

	/*if (LEFT_BUTTON != last_evt.left_btn) {
		evt.mouse.button = MOUSE_LEFT_BUTTON;
		evt.type = (MOUSE_LEFT_BUTTON) ? Mouse_released : Mouse_pressed;
	} else if (RIGHT_BUTTON != last_evt.right_btn) {
		evt.mouse.button = MOUSE_RIGHT_BUTTON;
		evt.type = (MOUSE_RIGHT_BUTTON) ? Mouse_released : Mouse_pressed;
	} else if (MIDDLE_BUTTON != last_evt.middle_btn) {
		evt.mouse.button = MOUSE_MIDDLE_BUTTON;
		evt.type = (MOUSE_MIDDLE_BUTTON) ? Mouse_released : Mouse_pressed;
	}*/
	refresh_cursor(__mouse_x, __mouse_y);
	create_mouse_event(evt);
	//refresh_cursor(__mouse_x, __mouse_y);
	LEFT_BUTTON   = last_evt.left_btn;
	RIGHT_BUTTON  = last_evt.right_btn;
	MIDDLE_BUTTON = last_evt.middle_btn;
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
