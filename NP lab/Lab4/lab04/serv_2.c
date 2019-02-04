#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define n_dns 3

struct map{
	char name[50];
	char ip[50];
};

struct map dns[n_dns] = {
	{"google.com", "172.217.12.174"},
	{"microsoft.com", "13.77.161.179"},
	{"yahoo.com", "98.138.219.231"}
};

void find_by_name(char buff[]){
	int i;
	for(i=0; i<n_dns; i++){
		if(!strcmp(buff, dns[i].name)){
			break;
		}
	}
	if(i==n_dns){
		strcpy(buff, "Not found");
	} else {
		sprintf(buff, "IP: %s", dns[i].ip);
	}
}

    main() {
        int s, r, recb, sntb, x, ns, a = 0;
        printf("INPUT port number: ");
        scanf("%d", & x);
        socklen_t len;
        struct sockaddr_in server, client;
        char buff[500];

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1) {
            printf("\nSocket creation error.");
            exit(0);
        }
        printf("\nSocket created.");

        server.sin_family = AF_INET;
        server.sin_port = htons(x);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        r = bind(s, (struct sockaddr * ) & server, sizeof(server));
        if (r == -1) {
            printf("\nBinding error.");
            exit(0);
        }
        printf("\nSocket binded.");

        r = listen(s, 1);
        if (r == -1) {
            close(s);
            exit(0);
        }
        printf("\nSocket listening.");

        len = sizeof(client);

        ns = accept(s, (struct sockaddr * ) & client, & len);
        if (ns == -1) {
            close(s);
            exit(0);
        }
        printf("\nSocket accepting.");

        recb = recv(ns, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            close(ns);
            exit(0);
        }
		
		find_by_name(buff);

        sntb = send(ns, buff, sizeof(buff), 0);
        if (sntb == -1) {
            printf("\nMessage Sending Failed");
            close(s);
            close(ns);
            exit(0);
        }

        close(ns);
        close(s);
        printf("Exit\n");
        exit(0);
    }
