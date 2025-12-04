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
