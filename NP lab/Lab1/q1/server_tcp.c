#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int n, ar[50];

int search (int x, int ar[]){
	//printf("\npfunc : %d", x);
	int found = -1;
	for (int i = 0; i<n; i++){
		if (ar[i] == x)
			found = i;
		//printf("%d\t", ar[i]);
	}
	return found;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int odd(int ar[]) {
	int k = 0;
	for (int i = 0; i < n; ++i){
		// printf("ar[i] = %d\n", ar[i]);
		if ((ar[i]%2)!=0){
			ar[k] = ar[i];
			k++;
			// printf("%d\t", ar[k]);
		}
	}
	return k;
}

int even(int ar[]) {
	int k = 0;
	for (int i = 0; i < n; ++i){
		// printf("ar[i] = %d\n", ar[i]);
		if ((ar[i]%2)==0){
			ar[k] = ar[i];
			k++;
			// printf("%d\t", ar[k]);
		}
	}
	return k;
}

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
	int choice, search_key;
	do {
		status = read(newsockfd, &n, sizeof(n));
		// printf("n = %d\n", n);
		status = read(newsockfd, ar, sizeof(ar));

		/*for (int i = 0; i < n; ++i) {
			printf("%d\t", ar[i]);
		}*/
		//printf("\n");
		
		status = read(newsockfd, &choice, sizeof(n));
		//printf("choice is : %d", choice);
		//printf("\nstatus : %d\n", status);
		
		switch (choice){
			case 1:
			status = read(newsockfd, &search_key, sizeof(n));
			search_key = search(search_key, ar);
			status = write(newsockfd, &search_key, sizeof(n));
			break;
			
			case 2:
			qsort(ar, n, sizeof(int), cmpfunc);
			status = write(newsockfd, ar, sizeof(ar));
			break;
			
			case 3:
			status = read(newsockfd, &choice, sizeof(n));
			if (choice == 1){
				n = odd(ar);
				// printf("n = %d\n", n);
				// for (int i = 0; i < n; ++i)
				// {
				// 	printf("%d\n", ar[i]);
				// }
				status = write(newsockfd, &n, sizeof(n));
				status = write(newsockfd, ar, sizeof(ar));
			}
			else {
				n = even(ar);
				// printf("n = %d\n", n);
				// for (int i = 0; i < n; ++i)
				// {
				// 	printf("%d\n", ar[i]);
				// }
				status = write(newsockfd, &n, sizeof(n));
				status = write(newsockfd, ar, sizeof(ar));
			}

			break;
		}
		
		
		
		status = read(newsockfd, buff, sizeof(buff));

		/*status = recv(newsockfd, buff, sizeof(buff), 0);
		printf("Message recieved : ");
		printf("%s\n", buff);

		printf("Enter Message : ");
		scanf("%s", buff);
		status = send(newsockfd, buff, sizeof(buff), 0);*/
	} while (strcmp(buff, "exit"));

	close(sockfd);
	close(newsockfd);
}
