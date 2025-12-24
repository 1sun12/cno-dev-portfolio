#include <stdlib.h>
#include <stdio.h>
#include <netdb.h> // defines struct addrinfo
#include <sys/types.h>
#include <sys/socket.h> // defines the socket sys call
#include <cstring> // defines "memset()"

int main() {
	struct addrinfo hints; // template for dns lookup
	struct addrinfo *res; // linked-list to the results of the dns lookup
	int status_gai = -1;
	int status_connect = -1;

	// clear garbage memory from hints
	memset(&hints, 0, sizeof hints);

	// fill out the hints template
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET; // ipv4
	hints.ai_socktype = SOCK_STREAM; // tcp
	hints.ai_protocol = 0; // "any"
	
	status_gai = getaddrinfo("127.0.0.1", "3322", &hints, &res);
	if (status_gai == 0) puts("gai was successful!");

	// create a socket will be sending messages over
	int soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// connect to a listening server using our new socket!
	status_connect = connect(soc, res->ai_addr, res->ai_addrlen);

	// attempt to send a TCP message to that Ipv4 over our newly connected socket
	char *msg = "MY MOTHERFUCKING TCP IPV4 COMMUNICATION IS WORKING!!!!";
	int len, bytes_sent;
	len = strlen(msg);
	bytes_sent = send(soc, msg, len, 0);


	puts("exiting...");
	return EXIT_SUCCESS;
}
