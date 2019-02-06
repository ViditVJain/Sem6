#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define n_stud 5
struct stud{
	char reg[500];
	char name[500];
	char sub[500];
};

struct stud db[n_stud] = {
	{"160953777", "raghav","456"},
	{"160953882", "abc","453"},
	{"160953566", "KBJH","456"},
	{"160953349", "zxcv","453"},
    {"160953322", "znyc","456"}
};

void find_by_reg(char buff[]){
	int i;
	for(i=0; i<n_stud; i++){
		if(!strcmp(buff, db[i].reg)){
			break;
		}
	}
	if(i==n_stud){
        sprintf(buff, "%s", "Not found");
	} else {
		sprintf(buff, "Name: %s\nSub: %s", db[i].name, db[i].sub);
	}
}

void find_by_name(char buff[]){
	int i;
	for(i=0; i<n_stud; i++){
		if(!strcmp(buff, db[i].name)){
			break;
		}
	}
	if(i==n_stud){
        sprintf(buff, "%s", "Not found");
	} else {
		sprintf(buff, "Reg: %s\nsub: %s", db[i].name, db[i].sub);
	}
}

void find_by_code(char buff[]){
	int i;
    for(i=0; i<n_stud; i++){
        if(!strcmp(buff, db[i].sub)){
            break;
        }
    }
    if(i==n_stud){
        sprintf(buff, "%s", "Not found");
    } else {
        sprintf(buff, "Name: %s\nReg: %s", db[i].name, db[i].Reg);
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
        
        int opt = atoi(buff);
        
        recb = recv(ns, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            close(ns);
            exit(0);
        }
        int pid = fork();
        if(!pid){
        	switch(opt){
				case 1:
					printf("Reg no: %s", buff);
					find_by_reg(buff);
					break;
				case 2:
					printf("Name: %s", buff);
					find_by_name(buff);
					break;
				case 3:
					printf("Sub code: %s", buff);
					find_by_code(buff);
					break;
			}
        } else {
        	sprintf(buff, "PID: %d", pid);
        }
		    

        //printf("\nMessage Recieved: ");
        //printf("%s", buff);

        //printf("\n\n");
        //scanf("%s", buff);

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
