// showing off "wraparound"; a feature of unsigned int(s)

#include <limits.h> // access to macros like UCHAR_MAX, UINT_MAX, etc.
#include <stdio.h>

int main() {
	unsigned int x = UINT_MAX;
	printf("%u\n", x); // 4,294,967,295 on x86
	x++;             // add +1
	printf("%u\n", x); // should be 0
	x--; 	         // subtract -1
	printf("%u\n", x); // should be the orig. number

	return 0;
}
