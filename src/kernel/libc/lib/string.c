

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/string.h"
#include "../include/math.h"



uint32_t strlen(char * s) {
	uint32_t i = 0;
	while (s[i] != '\0') ++i;
	return i;
}

void reverse(char s[]) {
	int32_t c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

uint32_t nbr_of_digits(uint32_t n) {
	uint32_t count = 0;
	for (; n != 0; n /=10) ++count;
	return count;
}

int32_t itoa(int32_t x, char str[]) {
	int32_t i;
	for (i = 0; x != 0; x /=10) str[i++] = (x % 10) + '0';
	str[i] = '\0';
	reverse(str);
	return i;
}

static float __slow_safe_int_to_float(uint32_t i) {
	float res = 0;
	for (; i > 0; i--) res += 1.0;
	return res;
}

void ftoa(float n, char str[]) {
	/**
	 *   take the part before che decimal point;
	 **/
	uint32_t i_part = (uint32_t)(n);

	/**
	 *   take remaining float part;
	 **/
	float f_i_part = __slow_safe_int_to_float(i_part);
	float f_part = (n - f_i_part);

	/**
	 *   add the int part as a string to the result
	 *   and store its length, and ad the decimal point;
	 **/
	int32_t i = itoa(i_part, str);
	str[i] = '.';
	i++;

	/**
	 *   shift up the decimal part a step at the time
	 *   in order to catch cases like  1.03;
	 **/
	for (uint8_t j = 0; j < FLOAT_PRINT_ACCURACY; j++) {
		f_part *= 10;
		if((uint32_t)f_part == 0) {
			str[i] = '0';
			i++;
		}
	}

	/**
	 * if the float part was not 0 append it to the string
	 **/
	if ((uint32_t)f_part != 0) itoa((uint32_t)f_part, str + i);
}


char * strcat(char * s1, const char *s2) {
	/**
	 *   copy char s2[] to end of s1[]
	 **/
	char *s;
	/**
	 *   go to end of s1
	 **/
	for (s = s1; *s != '\0'; ++s);
	/**
	 *   copy over s2
	 **/
	for (; (*s = *s2) != '\0'; ++s, ++s2);

	return s1;
}
