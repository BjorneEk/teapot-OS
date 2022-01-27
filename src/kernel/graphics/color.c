
#include "color.h"
#include "../libc/include/math.h"



color_t from_radian(float r) {
	return (color_t) {
		.r    = (uint32_t)(sin(0.3f * r + 0.0f) * 4.0 + 3.0),
		.g    = (uint32_t)(sin(0.3f * r + 2.0f) * 4.0 + 3.0),
		.b    = (uint32_t)(sin(0.3f * r + 4.0f) * 2.0 + 1.0)
	};
}
