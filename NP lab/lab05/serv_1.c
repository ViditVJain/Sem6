#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

    main() {
		FILE *filePointer;
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
        
        int i;
        strcpy(buff,"");
        for(i=0; i<2; i++){
        	len = sizeof(client);

		    ns = accept(s, (struct sockaddr * ) & client, & len);
		    if (ns == -1) {
		        close(s);
		        exit(0);
		    }
		    printf("\nSocket accepting.");
		    
		    int pid = fork();
		    

		    if(!pid){
		    	char tmp[500];
		    	char tmp2[500];
		    	
		    	printf("Inside fork\n");
		    	recb = recv(ns, buff, sizeof(buff), 0);
				if (recb == -1) {
				    printf("\nMessage Recieving Failed");
				    close(s);
				    close(ns);
				    exit(0);
				}
				filePointer = fopen("test.txt", "r");
				strcpy(tmp,"");
				strcpy(tmp2,"");
		    	/*while( fgets ( tmp2, 500, filePointer ) != NULL ) 
				{ 
				    sprintf(tmp, "%s %s" , tmp, tmp2) ; 
				}*/
				char ch;
				ch = fgetc(filePointer);
				while (ch != EOF && ch != '\n')
				{
					printf ("%c", ch);
					sprintf(tmp, "%s%c", tmp, ch);
					ch = fgetc(filePointer);
				}
				fclose(filePointer);
				
				printf("buff: %s\n", buff);
				printf("tmp: %s\n", tmp);
				sprintf(tmp2, "%s %s", tmp, buff);
				printf("new buff: %s\n", tmp2);
				
			    filePointer = fopen("test.txt", "w");
			    fputs(tmp2, filePointer);
			    fclose(filePointer);
				close(ns);
        		close(s);
		    }
        }

        close(ns);
        close(s);
    }
