#ifndef MOUSE_H
#define MOUSE_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#include "../../libc/include/int.h"

void init_mouse();

extern int32_t __mouse_x;
extern int32_t __mouse_y;

extern float x_angle;
extern float y_angle;


#endif /* MOUSE_H */
