#ifndef MOUSE_H
#define MOUSE_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////


#include "../../libc/include/int.h"

/**
 *    bitfield used to interract whith the
 *    data packet recived from the mouse.
 **/
typedef struct internal_mouse_event {
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
} _internal_mouse_evt_t;

void init_mouse();

/**
 *    used for convinience to enable direct acces
 *    to the last mouse position, primarily used for
 *    drawing the cursor.
 **/
extern uint32_t __mouse_x;
extern uint32_t __mouse_y;

#endif /* MOUSE_H */
