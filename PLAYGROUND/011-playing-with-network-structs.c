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

puts("=== END OF PROGRAM ===");

return EXIT_SUCCESS;
}
