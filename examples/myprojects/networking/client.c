// client application with the following requirements:
// The server should handle multiple clients (use either fork() or threads).
// Clients should be able to connect to the server, send messages, and receive messages from other connected clients.
// Implement basic message broadcasting: when one client sends a message, the server broadcasts it to all other connected clients.
// Handle client disconnection gracefully.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "networkConstants.h"


int main()
{
	// make client socket
	printf("Creating socket...\n");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("CLI: ERROR creating socket\n");
		exit(EXIT_FAILURE);
	}
	
	// build hints structure for finding the server on port 8080
	printf("Building Hints...\n");
	struct addrinfo serverAddrInfoHints;
	serverAddrInfoHints.ai_flags = AI_V4MAPPED; // use IPV4
	serverAddrInfoHints.ai_family = AF_INET; // use IPV4
	serverAddrInfoHints.ai_socktype = SOCK_STREAM; // use TCP socket
	serverAddrInfoHints.ai_protocol = 0; // any protocol
	serverAddrInfoHints.ai_addrlen = 0;
	serverAddrInfoHints.ai_addr = NULL;
	serverAddrInfoHints.ai_canonname = NULL;
	serverAddrInfoHints.ai_next = NULL;
	
	// get server info
	printf("Searching server...\n");
	struct addrinfo* serverAddrInfoResult; // struct to store results of server found
	int result = getaddrinfo("0.0.0.0", "8080", &serverAddrInfoHints, &serverAddrInfoResult);
	if(result != 0)
	{
		printf("CLI: ERROR getting server info\n");
		exit(EXIT_FAILURE);
	}
	
	// connect to server
	printf("Attempting connection...\n");
	int conResult = connect(sockfd, serverAddrInfoResult->ai_addr, serverAddrInfoResult->ai_addrlen);
	if(conResult != 0)
	{
		printf("CLI: ERROR connecting to server\n");
		exit(EXIT_FAILURE);
	}
	printf("Connection succesful...\n");
	
	printf("Sending message...\n");
	sleep(1);
	char buffer[BUFFER_SIZE];
	strcpy(buffer, "Hello from client! \n");
	send(sockfd, buffer, sizeof(buffer), 0);
	recv(sockfd, buffer, BUFFER_SIZE, 0); // wait reply
	printf("server reply: %s", buffer);

	sleep(1);
	strcpy(buffer, "world\n");
	send(sockfd, buffer, sizeof(buffer), 0);
	recv(sockfd, buffer, BUFFER_SIZE, 0); // wait reply
	printf("server reply: %s", buffer);

	
	printf("Closing Connection...\n");
	sleep(5);
	close(sockfd);
	freeaddrinfo(serverAddrInfoResult);
	exit(EXIT_SUCCESS);
}
