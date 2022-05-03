/*
	Name: Hernandez, Ayessa Amor N.
	Student Number: 2018-11019
	Exer 05: Socket Programming

	@date: 2022-05-03 12:42

	References: 
		- https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
		- https://gist.github.com/0x000000AC/ac8c913f786b88eb7e09.
*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

char* pigLatin ( char *word )
{
    // First, get a count of the number
    // of characters in the user-input string
    int n;
    int charCount = 0;
    char *ayEnding = "ay";

    for( n=0; word[n]; ++n)
    {
            if( word[n] != ' ' )
        {
                charCount ++;
            }
    }

    // Create a substring with the first character of
    // the user-entered word.  This will later be
    // concatenated with the substring.

    char wordFirstChar[1];
    memcpy ( wordFirstChar, &word[0], 1 );
    wordFirstChar[1] = '\0';

    // Declare a substring with the number of characters
    // from the string.  This will be your base to which
    // the first character of the original string and
    // 'ay' will be appended
    char subString[charCount];
    memcpy( subString, &word[1], charCount-1 );
    subString[charCount] = '\0'; // must ensure null terminator is re-added
    // You have the char, you have the substring, concatenate
    // the two and append 'ay'
    char pigLatinifiedWord[charCount+3];
    bzero(pigLatinifiedWord, sizeof(pigLatinifiedWord));
    strcat(pigLatinifiedWord, subString);
    strcat(pigLatinifiedWord, wordFirstChar);
    strcat(pigLatinifiedWord, ayEnding); 

    char *plword = pigLatinifiedWord;
    return plword;

}

void lowerCaseStr(char *s)
{
  char  *p;

  for (p = s; *p != '\0'; p++) 
    *p = (char) tolower(*p);
}


// Function designed for chat between client and server.
void func(int connfd)
{
	char buff[MAX];
	char *word;
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));

		// print buffer which contains the client contents
		printf("\nReceived word: %s\n", buff);

		lowerCaseStr(buff);
		word = pigLatin(buff);
		printf("Translated word: %s\n", word);

		// and send that buffer to client
		write(connfd, word, sizeof(word));

		bzero(buff, MAX);
		read(connfd, buff, sizeof(buff));
		if (strncmp("N", buff, 1) == 0 || strncmp("n", buff, 1) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		//printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Acknowledgment failed.\n");
		exit(0);
	}
	else
		printf("Client acknowledged!\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
