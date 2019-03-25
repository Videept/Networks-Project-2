


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <string>
#include <pthread.h>
#include <sstream>

#include "router.hpp"

/*  not finished - unsure if connecting output is all sebd messages 

work in progress
*/
#define bufferSize 1024 
#define routers 10
#define portNum 10000


int main(int atgc , char * argv[]){
  
    router router(argv);
    int sockfd;
    struct sockaddr_in addr; 
    char buffer[bufferSize] = {0}; 

    if (sockfd == router.socketSetUp < 0   ){
        std::cerr << " Error creating / binding to socket "<< std::endl ; 
    }


    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNum);     // this is wrong need to change the port numb 
    addr.sin_addr.s_addr =inet_addr("127.0.0.1"); // local machine
    socklen_t sizeAddr = sizeof (addr);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("   Did not succesfully bind \n");
    return 2;
    }

  // set socket to listen status
  if (listen(sockfd, 1) == -1) {
    perror("listen");
    return 3;
  }

    int send = sendto(sockfd,buffer,bufferSize ,0,(struct sockaddr*)&addr,  sizeAddr);
    if (send == -1 ){
        std:: cerr << " did not send "  << std :: endl; 
    }


    return 0 ; 

}





