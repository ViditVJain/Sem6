#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>


#define SERVER_PORT  12345

main (int argc, char *argv[])
{
   int    i, len, num, rc, on = 1;
   int    listen_sd, accept_sd;
   char   buffer[80];
   struct sockaddr_in6   addr;

   num=2;

   
   listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
   if (listen_sd < 0)
   {
      perror("socket creation failed");
      exit(-1);
   }

 /* 
  // rc = setsockopt(listen_sd,  SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
   if (rc < 0)
   {
      perror("setsockopt() failed");
      close(listen_sd);
      exit(-1);
   }*/
   

   memset(&addr, 0, sizeof(addr));
   addr.sin6_family      = AF_INET6;
   memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
   addr.sin6_port        = htons(SERVER_PORT);
   rc = bind(listen_sd,
             (struct sockaddr *)&addr, sizeof(addr));
   if (rc < 0)
   {
      perror("bind() failed");
      close(listen_sd);
      exit(-1);
   }

   
   
   rc = listen(listen_sd, 5);
   if (rc < 0)
   {
      perror("listen() failed");
      close(listen_sd);
      exit(-1);
   }

   
   printf("The server is ready\n");

   for (i=0; i < 2; i++)
   {
      
      printf("client#  %d\n", i+1);
      printf("  accepting\n");
      accept_sd = accept(listen_sd, NULL, NULL);
      if (accept_sd < 0)
      {
         perror("error in acccepting");
         close(listen_sd);
         exit(-1);
      }
      printf("  connection successful\n");

     
     
      rc = recv(accept_sd, buffer, sizeof(buffer), 0);
      if (rc <= 0)
      {
         perror("recv() failed");
         close(listen_sd);
         close(accept_sd);
         exit(-1);
      }
      
      printf("  You entered: %s ", buffer);
	int length;
	int flag=0;
      length = strlen(buffer);
      
    
    
    for(i=0;i < length ;i++){
        if(buffer[i] != buffer[length-i-1])
        {
            flag = 1;
             break;
	   }
	}
	
	
	
    
    if (flag) {
        strcpy(buffer,"this string is  not a paliNNNNdrome");
        rc=send(accept_sd,buffer,sizeof(buffer),0);
   	}    
   		 
   		 
   		 
    else {
        strcpy(buffer,"this string is a palIIIndrome");
        rc=send(accept_sd,buffer,sizeof(buffer),0);
    	}    
    
      
      if (rc <= 0)
      {
         perror("send() failed");
         close(listen_sd);
         close(accept_sd);
         exit(-1);
      }

  
      close(accept_sd);
   }

   
   close(listen_sd);
}
