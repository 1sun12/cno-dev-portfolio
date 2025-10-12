// swap function, BUT NOW, at the memory level with pointers!

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int t = 0;
	t = *a;  // store the a-val
	a = b; // set a-addr to b-addr
	*b = t;	 // set b-val to original a-val
	printf("swap: a = %d, b = %d\n", *a, *b);
}

int main() {
	int a = 21;
	int b = 17;
	swap(&a, &b);
	printf("main: a = %d, b = %d\n", a, b);
	return EXIT_SUCCESS;
}
