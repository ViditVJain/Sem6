#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

void encrypt(char buff[]){
	int i;
	for(i=0; i<strlen(buff); i++){
		buff[i]+=3;
	}
}

void decrypt(char buff[]){
	int i;
	for(i=0; i<strlen(buff); i++){
		buff[i]-=3;
	}
}

void fsend(int s, char buff[]){
	int sntb = send(s, buff, sizeof(char)*500, 0);
    if (sntb == -1) {
        close(s);
        printf("\nMessage Sending Failed");
        exit(0);
    }
}

void frecv(int s, char buff[]){
	int recb = recv(s, buff, sizeof(char)*500, 0);
    if (recb == -1) {
        printf("\nMessage Recieving Failed");
        close(s);
        exit(0);
    }
}

    main() {
        int s, r, recb, sntb, x;
        printf("INPUT port number: ");
        scanf("%d", & x);
        struct sockaddr_in server;
        char buff[500];
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1) {
            printf("\nSocket creation error.");
            exit(0);
        }
        printf("\nSocket created.");

        server.sin_family = AF_INET;
        server.sin_port = htons(x);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        r = connect(s, (struct sockaddr * ) & server, sizeof(server));
        if (r == -1) {
            printf("\nConnection error.");
            exit(0);
        }
        printf("\nSocket connected.");

        printf("\n\n");
        
        printf("Username: ");
        scanf(" %[^\t\n]s", buff);
        fsend(s, buff);
        
        printf("Password: ");
        scanf(" %[^\t\n]s", buff);
		encrypt(buff);
        fsend(s, buff);
        
        frecv(s, buff);

        printf("%s\n", buff);
        
        if(!strcmp(buff, "Successful")){
        	while(1){
		    	printf("1. Debit\n2. Credit\n3. View Balance\n4. Exit\n");
		    	scanf("%s", buff);
		    	int opt = atoi(buff);
		    	fsend(s, buff);
		    	if(opt==4){
		    		printf("Exit\n");
		    		break;
		    	}
		    	switch(opt){
		    		case 1:
		    			printf("Debit amount: ");
		    			scanf("%s", buff);
		    			fsend(s, buff);
		    			break;
		    		case 2:
		    			printf("Credit amount: ");
		    			scanf("%s", buff);
		    			fsend(s, buff);
		    			break;
		    		case 3:
		    			printf("View Balance\n");
		    			break;
		    		case 4:
		    			printf("Exit\n");
		    			break;
		    	}
		    	frecv(s, buff);
		    	printf("%s\n", buff);
		    }
        }

        close(s);

    }
