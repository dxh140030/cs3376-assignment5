/* A simple server in the internet domain using TCP
The port number is passed as an argument
This version runs forever, forking off a separate
process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//#include "server.h"


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, pid, pid2, status;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	while (1) {
		newsockfd = accept(sockfd,
			(struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		//--------------------------------------------//
		//thinkiii.blogspot.com/2009/12/double-fork-to-avoid-zombie-process.html
		//parent process
		if (pid = fork())
		{
			close(sockfd);
			dostuff(newsockfd);
			//waits for child to finish
			waitpid(pid, &status, NULL);
			exit(0);
		}
		//child process 1, which terminates once process 2 is created
		else if (!pid)
		{
			if (pid2 = fork())
			{
				exit(0);
			}
			else if (!pid2)
			{
				//child process 3
				close(newsockfd);
			}
		}
		else
		{
			//error
		}
		//---------------------------------------------//
	} /* end of while */
	close(sockfd);
	return 0; /* we never get here */
}
