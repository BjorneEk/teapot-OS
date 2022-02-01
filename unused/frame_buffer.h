#ifndef FRAME_BUFF_H
#define FRAME_BUFF_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../../libc/include/int.h"

#define FRAME_WIDTH  320
#define FRAME_HEIGHT 200


#define CURSOR_DEPTH     4
#define FIRST_WINDOW     3
#define SECOND_WINDOW    2
#define THIRD_WINDOW     1
#define BACKGROUND_DEPTH 0

#define BUFFER_DEPTH 5

#define STATE_INACTIVE 0
#define STATE_VISIBLE  1

typedef struct buffer_pixel {
	uint8_t color;
	uint8_t state;
} bpx_t;

#define NO_PIXEL (bpx_t){.color = 0, .state = STATE_INACTIVE}

/**
 *   the frame depth buffer is used by the graphics driver
 *   to enable more than one pixel on each location.
 *   this is usefull for example when having multiple windows or a cursor
 **/
typedef struct frame_depth_buffer {

	bpx_t d_buff[FRAME_WIDTH][FRAME_HEIGHT][BUFFER_DEPTH];

} depth_buffer_t;

void init_frame_buffer(depth_buffer_t * buff);

uint8_t frame_buffer_pixel_at(depth_buffer_t * buff, int16_t x, int16_t y);

#endif /* FRAME_BUFF_H */
