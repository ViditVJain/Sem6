#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

	void sortAlpha(char buff[]){
		int n = strlen(buff);
		char tmp[500];
		int i, j=0;
		for(i=0; i<n; i++){
			char c = buff[i];
			if(c>='a' && c<='z'){
				tmp[j++] = c;
				printf("%c ", c);
			}
		}
		tmp[j] = '\0';
		printf("\n j = %d tmp = %s\n", j, tmp);
		int pass;
		for(pass=0; pass<j; pass++){
			for(i=0; i<j-1; i++){
				if(tmp[i]<tmp[i+1]){
					char t;
					t = tmp[i];
					tmp[i] = tmp[i+1];
					tmp[i+1] = t;
				}
			}
		}
		strcpy(buff, "Output at the parent process of the server: ");
		strcat(buff, tmp);
		printf("buff: %s \n", buff);
	}
	
	void sortNum(char buff[]){
		int n = strlen(buff);
		char tmp[500];
		int i, j=0;
		for(i=0; i<n; i++){
			char c = buff[i];
			if(c>='0' && c<='9'){
				tmp[j++] = c;
				printf("%c ", c);
			}
		}
		tmp[j] = '\0';
		printf("\n j = %d tmp = %s\n", j, tmp);
		int pass;
		for(pass=0; pass<j; pass++){
			for(i=0; i<j-1; i++){
				if(tmp[i]>tmp[i+1]){
					char t;
					t = tmp[i];
					tmp[i] = tmp[i+1];
					tmp[i+1] = t;
				}
			}
		}
		strcpy(buff, "Output at the child process of the server: ");
		strcat(buff, tmp);
		printf("buff: %s \n", buff);
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
		printf("\nMessage Recieved: ");
		printf("%s\n", buff);
        int pid = fork();
    	if(pid){
			sortAlpha(buff);
	    } else {
			sortNum(buff);
	    }
	    sntb = send(ns, buff, sizeof(buff), 0);
		if (sntb == -1) {
		    printf("\nMessage Sending Failed");
		    close(s);
		    close(ns);
		    exit(0);
		}
        

        close(ns);
        close(s);
    }
