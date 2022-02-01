
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/frame_buffer.h"

void init_frame_buffer(depth_buffer_t * buff) {
	for (size_t i = 0; i < FRAME_WIDTH; i++) {
		for (size_t j = 0; j < FRAME_HEIGHT; j++) {
			for (size_t k = 0; k < BUFFER_DEPTH; k++) {
				buff->d_buff[i][j][k] = NO_PIXEL;
			}
		}
	}
}

uint8_t frame_buffer_pixel_at(depth_buffer_t * buff, int16_t x, int16_t y) {
	for (size_t i = CURSOR_DEPTH; i > BACKGROUND_DEPTH; i--)
		if (buff->d_buff[x][y][i].state != STATE_INACTIVE) return buff->d_buff[x][y][i].color;
	return buff->d_buff[x][y][BACKGROUND_DEPTH].color;
}
