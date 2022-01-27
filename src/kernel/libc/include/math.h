#ifndef MATH_H
#define MATH_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "int.h"

#define PI 3.14159265358979323

#define abs(v) (((v) < (0)) ? -(v) : (v))

int32_t floor(float x);

int32_t ceil(float x);

float pow(float x, uint32_t p);

float mod(float a, float b);

float sin(float x);

float cos(float x);

float tan(float x);

float sqrt(float x);



#endif /* MATH_H */
