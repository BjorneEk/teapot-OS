

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
/*
triangle3d_t triangle_mult_matrix(triangle3d_t tri, matrix4x4_t m) {
	return (triangle3d_t) {
		.p1 = mat4x4_vec_mult(tri.p1, m),
		.p2 = mat4x4_vec_mult(tri.p2, m),
		.p3 = mat4x4_vec_mult(tri.p3, m),
		.normal = mat4x4_vec_mult(tri.normal, m)
	};
}*/


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

	float itr_cnt = 0x36;

	/**
	 *   lerp vector p2-->p3 used to lerp through and get
	 *   second coordinate of line to draw.
	 **/
	vec3d_t lv1 = sub_vec3d(triangle.p2, triangle.p3);
	vec3d_t lv2 = sub_vec3d(triangle.p2, triangle.p1);
	vec3d_t lv3 = sub_vec3d(triangle.p3, triangle.p1);
	float i;

	for (i = 0; i <= itr_cnt; i++) {
		/**
		 *   i/itr_cnt will be a number between 1 and 0
		 *   this is used to lerp throgh p2-->p3, p3 must be
		 *   added to place it in the correct final position.
		 *
		 *   in order to counterract the problem with the algorithm,
		 *   (it is much better in the corners than around the midle
		 *   and sides ot the triangle) the algorithm will create a
		 *   'fractal tree' aproach
		 *
		 *   funny color mode: from_radian(5*((i/itr_cnt))*PI).c
		 **/
		vec3d_t next1 = add_vec3d(triangle.p3, scale_vec3d(lv1, i/(itr_cnt)));
		vec3d_t next2 = add_vec3d(triangle.p1, scale_vec3d(lv2, i/(itr_cnt)));
		vec3d_t next3 = add_vec3d(triangle.p1, scale_vec3d(lv3, i/(itr_cnt)));

		draw_line((uint32_t)triangle.p1.x, (uint32_t)triangle.p1.y, (uint32_t)next1.x, (uint32_t)next1.y, color.c);
		draw_line((uint32_t)triangle.p3.x, (uint32_t)triangle.p3.y, (uint32_t)next2.x, (uint32_t)next2.y, color.c);
		draw_line((uint32_t)triangle.p2.x, (uint32_t)triangle.p2.y, (uint32_t)next3.x, (uint32_t)next3.y, color.c);

		if(i != itr_cnt) {
			vec3d_t no1 = triangle.p1;
			vec3d_t no2 = triangle.p3;
			vec3d_t no3 = triangle.p2;
			for (float j = (i)/(itr_cnt); j < (i+1)/(itr_cnt); j+=0.1) {
				no1 = add_vec3d(no1, scale_vec3d(sub_vec3d(next1, no1), 0.2));
				no2 = add_vec3d(no2, scale_vec3d(sub_vec3d(next2, no2), 0.2));
				no3 = add_vec3d(no3, scale_vec3d(sub_vec3d(next3, no3), 0.2));
				next1 = add_vec3d(triangle.p3, scale_vec3d(lv1, j));
				next2 = add_vec3d(triangle.p1, scale_vec3d(lv2, j));
				next3 = add_vec3d(triangle.p1, scale_vec3d(lv3, j));
				draw_line((uint32_t)no1.x, (uint32_t)no1.y, (uint32_t)next1.x, (uint32_t)next1.y, color.c);
				draw_line((uint32_t)no2.x, (uint32_t)no2.y, (uint32_t)next2.x, (uint32_t)next2.y, color.c);
				draw_line((uint32_t)no3.x, (uint32_t)no3.y, (uint32_t)next3.x, (uint32_t)next3.y, color.c);
			}
		}
	}
}
