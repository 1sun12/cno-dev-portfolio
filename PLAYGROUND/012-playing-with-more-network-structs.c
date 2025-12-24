// sample call if you're a client who wants to connect to a server
// say for example "google.com" on port 80
// this doesn't actually connect, it just sets up the NETWORK STRUCTS

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <cstring>

int main() {
int status;
struct addrinfo hints;
struct addrinfo *servinfo; // will point to results from getaddrinfo()

// zero-out the hints struct (first-step)
memset(&hints, 0, sizeof hints);

// set necessary information
hints.ai_family = AF_INET; // IPV4
hints.ai_socktype = SOCK_STREAM; // TCP

status = getaddrinfo("www.google.com", "80", &hints, &servinfo);

if (status == 0){
	char ip4[INET_ADDRSTRLEN];
	struct sockaddr_in *address = (struct sockaddr_in *)servinfo->ai_addr;
	inet_ntop(AF_INET, &(address->sin_addr), ip4, INET_ADDRSTRLEN);
	printf("IPv4 Address: %s\n", ip4);
}

return EXIT_SUCCESS;
}

