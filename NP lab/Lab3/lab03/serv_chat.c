#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
    
    void pidprint(int pid){
        // int pid;
        
        // pid=fork(); /* Duplicate. Child and parent continue from here.*/
        if (pid!=0) /* pid is non-zero, so I must be the parent */
        {
            printf("I'm the parent process with PID %d and PPID %d.\n",
            getpid(),getppid());
            printf("My child's PID is %d.\n", pid);
        }
        else /* pid is zero, so I must be the child. */
        {
            printf("I'm the child process with PID %d and PPID %d.\n",
            getpid(),getppid());
        }
        printf("PID %d terminates.\n",pid); /* Both processes execute this */
    }


    main() {
        int s, r, recb, sntb, x, ns, a = 0;
        printf("INPUT port number: ");
        scanf("%d", & x);
        socklen_t len;
        struct sockaddr_in server, client;
        char buff[50];

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
        printf("I'm the original process with PID %d and PPID %d.\n",
        getpid(),getppid());
        
        int pid = fork();
        int work = 1;
        pidprint(pid);

        while(work){
        	if(pid){
        		recb = recv(ns, buff, sizeof(buff), 0);
				if (recb == -1) {
				    printf("\nMessage Recieving Failed");
				    close(s);
				    close(ns);
				    exit(0);
				}

				printf("\nMessage Recieved: ");
				printf("%s\n", buff);
		    } else {
				scanf("%s", buff);

				sntb = send(ns, buff, sizeof(buff), 0);
				if (sntb == -1) {
				    printf("\nMessage Sending Failed");
				    close(s);
				    close(ns);
				    exit(0);
				}
		    }
		    if(!strcmp(buff, "BYE")){
		        printf("\nChat terminated\n");
				sntb = send(ns, "BYE", sizeof("BYE"), 0);
				if (sntb == -1) {
					printf("\nMessage Sending Failed");
					close(s);
					close(ns);
					exit(0);
				}
		    	exit(0);
		    }
        }
        

        close(ns);
        close(s);
    }
