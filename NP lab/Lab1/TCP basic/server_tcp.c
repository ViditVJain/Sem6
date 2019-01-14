#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	int sockfd, newsockfd, status, port_no;
	struct sockaddr_in server, client;
	char buff[50];

	printf("Enter port : \n");
	scanf("%d", &port_no);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr.s_addr = htonl(INADDR_ANY);	

	status = bind(sockfd, (struct sockaddr*)&server, sizeof(server));	

	status = listen(sockfd, 1); 
	
	socklen_t len = sizeof(client);
	newsockfd = accept(sockfd, (struct sockaddr*)&client, &len); 
	// printf("here\n");
	int ar[50];
	do {
		status = read(newsockfd, ar, sizeof(ar));
		// status = recv(newsockfd, &ar, sizeof(ar), 0);
		for (int i = 0; i < sizeof(ar)/sizeof(ar[0]); ++i) {
			printf("%d\t", &ar[i]);
		}




		// status = recv(newsockfd, buff, sizeof(buff), 0);
		// printf("Message recieved : ");
		// printf("%s\n", buff);

		// printf("Enter Message : ");
		// scanf("%s", buff);
		// status = send(newsockfd, buff, sizeof(buff), 0);
	} while (strcmp(buff, "exit"));

	close(sockfd);
	close(newsockfd);
}