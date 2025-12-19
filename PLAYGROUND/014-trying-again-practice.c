#include <stdlib.h> // some helpful C macros
#include <stdio.h> // basic C input and output
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> // defines "struct addrinfo" 
#include <cstring> // defines "memset()"

#define BACKLOG 10 // the amount of connections that can queue for the listening socket

int main() {
	struct addrinfo hints; // template for DNS lookup
	struct addrinfo *res; // results from the DNS lookup
	int status_gai = -1; // did the address lookup fail or not?
	int status_bind = -1; // did the address fail or not?
	int status_listen = -1; // did the listen fail or not?
	
	memset(&hints, 0, sizeof hints); // cleans up the memory space of hints
	hints.ai_flags = AI_PASSIVE; // any interface
	hints.ai_family = AF_INET; // ipv4
	hints.ai_socktype = SOCK_STREAM; // tcp
	
	status_gai = getaddrinfo("127.0.0.1", "3322", &hints, &res);

	if (status_gai == 0) printf("DNS lookup successful!\n");

	// create a socket using the results of the lookup
	int soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// bind on the port used in the getaddrinfo - step 1 in creating a simple stream server
	status_bind = bind(soc, res->ai_addr, res->ai_addrlen);
	if (status_bind == 0) printf("bind was successful!\n");

	// listen on that port and IP
	status_listen = listen(soc, BACKLOG);
	if (status_listen == 0) printf("listen was succesful!\n");

	// now that we are listening, lets accept a connecting communication
	struct sockaddr_storage their_addr; // incoming connection
	socklen_t addr_size; // size of that IP in bytes
	int soc_new; // create a new socket using the incoming IP
	
	addr_size = sizeof their_addr;
	soc_new = accept(soc, (struct sockaddr *)&their_addr, &addr_size);

	// ... program will hang till a connection is made ^
	
	// recieve some incoming packets:
	char msg_recv[256]; // we can store a sentence 0 - 255 characters big
	int max_len = 256 - 1; // the max amount of bytes allowed to be received at once
	int flags = 0; // 0 = wait / block till a message is recieved

	recv(soc_new, msg_recv, max_len, flags);

	printf("printing the recieved message!\n");
	printf("%s\n", msg_recv);
	


	return EXIT_SUCCESS;
}
