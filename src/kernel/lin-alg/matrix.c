

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////
#include "matrix.h"
#include "../libc/include/math.h"
#include "../libc/include/string.h"

/*
matrix3x3_t rot_x_mat3x3(float v) {
	return (matrix3x3_t)
	{
		.r1 = {1.0f,   0.0f,    0.0f},
		.r2 = {0.0f, cos(v), -sin(v)},
		.r3 = {0.0f, sin(v),  cos(v)}
	};
}
matrix3x3_t rot_y_mat3x3(float v) {
	return (matrix3x3_t)
	{
		.r1 = { cos(v), 0.0f, sin(v)},
		.r2 = {   0.0f, 1.0f,   0.0f},
		.r3 = {-sin(v), 0.0f, cos(v)}
	};
}
matrix3x3_t rot_z_mat3x3(float v) {
	return (matrix3x3_t)
	{
		.r1 = {cos(v), -sin(v), 0.0f},
		.r2 = {sin(v),  cos(v), 0.0f},
		.r3 = {  0.0f,    0.0f, 1.0f}
	};
}

matrix4x4_t rot_x_mat4x4(float v) {
	return (matrix4x4_t)
	{
		.m[0] = {1.0f,   0.0f,    0.0f, 0.0f},
		.m[1] = {0.0f, cos(v), -sin(v), 0.0f},
		.m[2] = {0.0f, sin(v),  cos(v), 0.0f},
		.m[3] = {0.0f,   0.0f,    0.0f, 1.0f}
	};
}
matrix4x4_t rot_y_mat4x4(float v) {
	return (matrix4x4_t)
	{
		.m[0] = { cos(v), 0.0f, sin(v), 0.0f},
		.m[1] = {   0.0f, 1.0f,   0.0f, 0.0f},
		.m[2] = {-sin(v), 0.0f, cos(v), 0.0f},
		.m[3] = {   0.0f, 0.0f,   0.0f, 1.0f}
	};
}
matrix4x4_t rot_z_mat4x4(float v) {
	return (matrix4x4_t)
	{
		.m[0] = {cos(v), -sin(v), 0.0f, 0.0f},
		.m[1] = {sin(v),  cos(v), 0.0f, 0.0f},
		.m[2] = {  0.0f,    0.0f, 1.0f, 0.0f},
		.m[3] = {  0.0f,    0.0f, 0.0f, 1.0f}
	};
}

matrix4x4_t translation_matrix(vec3d_t pos) {
	return (matrix4x4_t)
	{
		.m[0] = {1.0f, 0.0f, 0.0f, pos.x},
		.m[1] = {0.0f, 1.0f, 0.0f, pos.y},
		.m[2] = {0.0f, 0.0f, 1.0f, pos.z},
		.m[3] = {0.0f, 0.0f, 0.0f,  1.0f}
	};
}

matrix4x4_t scaling_matrix(vec3d_t xyz_scale) {
	return (matrix4x4_t)
	{
		.m[0] = {xyz_scale.x,        0.0f,        0.0f, 0.0f},
		.m[1] = {       0.0f, xyz_scale.y,        0.0f, 0.0f},
		.m[2] = {       0.0f,        0.0f, xyz_scale.z, 0.0f},
		.m[3] = {       0.0f,        0.0f,        0.0f, 1.0f}
	};
}
*/
matrix4x4_t projection_matrix(float near, float far, float fov, float ar){
	return (matrix4x4_t)
	{
		.m[0] = {ar * 12.53983, 0.0f    , 0.0f                       , 0.0f},
		.m[1] = {0.0f         , 12.53983, 0.0f                       , 0.0f},
		.m[2] = {0.0f         , 0.0f    , far / (far - near)         , 1.0f},
		.m[3] = {0.0f         , 0.0f    , (-far * near) / (far- near), 0.0f}
	};
}

vec3d_t mat4x4_vec_mult(vec3d_t v, matrix4x4_t m) {
	return (vec3d_t)
	{
		.x = (v.x * m.m[0][0]) + (v.y * m.m[1][0]) + (v.z * m.m[2][0]),
		.y = (v.x * m.m[0][1]) + (v.y * m.m[1][1]) + (v.z * m.m[2][1]),
		.z = (v.x * m.m[0][2]) + (v.y * m.m[1][2]) + (v.z * m.m[2][2]),
	};
}

void project_vec(vec3d_t * v, matrix4x4_t m) {
	vec3d_t i = *v;
	v->x    = (i.x * m.m[0][0]) + (i.y * m.m[1][0]) + (i.z * m.m[2][0]) + m.m[3][0];
	v->y    = (i.x * m.m[0][1]) + (i.y * m.m[1][1]) + (i.z * m.m[2][1]) + m.m[3][1];
	v->z    = (i.x * m.m[0][2]) + (i.y * m.m[1][2]) + (i.z * m.m[2][2]) + m.m[3][2];
	float w = (i.x * m.m[0][3]) + (i.y * m.m[1][3]) + (i.z * m.m[2][3]) + m.m[3][3];
	if (w >= 0) {
		v->x /= w;
		v->y /= w;
		v->z /= w;
	}
}

vec3d_t mat3x3_vec_mult(vec3d_t v, matrix3x3_t m) {
	return (vec3d_t)
	{
		.x = (m.m[0][0] * v.x) + (m.m[1][0] * v.y) + (m.m[2][0] * v.z),
		.y = (m.m[0][1] * v.x) + (m.m[1][1] * v.y) + (m.m[2][1] * v.z),
		.z = (m.m[0][2] * v.x) + (m.m[1][2] * v.y) + (m.m[2][2] * v.z),
	};
}
/*
matrix4x4_t mat4x4_mult(matrix4x4_t m1, matrix4x4_t m2) {
	matrix4x4_t res;
	for (uint8_t i = 0; i < 4; i++) {
		for (uint8_t j = 0; j < 4; j++) {
			res.m[i][j] = 0.0f;
			for (uint8_t k = 0; k < 4; k++) {
				res.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return res;
}

matrix3x3_t mat3x3_mult(matrix3x3_t m1, matrix3x3_t m2) {
	matrix3x3_t res;
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t j = 0; j < 3; j++) {
			res.m[i][j] = 0.0f;
			for (uint8_t k = 0; k < 3; k++) {
				res.m[i][j] += m1.m[i][j] * m2.m[k][j];
			}
		}
	}
	return res;
}
*/
void mat4x4_to_str(matrix4x4_t m, char str[]) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			char v[8];
			ftoa(m.m[i][j], v);
			strcat(str, v);
			strcat(str, " : ");
		}
		strcat(str, "\n");
	}
}
