

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

void tri_set_normal(triangle3d_t * tri) {
	tri->normal = normalized(cross_prod(sub_vec3d(tri->p1, tri->p2), sub_vec3d(tri->p1, tri->p3)));
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

void draw_triangle(triangle3d_t tri, color_t clr) {
	draw_line((uint32_t)tri.p1.x, (uint32_t)tri.p1.y, (uint32_t)tri.p2.x, (uint32_t)tri.p2.y, clr.c);
	draw_line((uint32_t)tri.p1.x, (uint32_t)tri.p1.y, (uint32_t)tri.p3.x, (uint32_t)tri.p3.y, clr.c);
	draw_line((uint32_t)tri.p3.x, (uint32_t)tri.p3.y, (uint32_t)tri.p2.x, (uint32_t)tri.p2.y, clr.c);
}

/****************************************************************************
 ****************************************************************************
 *        for each corner draw a line from that corner                      *
 *        to each point on the line between the two other                   *
 *        corners. this fills the triangle however it is                    *
 *        not verry efficent.                                               *
 ****************************************************************************
 ****************************************************************************/
void fill_triangle(triangle3d_t triangle, color_t color) {

	float itr_cnt = 0x4f;

	/**
	 *   lerp vector p2-->p3 used to lerp through and get
	 *   second coordinate of line to draw.
	 **/
	vec3d_t lv = sub_vec3d(triangle.p2, triangle.p3);
	float i;

	for (i = 0; i < itr_cnt; i++) {
		/**
		 *   i/itr_cnt will be a number between 1 and 0
		 *   this is used to lerp throgh p2-->p3, p3 must be
		 *   added to place it in the correct final position.
		 *
		 *   funny color mode: from_radian(5*((i/itr_cnt))*PI).c
		 **/
		vec3d_t next = add_vec3d(triangle.p3, scale_vec3d(lv, i/(itr_cnt)));

		draw_line((uint32_t)triangle.p1.x, (uint32_t)triangle.p1.y, (uint32_t)next.x, (uint32_t)next.y, color.c);
	}


	/**
	 *  repeat for the other sides for a more uniform triangle;
	 **/
	lv = sub_vec3d(triangle.p2, triangle.p1);
	for (i = 0; i < itr_cnt; i++) {
		vec3d_t next = add_vec3d(triangle.p1, scale_vec3d(lv, i/(itr_cnt)));
		draw_line((uint32_t)triangle.p3.x, (uint32_t)triangle.p3.y, (uint32_t)next.x, (uint32_t)next.y, color.c);
	}
	lv = sub_vec3d(triangle.p3, triangle.p1);
	for (i = 0; i < itr_cnt; i++) {
		vec3d_t next = add_vec3d(triangle.p1, scale_vec3d(lv, i/(itr_cnt)));
		draw_line((uint32_t)triangle.p2.x, (uint32_t)triangle.p2.y, (uint32_t)next.x, (uint32_t)next.y, from_radian(5*((i/itr_cnt))*PI).c);
	}
}
