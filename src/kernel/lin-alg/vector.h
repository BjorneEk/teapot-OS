#ifndef VECTOR_H
#define VECTOR_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../libc/include/int.h"

/**
 *   the struct used to represent points in 3d space
 *   aswell as vectors.
 *
 *   fourth component w is neccesary since 4x4 matricies
 *   are preferred in 3d graphics, w makes it possible
 *   to do vec3d X mat4x4 multiplication.
 **/
typedef struct vec3d {
	float x;
	float y;
	float z;
	float w;
} vec3d_t;

typedef struct vec2d {
	float x;
	float y;
} vec2d_t;

float length_3d(vec3d_t v);
float length_2d(vec2d_t v);

float dist_3d(vec3d_t v1, vec3d_t v2);
float dist_2d(vec2d_t v1, vec3d_t v2);

/**
 *   functions for doing arithmetic operations
 *   between vectors;
 */
vec2d_t add_vec2d(vec2d_t v1, vec2d_t v2);
vec3d_t add_vec3d(vec3d_t v1, vec3d_t v2);

vec2d_t sub_vec2d(vec2d_t v1, vec2d_t v2);
vec3d_t sub_vec3d(vec3d_t v1, vec3d_t v2);

vec2d_t mult_vec2d(vec2d_t v1, vec2d_t v2);
vec3d_t mult_vec3d(vec3d_t v1, vec3d_t v2);

//vec2d_t div_vec2d(vec2d_t v1, vec2d_t v2);
//vec3d_t div_vec3d(vec3d_t v1, vec3d_t v2);

/**
 *   functions for doing arithmetic operations
 *   between vectors and scalars;
 */
//vec3d_t add_scalar_vec3d(vec3d_t v, float scalar);
//vec2d_t add_scalar_vec2d(vec2d_t v, float scalar);

vec3d_t scale_vec3d(vec3d_t v, float scalar);
vec2d_t scale_vec2d(vec2d_t v, float scalar);

//vec2d_t to_vec2d(vec3d_t vec);
//vec3d_t to_vec3d(vec2d_t vec);


uint8_t equals_v2d(vec2d_t v1, vec2d_t v2);
uint8_t equals_v3d(vec3d_t v1, vec3d_t v2);


vec3d_t cross_prod(vec3d_t v1, vec3d_t v2);

float dot_prod(vec3d_t v1, vec3d_t v2);

void normalize(vec3d_t * v);

vec3d_t normalized(vec3d_t v);

float cmp_vec(vec3d_t v1, vec3d_t v2);

#endif /* VECTOR_H */
