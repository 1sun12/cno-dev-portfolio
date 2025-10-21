#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/sockets.h>

#include <netinet/in.h>

int main(void) {
	// create sockets
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	return EXIT_SUCCESS;
}
