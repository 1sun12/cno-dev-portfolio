// learning how to use calloc and malloc for c strings

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	
	char *c_str = (char *)calloc(2, sizeof(char));
	return EXIT_SUCCESS;
}
