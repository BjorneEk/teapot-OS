
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/mouse.h"
#include "../include/ports.h"
#include "../../cpu/isr.h"
#include "../../graphics/graphics.h"
#include "../../graphics/cursor.h"
#include "../../utils/include/string.h"

#define WAIT_FOR_READ_OK 0
#define WAIT_FOR_WRITE_OK 1



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



int32_t __mouse_x = 0;
int32_t __mouse_y = 0;
uint8_t mouse_cycle = 0;
int8_t  _dx = 0;
mouse_evt_t last_evt;

void update_mouse_pos(int8_t dx, int8_t dy) {
	if ((__mouse_x + dx) > VGA_WIDTH) __mouse_x = VGA_WIDTH;
	else if ((__mouse_x + dx) < 0) __mouse_x = 0;
	else __mouse_x += dx;
	if ((__mouse_y + dy) > VGA_HEIGHT) __mouse_y = VGA_HEIGHT;
	else if ((__mouse_y + dy) < 0) __mouse_y = 0;
	else __mouse_y += dy;
	__mouse_x = __mouse_x;
	__mouse_y = __mouse_y;
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
			} else if(last_evt.left_btn) {
				display_mouse("mouse: ", "left-btn");
			}else if(last_evt.middle_btn) {
				display_mouse("mouse: ", "middle-btn");
			} else display_mouse("mouse: ", "no-btn");

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
