// learning how to use calloc and malloc for c strings

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

int main(void) {
	
	char *c_str = (char *)calloc(2, sizeof(char));
	strcpy(c_str, "h");
	printf("%s", c_str);

	return EXIT_SUCCESS;
}
