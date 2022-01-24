#ifndef CURSOR_H
#define CURSOR_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../utils/include/int.h"
#include "color.h"

#define CURSOR_IMG_HEIGHT 7
#define CURSOR_IMG_WIDTH 5

typedef struct cursor_graphics {
	uint8_t img[7][5];
	color_t prev[7][5];
}cursor_t;

#endif /* CURSOR_H */
