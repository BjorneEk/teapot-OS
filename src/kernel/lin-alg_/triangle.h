#ifndef TRIANGLE_H
#define TRIANGLE_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../libc/include/int.h"
#include "matrix.h"


typedef struct triangle3d {
	union {
		struct {
			vec3d_t p1;
			vec3d_t p2;
			vec3d_t p3;
			vec3d_t normal;
		};
		vec3d_t p[4];
	};
} triangle3d_t;

/**
 *   average Z value in all point of trianlge
 *   this function is used to sort a mesh before
 *   it is drawn to the screen.
 **/
float z_avg(triangle3d_t * tri);

uint8_t tri_contains(triangle3d_t tri, vec3d_t p);

uint8_t equals_tri(triangle3d_t t1, triangle3d_t t2);

vec3d_t tri_set_normal(triangle3d_t tri);

triangle3d_t triangle_mult_matrix(triangle3d_t tri, matrix4x4_t m);

triangle3d_t rotate_tri(triangle3d_t tri, float x, float y, float z);

triangle3d_t translate_tri(triangle3d_t tri, vec3d_t pos);

triangle3d_t scale_tri(triangle3d_t tri, float scale);

triangle3d_t project_tri(triangle3d_t tri, float near, float far, float fov, float ar);




#endif /* triangle_H */
