#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>


main()
{
	int s,r,recb,sntb,x,ns,a=0;
	pid_t pid;
	
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.");

	
	
	printf("\nSocket accepting.");
	
	



	
int counter=0;
while(1)


{   	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	
	
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	counter++;
	
	if(counter==3)
	{ printf("exiting");
	  close(s);
	  close(ns);
	  exit(0);
	  
	  
	}
	
	
	pid=fork();
	
	if(pid==0)
	
	{    	close(s);
	
	
	
	 while(1)
	 
	{
        	memset(buff, 0, sizeof(buff));
		recb=recv(ns,buff,sizeof(buff),0);
		
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			
			close(ns);
			exit(0);
		}	
	
		printf("\nMessage Recieved: ");
		printf("%s", buff);
        	if(!strcmp(buff,"stop"))
	 	 break;


			strcpy(buff, "hello this is server");
			sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			close(ns);
			exit(0);
		}
		
	
	
   	 }//end while
 	
 	
 	}//endif
else

 	close(ns);
 	
} //end while outer
	
}
