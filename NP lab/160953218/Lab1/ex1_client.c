#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int port_no, status, sockfd, newsockfd;
	struct sockaddr_in server;
	char buff[50];
	printf("Enter port no. : ");
	scanf("%d", &port_no);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	status = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
	
	printf("Enter message: ");
	scanf("%s", buff);
	
	status = send(sockfd, buff, sizeof(buff), 0);
	
	close(sockfd);
}
