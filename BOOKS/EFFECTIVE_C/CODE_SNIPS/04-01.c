// Pg. 80 explains the "Order of Evaluation" in case 
// below is an example of the unspecificed order in Evaluation
// running this program will give you different results each time 
// requires a re-compile each time 
// because of hardware implications, just pretend that you re-compile and you'll either get 10 or 52

#include <stdio.h>
#include <stdlib.h>

int glob; // static storage initialized to 0

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int f(void) {
	return glob + 10;
}

int g(void) {
	glob = 42;
	return glob;
}

int main(void) {

	// both f() and g() access a global var glob
	// if f() is called first, it will return 10
	// if g() is called first, it will return 52
	int max_value = max(f(), g());
	printf("max value: %d\n", max_value);

	return EXIT_SUCCESS;
}
