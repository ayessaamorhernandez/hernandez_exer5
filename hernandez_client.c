/*
	Name: Hernandez, Ayessa Amor N.
	Student Number: 2018-11019
	Exer 05: Socket Programming

	@date: 2022-05-03 12:42

	References: 
		- https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
		- https://gist.github.com/0x000000AC/ac8c913f786b88eb7e09.
*/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string to translate: ");
		bzero(buff, sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		while (n!=0){
			if (buff[n] == '\n'){
				buff[n] = '\0';
			}
			n--;
		}
		// printf("buff: %s\n", buff);
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		bzero(buff, sizeof(buff));
		printf("\nSend again? Y or N. ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		if ((strncmp(buff, "n", 1)) == 0 || (strncmp(buff, "N", 1)) == 0) {
			printf("Client Exit...\n");
			break;
		}

	}
}

int main()
{
	int sockfd, connfd, x;
	struct sockaddr_in servaddr, cli;
	char addr[MAX];
	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
		printf("Enter Server IP: ");
		x = 0;
		while ((addr[x++] = getchar()) != '\n')
			;
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	// servaddr.sin_addr.s_addr = inet_aton(addr);
	servaddr.sin_port = htons(PORT);
	inet_aton(addr, &servaddr.sin_addr.s_addr);
	//printf("%d", servaddr.sin_addr.s_addr);
	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection with the server failed...\n");
		exit(0);
	}
	else
		// printf("%d", servaddr.sin_addr.s_addr);
		printf("Connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
