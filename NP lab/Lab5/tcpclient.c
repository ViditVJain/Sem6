#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#define MAX 50

void signup(int sockfd)
{
	char msg[MAX];
	int sbytes;
	memset(msg,0, sizeof(msg));
	strcpy(msg,"signup");
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}
	memset(msg,0, sizeof(msg));
	printf("Enter username : ");
	scanf("%s",msg);
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}
		
	memset(msg,0, sizeof(msg));
	printf("Enter password : ");
	scanf("%s",msg);
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}	
}

void login(int sockfd)
{
	char msg[MAX],rbytes;
	int sbytes;
	memset(msg,0, sizeof(msg));
	strcpy(msg,"login");
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}
	printf("Enter username : ");
	memset(msg,0, sizeof(msg));
	scanf("%s",msg);
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}
		
	memset(msg,0, sizeof(msg));
	printf("Enter password : ");
	scanf("%s",msg);
	sbytes=send(sockfd,msg,sizeof(msg),0);
	if(sbytes==-1)
	{
		printf("Error in sending\n");
		close(sockfd);
		exit(0);
	}	
	
	memset(msg,0, sizeof(msg));
	rbytes=recv(sockfd,msg,sizeof(msg),0);	
	if(rbytes==-1)
	{
		printf("Error in receiving\n");
		close(sockfd);
		exit(0);
	}
	printf("%s\n",msg);
}

int main()
{
	int sockfd,retval;
	int rbytes,sbytes;
	struct sockaddr_in server;
	char msg[MAX],msg2[MAX];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Creation error\n");
		exit(0);
	}
	printf("Created \n");
	server.sin_family=AF_INET;
	server.sin_port=htons(44666);
	server.sin_addr.s_addr=INADDR_ANY;
	retval=connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	if(retval==-1)
	{
		printf("Connection Error\n");
		exit(0);
	}
	printf("Connected \n");
	int choice=0;
	while(choice!=3)
	{
		printf("\n1.Signup \n");
		printf("2.Login \n");
		printf("3.Exit \n");
		scanf("%d",&choice);
		if(choice==1)
			signup(sockfd);
		else if(choice==2)
			login(sockfd);
		else
		{
			strcpy(msg,"exit");
			sbytes=send(sockfd,msg,sizeof(msg),0);
			if(sbytes==-1)
			{
				printf("Error in sending\n");
				close(sockfd);
				exit(0);
			}
			close(sockfd);
			exit(0);	
		}
	}
	close(sockfd);	
}
	
	/*memset(msg,0, sizeof(msg));
	int o;
	scanf("%d",&o);
	if(strcmp(msg,"exit")!=0)
	{
		
		if(o==1)
		{
			sbytes=send(sockfd,msg,sizeof(msg),0);
			if(sbytes==-1)
		

	}   */	
	

