

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "triangle.h"
#include "../libc/include/math.h"


float z_avg(triangle3d_t * tri) {
	return (tri->p1.z + tri->p2.z + tri->p3.z) / 3.0;
}

uint8_t tri_contains(triangle3d_t tri, vec3d_t p) {
	return equals_v3d(tri.p1, p) || equals_v3d(tri.p2, p) || equals_v3d(tri.p3, p);
}

uint8_t equals_tri(triangle3d_t t1, triangle3d_t t2) {
	return tri_contains(t1, t2.p1) && tri_contains(t1, t2.p2) && tri_contains(t1, t2.p3);
}

vec3d_t tri_set_normal(triangle3d_t tri) {
	tri.normal = normalized(cross_prod(sub_vec3d(tri.p1, tri.p2), sub_vec3d(tri.p1, tri.p3)));
}

triangle3d_t triangle_mult_matrix(triangle3d_t tri, matrix4x4_t m) {
	return (triangle3d_t) {
		.p1 = mat4x4_vec_mult(tri.p1, m),
		.p2 = mat4x4_vec_mult(tri.p2, m),
		.p3 = mat4x4_vec_mult(tri.p3, m),
		.normal = mat4x4_vec_mult(tri.normal, m)
	};
}

triangle3d_t rotate_tri(triangle3d_t tri, float x, float y, float z) {
	matrix4x4_t rot_mat = mat4x4_mult(rot_x_mat4x4(x), rot_y_mat4x4(y));
	rot_mat = mat4x4_mult(rot_mat, rot_z_mat4x4(z));
	return triangle_mult_matrix(tri, rot_mat);
}

triangle3d_t translate_tri(triangle3d_t tri, vec3d_t pos) {
	return triangle_mult_matrix(tri, translation_matrix(pos));
}

triangle3d_t scale_tri(triangle3d_t tri, float scale) {
	return triangle_mult_matrix(tri, scaling_matrix((vec3d_t){.x=scale,.y=scale,.z=scale,.w=1}));
}

triangle3d_t project_tri(triangle3d_t tri, float near, float far, float fov, float ar) {
	return triangle_mult_matrix(tri, projection_matrix(near, far, fov, ar));
}
