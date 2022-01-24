

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/string.h"


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

void int_to_string(int32_t n, char str[]) {
	int32_t i, sign;
	if ((sign = n) < 0) n = -n;
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0) str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}
