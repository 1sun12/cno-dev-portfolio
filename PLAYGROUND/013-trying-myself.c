// server

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <cstring>

int main(void) {
	struct addrinfo hints; // template
	struct addrinfo *results; // DNS look-up results
	int gai_status = -1; // status of our DNS look-up, later
	int sock_serv = -1;
	
	memset(&hints, 0, sizeof hints); // never forget this step!
	hints.ai_flags = AI_PASSIVE; // accept connections on every interface
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_protocol = 0; // "any"
			       
	gai_status = getaddrinfo("127.0.0.1", "3322", &hints, &results);
	
	// error check to see if getaddrinfo worked
	if (gai_status != 0) {
		fprintf(stderr, "gai error: %s\n", gai_strerror(gai_status));
	}

	// were just gonna assume the first result in the linked list is safe and ready to use :)
	// normally you would for-loop through the list and error check, but Im lazy!
	
	// use results from table to create our socket
	sock_serv = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	int yes = 1;
	setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	// bind socket to a port
	bind(sock_serv, results->ai_addr, results->ai_addrlen);
	// listen on this socket
	listen(sock_serv, 10);

	printf("waiting for connections...");
	
	
}
