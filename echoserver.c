/*
 * This file implements an iterative echo server.
 */

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csapp.h"
#include "echo.h"	// Declares echo().

static int	open_listen(int port);

/*
 * Requires:
 *   argv[1] is a string representing an unused TCP port number (in decimal).
 *
 * Effects:
 *   Opens a listening socket on the specified TCP port number.  Runs forever
 *   accepting client connections.  Echoes lines read from a connection until
 *   the connection is closed by the client.  Only accepts a new connection
 *   after the old connection is closed.
 */
int
main(int argc, char **argv)
{
	struct sockaddr_in clientaddr;
	socklen_t clientlen;
	int connfd, listenfd, port;
	char haddrp[INET_ADDRSTRLEN], host_name[NI_MAXHOST];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);
	listenfd = open_listen(port);
	if (listenfd < 0)
		unix_error("open_listen error");
	while (true) {
		clientlen = sizeof(clientaddr);
		/*
		 * Call Accept() to accept a pending connection request from
		 * the client, and create a new file descriptor representing
		 * the server's end of the connection.  Assign the new file
		 * descriptor to connfd.
		 */
		printf("listenfd %d\n", listenfd);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		printf("connfd %d\n", connfd);
		// Use getnameinfo() to determine the client's host name.
		getnameinfo((struct sockaddr *)&clientaddr, clientlen, host_name, NI_MAXHOST, NULL, 0, AI_NUMERICSERV | AI_ADDRCONFIG);
		/*
		 * Convert the binary representation of the client's IP
		 * address to a dotted-decimal string.
		 */
		Inet_ntop(AF_INET, &clientaddr.sin_addr, haddrp,
		    INET_ADDRSTRLEN);
		printf("server connected to %s (%s)\n", host_name, haddrp);
		/*
		 * Echo lines of text until the client closes its end of the
		 * connection.
		 */
		echo(connfd);
		close(connfd);
	}
}

/*
 * Requires:
 *   port is an unused TCP port number.
 *
 * Effects:
 *   Opens and returns a listening socket on the specified port.  Returns -1
 *   and sets errno on a Unix error.
 */
static int
open_listen(int port)
{
	struct sockaddr_in serveraddr;
	int listenfd, optval;

	// Prevent an "unused parameter" warning.  REMOVE THIS STATEMENT!
	(void)port;
	// Set listenfd to a newly created stream socket.
	// REPLACE THIS.
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1) {
		printf("Bad open socket");
	}
	// Eliminate "Address already in use" error from bind().
	optval = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
	    (const void *)&optval, sizeof(int)) == -1)
		return (-1);
	memset(&serveraddr, 0, sizeof(serveraddr));
	/*
	 * Set the IP address in serveraddr to the special ANY IP address, and
	 * set the port to the input port.  Be careful to ensure that the IP
	 * address and port are in network byte order.
	 */
	int addr = htonl(INADDR_ANY);
	serveraddr.sin_addr = *(struct in_addr*)&addr;
	serveraddr.sin_port = htonl(port);
	serveraddr.sin_family = AF_INET;
	// Use bind() to set the address of listenfd to be serveraddr.
	if(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof serveraddr)) {
		printf("Bad bind");
	}

	/*
	 * Use listen() to ready the socket for accepting connection requests.
	 * Set the backlog to 8.
	 */
	if(listen(listenfd, 8)) {
				printf("Bad listen");
	}
	return (listenfd);
}
