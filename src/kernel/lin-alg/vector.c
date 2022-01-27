

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#include "vector.h"
#include "../libc/include/math.h"



float length_3d(vec3d_t v) {
	return sqrt( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
}
float length_2d(vec2d_t v) {
	return sqrt( (v.x * v.x) + (v.y * v.y) );
}

float dist_3d(vec3d_t v1, vec3d_t v2) {
	return sqrt(abs( ((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) +
																		((v2.z - v1.z) * (v2.z - v1.z)) ));
}

float dist_2d(vec2d_t v1, vec3d_t v2) {
	return sqrt(abs( ((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) ));
}


vec2d_t add_vec2d(vec2d_t v1, vec2d_t v2) {
	return (vec2d_t)
	{
		.x = v1.x + v2.x,
		.y = v1.y + v2.y
	};
}
vec3d_t add_vec3d(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t)
	{
		.x = v1.x + v2.x,
		.y = v1.y + v2.y,
		.z = v1.z + v2.z
	};
}

vec2d_t sub_vec2d(vec2d_t v1, vec2d_t v2) {
	return (vec2d_t)
	{
		.x = v1.x - v2.x,
		.y = v1.y - v2.y
	};
}
vec3d_t sub_vec3d(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t)
	{
		.x = v1.x - v2.x,
		.y = v1.y - v2.y,
		.z = v1.z - v2.z
	};
}

vec2d_t mult_vec2d(vec2d_t v1, vec2d_t v2) {
	return (vec2d_t)
	{
		.x = v1.x * v2.x,
		.y = v1.y * v2.y
	};
}
vec3d_t mult_vec3d(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t)
	{
		.x = v1.x * v2.x,
		.y = v1.y * v2.y,
		.z = v1.z * v2.z
	};
}
/*
vec3d_t add_scalar_vec3d(vec3d_t v, float scalar) {
	return (vec3d_t)
	{
		.x = v.x + scalar,
		.y = v.y + scalar,
		.z = v.z + scalar
	};
}
vec2d_t add_scalar_vec2d(vec2d_t v, float scalar) {
	return (vec2d_t)
	{
		.x = v.x + scalar,
		.y = v.y + scalar
	};
}
*/
vec3d_t scale_vec3d(vec3d_t v, float scalar) {
	return (vec3d_t)
	{
		.x = v.x * scalar,
		.y = v.y * scalar,
		.z = v.z * scalar
	};
}
vec2d_t scale_vec2d(vec2d_t v, float scalar) {
	return (vec2d_t)
	{
		.x = v.x * scalar,
		.y = v.y * scalar
	};
}
/*
vec2d_t to_vec2d(vec3d_t v) {
	return (vec2d_t)
	{
		.x = v.x,
		.y = v.y
	};
}
vec3d_t to_vec3d(vec2d_t v) {
	return (vec3d_t)
	{
		.x = v.x,
		.y = v.y,
		.z = 0.0f
	};
}
*/

uint8_t equals_v2d(vec2d_t v1, vec2d_t v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}
uint8_t equals_v3d(vec3d_t v1, vec3d_t v2) {
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

vec3d_t cross_prod(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t)
	{
		.x = v1.y*v2.z - v1.z*v2.y,
		.y = v1.z*v2.x - v1.x*v2.z,
		.z = v1.x*v2.y - v1.y*v2.x
	};
}

float dot_prod(vec3d_t v1, vec3d_t v2) {
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

void normalize(vec3d_t * v) {
	float length = length_3d(*v);
	v->x = v->x/length;
	v->y = v->y/length;
	v->z = v->z/length;
}

vec3d_t normalized(vec3d_t v) {
	float length = length_3d(v);
	return (vec3d_t)
	{
		.x = v.x / length,
		.y = v.y / length,
		.z = v.z / length
	};
}
