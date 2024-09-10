// server application with the following requirements:
// The server should handle multiple clients (use either fork() or threads).
// Clients should be able to connect to the server, send messages, and receive messages from other connected clients.
// Implement basic message broadcasting: when one client sends a message, the server broadcasts it to all other connected clients.
// Handle client disconnection gracefully.

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "networkConstants.h"

int main()
{
	// create a socket
	printf("Creating socket...\n");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("SERV: ERROR creating socket\n");
		exit(EXIT_FAILURE);
	}
	
	// bind socket
	//// Create socket addres info structure
	printf("Building socket structure...\n");
	struct sockaddr_in sockAddr; // store socket info
	sockAddr.sin_family = AF_INET; // use IPV4
	sockAddr.sin_port = htons(8080); // use port 
	sockAddr.sin_addr.s_addr = INADDR_ANY; // bind to any address
	
	printf("Binding to socket...\n");
	int bindResult = bind(sockfd, (struct sockaddr*)&sockAddr, sizeof(sockAddr)); //bind socket
	if(bindResult == -1)
	{
		printf("SERV: ERROR binding socket\n");
		exit(EXIT_FAILURE);
	}

	printf("Listening...\n");	
	// listen for a connection
	if(listen(sockfd, CONNECTION_BACKLOG) == -1)
	{
		printf("SERV: ERROR listening on socket\n");
		exit(EXIT_FAILURE);
	}
	char serverAddress[INET_ADDRSTRLEN];
	inet_ntop(sockAddr.sin_family, &sockAddr.sin_addr, serverAddress, INET_ADDRSTRLEN);
	printf("Server listening on address: %s\n", serverAddress);
	
	
	// accept a connection
	//int clientfd = accept(sockfd, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	int clientfd = accept(sockfd, NULL, NULL);
	if(clientfd ==-1)
	{
		printf("SERV: ERROR accepting connection\n");
		exit(EXIT_FAILURE);
	}

	printf("Client connection established.\n");
	printf("Waiting for message...\n");

	char buffer[BUFFER_SIZE];
	while(recv(clientfd, buffer, BUFFER_SIZE, 0))
	{
		printf("received from client: %s\n", buffer);
		printf("sending reply...");
		strcpy(buffer, "hello client, I'm server!\n");
		send(clientfd, buffer, BUFFER_SIZE, 0);
	}
	printf("Client disconnected... Server closing\n");
	sleep(2);
	// clean up before closing
	close(clientfd);
	close(sockfd);
	
		
	exit(EXIT_SUCCESS);
	
}
