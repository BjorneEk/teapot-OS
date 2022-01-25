
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////


#include "../include/math.h"


float pow(float x, uint32_t p) {
	float res = x;
	for (size_t i = 0; i < p-1; i++) {
		res *= x;
	}
	return res;
}

float mod(float a, float b) {
	double mod = (a < 0) ? -a : a;
	if (b < 0) b = -b;
	// finding mod by repeated subtraction
	while (mod >= b) mod -= b;
	return (a < 0) ? -mod : mod;
}

/**
 *  Sine function based on taylor series of sin(x)
 *
 *  the function __taylor_sin is fairly accurate between -PI/3 and PI;
 *
 *  the sine function uses further logic to extend this range for ex since sin(-x) == -sin(x)
 *  the accuracy can be improved to -PI to PI;
 *
 * see docs/sin.txt for comparison with math.h sin(x); and graphical comparison
 * between __taylor_sin(x) and sin(x)
 **/

float __taylor_sin(float x){
	return (1.00003 * x) - (0.000312267 * x*x) -
		(0.165537 * pow(x, 3)) - (0.00203937 * pow(x, 4)) +
			(0.010286 * pow(x, 5)) - (0.000961693 * pow(x, 6));
}

float sin(float x){
	uint8_t sign;
	float _x = (sign = (x < 0)) ? -x : x;
	sign = ((!(((uint32_t)(x / (float)(PI))) % 2)) == sign);
	_x = mod(_x, PI);
	return (sign) ? -__taylor_sin(_x) : __taylor_sin(_x);
}
