#ifndef MOUSE_H
#define MOUSE_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////


#include "../../libc/include/int.h"

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

void init_mouse();

extern int32_t __mouse_x;
extern int32_t __mouse_y;

extern float x_angle;
extern float y_angle;


#endif /* MOUSE_H */
