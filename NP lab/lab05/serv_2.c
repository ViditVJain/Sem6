#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

	void checkAnagram(char s1[], char s2[], char buff[]){
		int flag = 1;
		if(strlen(s1)==strlen(s2)){
			int map[26], i;
			for(i=0; i<26; i++){
				map[i] = 0;
			}
			for(i=0; i<strlen(s1); i++){
				map[s1[i]%26]+=1;
				map[s2[i]%26]-=1;
			}
			for(i=0; i<26; i++){
				if(map[i]){
					flag = 0;
					break;
				}
			}
		} else {
			flag = 0;
		}

		if(flag){
			sprintf(buff, "Anagram: True");
		} else {
			sprintf(buff, "Anagram: False");
		}
	}

    main() {
		FILE *filePointer;
        int s, r, recb, sntb, x, ns, a = 0;
        printf("INPUT port number: ");
        scanf("%d", & x);
        socklen_t len;
        struct sockaddr_in server, client;
        char buff[500], s1[500], s2[500];

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

        r = listen(s, 5);
        if (r == -1) {
            close(s);
            exit(0);
        }
        printf("\nSocket listening.");
        
        int i;
        strcpy(buff,"");
        while(1){
        	len = sizeof(client);

		    ns = accept(s, (struct sockaddr * ) & client, & len);
		    if (ns == -1) {
		        close(s);
		        exit(0);
		    }
		    printf("\nSocket accepting.");
		    
		    int pid = fork();
		    
		    printf(":1\n");
		    if(pid){
		    	printf(":2\n");
		    	recb = recv(ns, buff, sizeof(buff), 0);
		    	printf(":3\n");
			    if (recb == -1) {
			        printf("\nMessage Recieving Failed");
			        close(s);
			        exit(0);
			    }
			    strcpy(s1, buff);
			    printf("got: %s\n", s1);

			    recb = recv(ns, buff, sizeof(buff), 0);
			    if (recb == -1) {
			        printf("\nMessage Recieving Failed");
			        close(s);
			        exit(0);
			    }
			    strcpy(s2, buff);
			    printf("got: %s\n", s2);

			    checkAnagram(s1, s2, buff);

			    sntb = send(ns, buff, sizeof(buff), 0);
			    if (sntb == -1) {
			        close(s);
			        printf("\nMessage Sending Failed");
			        exit(0);
			    }
			    
				close(ns);
		    }
        }

        close(ns);
        close(s);
    }
