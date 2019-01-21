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
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50],word[50],file[50];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

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

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.");
	while(1)
	{
		memset(buff, 0, sizeof(buff));
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			close(ns);
			exit(0);
		}	
	
		printf("\nMessage Recieved: ");
		printf("%s", buff);
		if(!strcmp(buff,"stop"))
		  break;

		FILE *fp = fopen(buff,"r");
		if( !fp)
		{ 
			perror("Error while opening the file.\n");		  	
			memset(buff, 0, sizeof(buff));
			strcpy(buff,"Error! File does not exist!");
		}
		else
		{
			memset(file, 0, sizeof(file));
			strcpy(file,buff);
			memset(buff, 0, sizeof(buff));
			strcpy(buff,"exist"); 	
			fclose(fp);			
		}
		//printf("\n%s",buff);
		//printf("\n%s",file);
		printf("\n Sending error/exist: ");
		
		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			close(ns);
			exit(0);
		}
		
		recb=recv(ns,word,sizeof(word),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			close(ns);
			exit(0);
		}	
	
		printf("\nWord Recieved: ");
		printf("%s", word);
		char line[500];
		FILE *pf;
		int count = 0;
		pf = fopen(file , "r");           /* open file for reading */
		while (fgets(line, 500, pf) != NULL)    /* while there's another line */
		{
			if (strstr(line, word) != NULL)      /* if the pattern matches */
			{
			    ++count;                        /* add 1 to count */
			}
		}
		fclose(pf);
		memset(buff, 0, sizeof(buff));
		//printf("\n%d",count);
		if(count==0)
		{
			strcpy(buff,"Word doesnt exist");	
		}
		else
		{		
			sprintf(buff,"%d",count);		
		}
		printf("\nthe count is %s",buff);
		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			close(ns);
			exit(0);
		}


	}	
	close(ns);
	close(s);
}
