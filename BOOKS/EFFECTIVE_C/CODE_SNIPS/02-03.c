// introduction of the bool type 

#include <stdbool.h> // bool is not a type by default; must be included
#include <stdio.h>
#include <stdlib.h>

bool arm_detonator(int ohno) {
	if (ohno == 3) return true;
	else return false;
}

void arm_missle(void) {
	bool armed = arm_detonator(3);
	if (armed) puts("Missle Armed");
	else puts("Missle Disarmed");
}

int main() {
	arm_detonator(3);
	arm_missle();
	return EXIT_SUCCESS;
}
