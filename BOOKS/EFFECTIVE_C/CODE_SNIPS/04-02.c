// an example showcasing size_t and sizeof()

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // by default it belongs to this header file
#include <climits> // CHAR_BIT

int main(void) {
	int x;
	size_t x_size = sizeof(x);	// the size of the object x in bytes
	size_t int_size = sizeof(int);	// the size of the type int in bytes

	int y = 5;
	size_t y_size_bit = CHAR_BIT * sizeof(y);	// the size of the object y in bits
	size_t int_size_bit = CHAR_BIT * sizeof(int);	// the size of the type int in bits

	printf("x size: %lu\nint size: %lu\n\ny size bits: %lu\nint size bits: %lu\n", x_size, int_size, y_size_bit, int_size_bit);
	
	return EXIT_SUCCESS;
}

