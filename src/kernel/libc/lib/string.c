

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

int32_t int_to_str(int32_t x, char str[], int32_t d) {
	int32_t i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

		reverse(str);
	str[i] = '\0';
	return i;
}

void ftoa(float n, char * res, int32_t afterpoint) {
	// Extract integer part
	int32_t ipart = (int32_t)n;

	// Extract floating part
	int32_t fpart = n - (float)ipart;

	// convert integer part to string
	int32_t i = int_to_str(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot
		/**
		*  Get the value of fraction part upto given no.
		*  of points after dot. The third parameter
		*  is needed to handle cases like 233.007
		**/
		fpart = fpart * 100;

		int_to_str((int)fpart, res + i + 1, afterpoint);
	}
}
