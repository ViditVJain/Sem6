#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	int sockfd, status, port_no;
	struct sockaddr_in server;
	char buff[50];

	printf("Enter port_no : \n");
	scanf("%d", &port_no);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	status = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
	// printf("here\n");

	int n, ar[50];
	do{
		printf("Enter size of number set : ");
		scanf("%d", &n);
		printf("Enter numbers :\n");
		for (int i = 0; i < n; ++i) {
			scanf("%d", &ar[i]);
		}
		printf("here1\n");
		status = write(sockfd, ar, sizeof(ar));
		// status = send(sockfd, &ar, sizeof(ar), 0);

		printf("here\n");

		// printf("Enter Message : ");
		// scanf("%s", buff);
		// status = send(sockfd, buff, sizeof(buff), 0);

		// status = recv(sockfd, buff, sizeof(buff), 0);
		// printf("Message recieved : ");
		// printf("%s\n", buff);
	} while (strcmp(buff, "exit"));

	close(sockfd);
	return(0);

}