// playing around with sockets as I work towards building a packet sniffer

#include <sys/socket.h>	// for socket functions
#include <sys/types.h> 	// for socket types
#include <stdio.h>	// for printf() and perror() 
#include <stdlib.h>	// for EXIT macros and other goodies
#include <string.h>	// for memset()
#include <netdb.h>	// for getaddrinfo() 
#include <unistd.h>	// for close()

int main(void) {

	// ~ STEP 1: setup addrinfo ~
	int socket;			// the socket file descriptor (our "phone")
	int status;			// return status for function calls 
	struct addrinfo hints;		// template of information for our socket
	struct addrinfo *servinfo;	// points to the results of getaddrinfo(), later
	
	// ~ STEP 2: zero out all fields in hints
	memset (&hints, 0 sizeof(hitns)); 
	
	// ~ STEP 3: set require information in hints ~
	hints.ai_family = AF_INET;		// use IPV4
	hints.ai_socktype = SOCK_STREAM;        // use TCP (stream socket)
	
	// ~ STEP 4: getaddrinfo ; DNS server lookup (requires wifi) to obtain information about our destination
	// this fills in *servinfo with the address details we need:
	status = getaddrinfo("127.0.0.1", "8080", &hints, &servinfo);

	// ~ STEP 5: getaddrinfo can fail, you must error check the DNS lookup to see if it worked, otherwise try again
	if (status != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status))
	}
}

