#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>

int main() {
	struct addrinfo hints;
	struct addrinfo *serv;
	int gai_status = -1;

	memset(&hints, 0, sizeof hints);

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	gai_status = getaddrinfo("127.0.0.1", "3322", &hints, &serv);

	return EXIT_SUCCESS;
}
