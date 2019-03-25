




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

//not using namespace std
#define portNum 10000



router::router(char * argv[])
{
    // constructor 

    stable = false;
    portNumber =atoi(argv[2]); // SECOND ARGUMENT RETURNED 


}



int router::socketSetUp(){
    // function to open and bind the the socket 

    // open the socket
    int sockfd =socket(AF_INET, SOCK_DGRAM, 0);
    int yes =1;

    // clear the socket to allow it to be reused 
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            std::cerr << "1   Error clearing socket" << std::endl ; 
            return -1;
                    
        }

    // set up error checks 

        if (sockfd == -1){
            std::cerr << "2     Error opening the socket" << std::endl;
            return -1;
        }

    struct sockaddr_in addr;


   addr.sin_family = AF_INET;
   addr.sin_port = htons(portNum);     // short, network byte order-convert from little to big endian
   addr.sin_addr.s_addr =inet_addr("127.0.0.1");  // GIVE ANY ADDRESS 
   socklen_t sizeAddr = sizeof(addr); 


        if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            std:: cerr << "3       Error binding to the socket " << std :: endl ; 
            return -1; 
        }

    // ** only used for testing -check if socket succesfully opened adn binded to  
        std:: cout << "Socket opened and binded" << std:: endl; 


 return sockfd; 

}