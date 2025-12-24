/*
 *  Minimal but professional HTTP server written in pure C.
 *
 *  Features:
 *      • Listens on all IPv4 interfaces, port 80.
 *      • Accepts connections and spawns a new thread per client.
 *      • Sends back a simple HTML page (no request parsing).
 *      • Robust error handling & logging.
 *
 *  Build:
 *      gcc -Wall -Wextra -O2 -o test_http_server test_http_server.c -pthread
 *
 *  Run (root needed for port 80):
 *      sudo ./test_http_server
 */

#define _POSIX_C_SOURCE 200809L   /* For getaddrinfo, pthreads, etc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <pthread.h>

/* --------------------------------------------------------------------- */
/* Configuration constants                                               */
/* --------------------------------------------------------------------- */

#define LISTEN_PORT     "80"          /* Listen on TCP port 80 */
#define BACKLOG         128           /* Max pending connections */
#define RECV_BUFFER_LEN 4096          /* Size of request buffer */

/* --------------------------------------------------------------------- */
/* Logging helper                                                        */
/* --------------------------------------------------------------------- */

static void log_error(const char *msg, int errnum)
{
    fprintf(stderr, "[%s] %s: %s\n", __func__, msg, strerror(errnum));
}

static void log_info(const char *msg)
{
    fprintf(stdout, "[%s] %s\n", __func__, msg);
}

/* --------------------------------------------------------------------- */
/* Thread argument structure                                            */
/* --------------------------------------------------------------------- */

typedef struct {
    int client_fd;          /* Socket descriptor for the accepted client */
} thread_arg_t;

/* --------------------------------------------------------------------- */
/* HTTP response (static)                                               */
/* --------------------------------------------------------------------- */

static const char *HTTP_RESPONSE =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n"
"Connection: close\r\n"
"Content-Length: 124\r\n"
"\r\n"
"<html>\n"
"    <head><title>Test Server</title></head>\n"
"    <body>\n"
"        <h1>Hello from the test HTTP server!</h1>\n"
"        <p>This is a static response served by a C program.</p>\n"
"    </body>\n"
"</html>\n";

/* --------------------------------------------------------------------- */
/* Thread routine: handles one client connection                       */
/* --------------------------------------------------------------------- */

static void *client_handler(void *arg)
{
    thread_arg_t *targ = (thread_arg_t *)arg;
    int fd = targ->client_fd;

    /* Free the argument struct */
    free(targ);

    /* ------------------------------------------------------------ */
    /* Optional: read the request. We simply drain until we see
     * an empty line or reach a reasonable limit.
     * The server does not actually parse or use the request.
     */
    char buffer[RECV_BUFFER_LEN];
    ssize_t nread;
    size_t total_read = 0;

    while ((nread = recv(fd, buffer, sizeof(buffer), 0)) > 0) {
        total_read += nread;
        /* Break on end‑of‑headers (\r\n\r\n) */
        if (strstr(buffer, "\r\n\r\n") != NULL)
            break;
        /* Avoid an infinite loop in case of a malformed request */
        if (total_read > 8192)   /* 8 KiB max for headers */
            break;
    }
    if (nread < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
        log_error("recv", errno);
    }

    /* ------------------------------------------------------------ */
    /* Send the static HTTP response */
    ssize_t nwritten = send(fd, HTTP_RESPONSE, strlen(HTTP_RESPONSE), 0);
    if (nwritten < 0) {
        log_error("send", errno);
    } else if ((size_t)nwritten != strlen(HTTP_RESPONSE)) {
        fprintf(stderr,
                "[%s] Warning: partial write (%zd of %zu bytes)\n",
                __func__, nwritten, strlen(HTTP_RESPONSE));
    }

    /* ------------------------------------------------------------ */
    /* Clean up */
    close(fd);

    pthread_exit(NULL);
    return NULL;   /* Never reached, but keeps the compiler happy */
}

/* --------------------------------------------------------------------- */
/* Main server loop                                                     */
/* --------------------------------------------------------------------- */

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    /* ---------------------- 1. Resolve address information -------------- */
    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_INET;          /* IPv4 only for simplicity */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;       /* For wildcard IP */

    if ((rv = getaddrinfo(NULL, LISTEN_PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return EXIT_FAILURE;
    }

    /* ---------------------- 2. Create socket and bind ----------------- */
    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("socket");
            continue;
        }

        /* Allow reuse of address */
        int yes = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
            perror("setsockopt");
            close(sockfd);
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == 0)
            break;      /* Success */

        perror("bind");
        close(sockfd);
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to bind socket\n");
        freeaddrinfo(servinfo);
        return EXIT_FAILURE;
    }

    freeaddrinfo(servinfo);

    /* ---------------------- 3. Listen --------------------------------- */
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        close(sockfd);
        return EXIT_FAILURE;
    }

    log_info("Server is listening on port 80...");

    /* ---------------------- 4. Accept loop ----------------------------- */
    while (1) {
        struct sockaddr_storage client_addr;
        socklen_t addr_size = sizeof(client_addr);

        int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
        if (client_fd == -1) {
            /* Interrupted by signal? Just retry. */
            if (errno == EINTR)
                continue;

            perror("accept");
            break;
        }

        /* Optional: log the client's IP address */
        char ipstr[INET_ADDRSTRLEN];
        struct sockaddr_in *s = (struct sockaddr_in *)&client_addr;
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        fprintf(stdout,
                "[%s] Accepted connection from %s:%d\n",
                __func__, ipstr, ntohs(s->sin_port));

        /* Allocate argument structure for the thread */
        thread_arg_t *targ = malloc(sizeof(thread_arg_t));
        if (!targ) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        targ->client_fd = client_fd;

        pthread_t tid;
        int err = pthread_create(&tid, NULL, client_handler, targ);
        if (err != 0) {
            fprintf(stderr,
                    "[%s] pthread_create failed: %s\n",
                    __func__, strerror(err));
            close(client_fd);
            free(targ);
            continue;
        }

        /* Detach so that resources are reclaimed automatically */
        pthread_detach(tid);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}

