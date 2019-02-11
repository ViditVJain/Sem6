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
#include<time.h>
#define MAX 150

struct login
{
	char username[50];
	char password[50];
};	

void signup(int sockfd,int newsockfd,struct login *user)
{
	char msg[MAX];
	int rbytes;
	memset(msg,0, sizeof(msg));
	rbytes=recv(newsockfd,msg,sizeof(msg),0);	
	if(rbytes==-1)
	{
		printf("Error in receiving\n");
		close(sockfd);
		exit(0);
	}	
	strcpy(user->username,msg);
	memset(msg,0, sizeof(msg));
	rbytes=recv(newsockfd,msg,sizeof(msg),0);	
	if(rbytes==-1)
	{
		printf("Error in receiving\n");
		close(sockfd);
		exit(0);
	}
	strcpy(user->password,msg);
	printf("Signup success\n");
	printf("Username : %s \n",user->username);
	printf("Password : %s \n",user->password);
}

void validate(int sockfd,int newsockfd,struct login *user)
{
	char msg[MAX];
	int rbytes,sbytes;
	memset(msg,0, sizeof(msg));
	rbytes=recv(newsockfd,msg,sizeof(msg),0);	
	if(rbytes==-1)
	{
		printf("Error in receiving\n");
		close(sockfd);
		exit(0);
	}	
	if(strcmp(user->username,msg)==0)
	{
		memset(msg,0, sizeof(msg));
		rbytes=recv(newsockfd,msg,sizeof(msg),0);	
		if(rbytes==-1)
		{
			printf("Error in receiving\n");
			close(sockfd);
			exit(0);
		}
		if(strcmp(user->password,msg)!=0)
		{
			printf("Wrong password\n");
			memset(msg,0, sizeof(msg));
			strcpy(msg,"wrong password");
			sbytes=send(newsockfd,msg,sizeof(msg),0);
			if(sbytes==-1)
			{
				printf("Error in sending\n");
				close(sockfd);
				exit(0);
			}
		}
		else
		{	
			printf("Login success from server side");
			printf("sending mesage to client..\n\n");
			strcpy(msg,"Success");
			sbytes=send(newsockfd,msg,sizeof(msg),0);
			if(sbytes==-1)
			{
				printf("Error in sending\n");
				close(sockfd);
				exit(0);
			}
		}
	}
	else
	{
		printf("Wrong username\n");
		strcpy(msg,"wrong username");
		sbytes=send(newsockfd,msg,sizeof(msg),0);
		if(sbytes==-1)
		{
			printf("client left..s\n");
			close(sockfd);
			exit(0);
		}
	}	
}

int main()
{
	struct login user;
	int sockfd,newsockfd,retval;
	int rbytes,sbytes;
	socklen_t actuallen,len;
	time_t t=time(NULL);
	struct tm *tm = localtime(&t);
	struct sockaddr_in server,client, temp;
	char msg[MAX],msg2[MAX];
  
  //creating socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Creation error\n");
		exit(0);
	}
	printf("Created \n");
	
	len=sizeof(temp);
	server.sin_family=AF_INET;
	server.sin_port=htons(44666);
	server.sin_addr.s_addr=INADDR_ANY;
	retval=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nBinding Error");
		close(sockfd);
		exit(0);
	}
	printf("Binded \n");
		
	retval=listen(sockfd,1);
	if(retval==-1)
	{
		printf("Listening error\n");
		close(sockfd);
		exit(0);
	}
	printf("Listening \n");
	actuallen=sizeof(client);
	newsockfd=accept(sockfd,(struct sockaddr *)&client,&actuallen);
	if(newsockfd==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("Accepted \n");
	memset(msg,0, sizeof(msg));
	rbytes=recv(newsockfd,msg,sizeof(msg),0);	
	if(rbytes==-1)
	{
		printf("client exited....\n");
		close(sockfd);
		exit(0);
	}
	while(strcmp(msg,"exit")!=0)
	{
		if(strcmp(msg,"signup")==0)
			signup(sockfd,newsockfd,&user);
		else if(strcmp(msg,"login")==0)
			validate(sockfd,newsockfd,&user);
		else
		{
			printf("Exit\n");
			close(newsockfd);
			close(sockfd);
			exit(0);
		}
		memset(msg,0, sizeof(msg));
		rbytes=recv(newsockfd,msg,sizeof(msg),0);	
		if(rbytes==-1)
		{
			printf("Error in receiving\n");
			close(sockfd);
			exit(0);
		}
	}
	
	validate(sockfd,newsockfd,&user);
	close(newsockfd);
	close(sockfd);	
}
	//int o;
	//rbytes=recv(newsockfd,&o,sizeof(&o),0);
	//if(strcmp(msg,"exit")!=0)
	//{
		//while(1)
		//{
			//puts(msg);
			//memset(msg,0, sizeof(msg));
			//if(o==1)
			//{
				
			//}
		//	else
			//	printf("%s",msg);	
		/*sbytes=send(newsockfd,msg,sizeof(msg),0);
			if(sbytes==-1)
			{
				printf("Error in sending\n");
				close(sockfd);
				exit(0);
			}
			memset(msg,0, sizeof(msg));
			rbytes=recv(newsockfd,msg,sizeof(msg),0);	
			if(rbytes==-1)
			{
				printf("Error in receiving\n");
				close(sockfd);
				exit(0);
			}
			if(strcmp(msg,"exit")==0)
			{
				puts(msg);
				break;
			}
		}
	}
	*/	
	
