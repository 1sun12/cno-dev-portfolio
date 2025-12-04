// below is a canonical "order-of-operations" when creating NETWORK structs
// for use with UNIX SOCKETS API
//
// AF_INET = IPv4
// AF_INET6 = IPv6
// AI_PASSIVE = macro for "local-host"
// SOCK_STREAM = TCP stream sockets
// SOCK_DGRAM = UDP stream sockets
//
// === STRUCTS IN ORDER ===
// struct addrinfo -- all the information needed for a getaddrinfo() call
// struct sockaddr -- address family, destination IP, and port
// struct sockaddr_in -- same as above, but can ONLY BE USED FOR IPv4, can be type-casted to a sockaddr
// struct in_addr -- a struct holding only the destination IPv4 address
//
// === HELPFUL MACROS ===
// inet_pton(); -- converts a string IPv4 / IPv6 to byte notation (computer readable)
// inet_ntop(); -- converts a byte notation IPv4 / IPv6 to string (humanly readable / can be printed)
// INET_ADDRSTRLEN -- the size of a IPv4 address (when allocating a char *)
// INET6_ADDRSTRLEN -- the size of a IPv6 address (when allocating a char *)
//
// === DNS LOOKUP ===
// getaddrinfo(
// const char *node, -- e.g. "google.com" or IP address
// const char *service, -- e.g. "http" or port number
// const struct addrinfo *hints, -- a supplied addrinfo filled out with relevent information
// struct addrinfo **res -- the results of the DNS look up stored in a linked-list
// );
// )

// === EXAMPLE 1 ===
// below is a sample call if I was a server listening on the local-host IP, for port 3490
// note, this doesn't actually do any listening or network setup; merely sets up structures we'll use later

// networking includes
#include <sys/types.h> // not sure WHY this is needed yet...
#include <sys/socket.h> // not sure WHY this is needed yet...
#include <netdb.h> // not sure WHY this is needed yet...
#include <netinet/in.h> // inet_ntop / inet_pton
#include <arpa/inet.h> // inet_ntop / inet_pton

// generic includes
#include <stdlib.h>
#include <stdio.h>
#include <cstring> // for "memset()"

int main() {
// create an addrinfo, to be filled with relevent destination and host information
struct addrinfo hints;

// create another addrinfo to hold the results of the getaddrinfo() DNS lookup
struct addrinfo *servinfo;

// always remember to empty / zero-out the struct 
memset(&hints, 0, sizeof hints);

// set to IPv4
hints.ai_family = AF_INET;

// set to TCP
hints.ai_socktype = SOCK_STREAM;

// set to local-host
hints.ai_flags = AI_PASSIVE;

// set protocol to 0 = "any"
hints.ai_protocol = 0;

// we are now ready for a DNS look-up using getaddrinfo() !!
// capture the return value of "getaddrinfo" by setting it equal to an int
int status_getaddrinfo = 0;

status_getaddrinfo = getaddrinfo(
	NULL, // IP address; not necessary because we set "ai_flags = AI_PASSIVE"; set to local-host
	"3490", // port number
	&hints, // required information for the DNS lookup
	&servinfo // where to store the returned results
	);

// status == 0 : success!
// status <= -1 : there was an error
// status > 0 : there was an error
if (status_getaddrinfo <= -1) {
	puts("getaddrinfo: -1 -- (<) there was an error!");
} else if (status_getaddrinfo == 0){
	puts("getaddrinfo: 0 -- success!");
} else if (status_getaddrinfo > 0) {
	puts("getaddrinfo: >0 -- (>) there was an error!");
}

// lets print the contents of the first addrinfo in the linked-list, just to see what's inside
// here is a key of what's normally inside an addrinfo{}
// struct addrinfo {
// int ai_flags;		1 -- e.g. AI_PASSIVE, AI_CANONNAME...
// int ai_family;		2 -- e.g. AF_INET, AF_INET6...
// int ai_socktype;		3 -- e.g. SOCK_STREAM, SOCK_DGRAM...
// int ai_protocol;		4 -- 0 for "any"
// size_t ai_addrlen;		5 -- size of ai_addr in bytes
// struct sockaddr *ai_addr;	6 -- IP address
// char *ai_canonname;		7 -- full canonical hostname
// struct addrinfo *ai_net;	8 -- linked-list, the next addrinfo after the DNS look-up
// }

puts("=== PRINTING THE FIRST addrinfo IN THE LIST ===");
printf("ai_flags: %d\n", servinfo->ai_flags);
printf("ai_family: %d\n", servinfo->ai_family);
printf("ai_socktype: %d\n", servinfo->ai_socktype);
printf("ai_protocol: %d\n", servinfo->ai_protocol);
printf("ai_addrlen: %u\n", servinfo->ai_addrlen);
printf("ai_addr->sa_family: %u\n", servinfo->ai_addr->sa_family);
char ip_string[INET_ADDRSTRLEN];
inet_ntop(AF_INET, &(servinfo->ai_addr->sa_data), ip_string, INET_ADDRSTRLEN);
printf("ai_addr->sa_data: %s\n", ip_string);

puts("=== END OF PROGRAM ===");

return EXIT_SUCCESS;
}
