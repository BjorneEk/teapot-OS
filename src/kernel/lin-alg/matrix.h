#ifndef MATRIX_H
#define MATRIX_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../libc/include/int.h"
#include "vector.h"

typedef struct matrix3x3 {
	union {
		struct {
			vec3d_t r1;
			vec3d_t r2;
			vec3d_t r3;
		};
		float m[3][3];
	};
} matrix3x3_t;

typedef struct matrix4x4 {
	float m[4][4];
} matrix4x4_t;



matrix3x3_t rot_x_mat3x3(float v);
matrix3x3_t rot_y_mat3x3(float v);
matrix3x3_t rot_z_mat3x3(float v);

matrix4x4_t rot_x_mat4x4(float v);
matrix4x4_t rot_y_mat4x4(float v);
matrix4x4_t rot_z_mat4x4(float v);

matrix4x4_t translation_matrix(vec3d_t pos);
matrix4x4_t scaling_matrix(vec3d_t xyz_scale);

matrix4x4_t projection_matrix(float near, float far, float fov, float ar);

void mat4x4_to_str(matrix4x4_t m, char str[]);

void project_vec(vec3d_t * v, matrix4x4_t m);


/**
 *  not true v3d * m4x4 multiplication
 *  but special case used for projection
 **/
vec3d_t mat4x4_vec_mult(vec3d_t v, matrix4x4_t m);
vec3d_t mat3x3_vec_mult(vec3d_t v, matrix3x3_t m);

matrix4x4_t mat4x4_mult(matrix4x4_t m1, matrix4x4_t m2);
matrix3x3_t mat3x3_mult(matrix3x3_t m1, matrix3x3_t m2);

#endif /* MATRIX_H */
