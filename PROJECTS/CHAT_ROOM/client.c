#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // sockets API 
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
	const char* ip = "172.253.63.27";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(80); // ports are unsigned-shorts (2 byte number); TCP requires BIG ENDIAN formatting, ty htons
	inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
	int result = connect(socket_fd, &address, sizeof (address));
	
	if (result == 0) printf("connection was successful\n");
	return EXIT_SUCCESS;
}
