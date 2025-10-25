// learning how to use calloc and malloc for c strings

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

// takes input ptr, and input string-literal
// sets pointer = target string literal 
void smake(char *source, char* target) {

	// if source input is NULL ? set temp source NULL : set temp source as input data
	char *t_source = source == NULL ? t_source = NULL : t_source = source;

	// if source input is NULL ? set temp target NULL : set temp target as input data
	char *t_target = target == NULL ? t_target = NULL : t_target = target;

	// size of source in bytes
	size_t source_size = sizeof(t_source);

	// size of target in bytes
	size_t target_size = sizeof(t_target);

	// reallocate new memory equal to the size of our string literal 
	t_source = (char *)realloc(t_source, sizeof(t_target));
	
	printf("smake ran successfully!");
}

int main(void) {
	
	char *c_str = (char *)calloc(2, sizeof(char));
	strcpy(c_str, "h");
	printf("%s", c_str);

	smake(c_str, c_str);

	return EXIT_SUCCESS;
}
