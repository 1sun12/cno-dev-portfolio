// learning how to use calloc and malloc for c strings

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

// takes input ptr, and input string-literal
// sets pointer = target string literal 
void smake(char **source, const char* target) {
	printf("[DEBUG] source bytes before: %lu\n", strlen(*source));
	char *temp = (char *)malloc(strlen(target) + 1);
	strcpy(temp, target);
	printf("[DEBUG] temp strcpy: %s\n", temp);
	if (*source != NULL) free(*source);
	*source = temp;
	printf("[DEBUG] source bytes after: %lu\n", strlen(*source));
	puts("[DEBUG] smake ran successfully!");
}

int main(void) {
	
	char *c_str = (char *)calloc(6, sizeof(char));
	strcpy(c_str, "hello");
	printf("[DEBUG] c_str before: %s\n", c_str);
	smake(&c_str, "hello!hello!hello!hello!");
	printf("[DEBUG] c_str after: %s\n", c_str);

	return EXIT_SUCCESS;
}
