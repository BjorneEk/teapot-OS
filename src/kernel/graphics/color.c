
#include "color.h"
#include "../libc/include/math.h"

/*
typedef struct color {
	union{
		uint8_t c;
		struct {
			uint8_t b : 2; // 0, 1, 2, 3 0 <-> 3
			uint8_t g : 3; // 0, 1, 2, 3, 4, 5, 6, 7 0 <-> 7
			uint8_t r : 3; // 0, 1, 2, 3, 4, 5, 6, 7 0 <-> 7
		};
	};
} color_t;
*/

color_t from_radian(float r) {
	return (color_t) {
		.r    = (uint32_t)(sin(0.3f * r + 0.0f) * 4.0 + 3.0),
		.g    = (uint32_t)(sin(0.3f * r + 2.0f) * 4.0 + 3.0),
		.b    = (uint32_t)(sin(0.3f * r + 4.0f) * 2.0 + 1.0)
	};
}
