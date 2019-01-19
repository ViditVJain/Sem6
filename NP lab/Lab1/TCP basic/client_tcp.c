#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

	int n, ar[50], choice, search_key;
	do{
		printf("Enter size of number set : ");
		scanf("%d", &n);
		status = write(sockfd, &n, sizeof(n));
			
		printf("Enter numbers :\n");
		for (int i = 0; i < n; ++i) {
			scanf("%d", &ar[i]);
		}
		status = write(sockfd, ar, sizeof(ar));
		
		printf("1. Search\t\t2. Sort\t\t3. Split\n");
		scanf("%d", &choice);
		status = write(sockfd, &choice, sizeof(n));
		switch (choice){
			case 1:
			printf("Enter number to search for : ");
			scanf("%d", &search_key);
			status = write(sockfd, &search_key, sizeof(n));
			status = read(sockfd, &search_key, sizeof(n));
			if (search_key == -1)
				printf("\nNot Found\n");
			else
				printf("\nFound at : %d\n", search_key);
			break;
			
			case 2:
			status = read(sockfd, ar, sizeof(ar));
			printf("Sorted Array : ");
			for (int i = 0; i<n; i++){
				printf("%d ", ar[i]);
			}
			printf("\n");
			break;
			
			case 3:
			printf("1. Odd\t\t2. Even\n");
			scanf("%d", &choice);
			status = write(sockfd, &choice, sizeof(n))
			break;
		}

		printf("\nEnter 'exit' to exit or anything else to continue.. : ");
		scanf("%s", buff);
		status = write(sockfd, buff, sizeof(buff));
		
		/*printf("Enter Message : ");
		scanf("%s", buff);
		status = send(sockfd, buff, sizeof(buff), 0);

		status = recv(sockfd, buff, sizeof(buff), 0);
		printf("Message recieved : ");
		printf("%s\n", buff);*/
	} while (strcmp(buff, "exit"));

	close(sockfd);
	return(0);

}
