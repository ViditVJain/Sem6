#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int port_no, status, sockfd, newsockfd;
	struct sockaddr_in server, client;
	char buff[50];
	printf("Enter port no. : ");
	scanf("%d", &port_no);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	
	
	status = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	
	status = listen(sockfd, 1);
	
	socklen_t len =  sizeof(client);
	newsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
	while(buff!="exit"){
		status = recv(newsockfd, buff, sizeof(buff), 0);
	}
	
	printf("\nmsg recvd = ");
	printf("%s", buff);
	close(sockfd);
	close(newsockfd);
}
