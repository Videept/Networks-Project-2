


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
#include <string>
#include <pthread.h>
#include <sstream>
#include <iostream>



class router {
    
public:
    // router constructor 
    router();
    // router(char * argv[]);
    int socketSetUp(int p );
    int addPeer(int p);

    // each router will have 
    int portNumber;
    char letter; // identification for each node
    bool stable; // if the table is in a stable state 
    int node ; 
    

};






router::router() // char * argv[])
{
    // constructor 

    stable = false; 
    portNumber ; // SECOND ARGUMENT RETURNED 
    node = 0;

}



int router::socketSetUp( int Number ){

    // creat the socket 
    // function to open and bind the the socket 
    router router;
    router.portNumber =  Number ; 
    router.letter ='A';
    // open the socket
    int sockfd =socket(AF_INET, SOCK_DGRAM, 0);

    printf( "Initial socket created \n ");


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
   addr.sin_port = htons(router.portNumber);     // short, network byte order-convert from little to big endian
   addr.sin_addr.s_addr =inet_addr("127.0.0.1");  // GIVE ANY ADDRESS 
   socklen_t sizeAddr = sizeof(addr); 


        if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            std:: cerr << "3       Error binding to the socket " << std :: endl ; 
            return -1; 
        }
    

    // ** only used for testing -check if socket succesfully opened adn binded to  
    std:: cout << "\n ***      Socket opened and binded port: " << router.portNumber <<" letter "<<router.letter << std:: endl; 

    int send = sendto(sockfd,"hello", 5 , 0,(struct sockaddr*)&caddr,  sizecAddr); // send a message to sockets and see if it picks up 

 return sockfd; 

}


int router ::addPeer (int p , char letter,void *threadID  ){ // connected to the same port but will have a different letter 
    
    router router ;
    router.letter=letter;
    router.portNumber = p; 
    char buff[bufferSize];
    int rMessage; 
    struct sockaddr_storage sendAddr;


    cout << "\n Connection thread set up and running\n "<< endl; 

    int threadNum = (intptr_t) threadID;
    int peerSock= socket(AF_INET, SOCK_DGRAM, 0);

     if (peerSock < 0 ){
            std::cerr << " Error opening the socket" << std::endl;
            return -1;
    }

    // bond to the router - take the port number
    memset((char *)&peerSock, 0, sizeof(peerSock));       

    peerSock.sin_family = AF_INET;
    peerSock.sin_port = htons(router.portNum);
    peerSock.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockalen_t addrSize = sizeof(peerSock);

     if (bind( peerSock, (struct sockaddr*)&peerSock, sizeof(peerSock)) == -1) {
            std:: cerr << "   Error binding to the socket " << std :: endl ; 
            return -1; 
       }


       for (;;)
       {
        rMessage =recvfrom (peerSock,buff, bufferSize,0,(struct sockaddr *)&peerSock, addrSize)
        std:: cout << " Message is received  " << buff << std :: endl ;

            if (rMessage >0 ){
                buff[rMessage] = 0;
                // send the packet sendPacket(buff)
            }
       }
    close (routerSock);   

}






#define bufferSize 1024 
#define routers 10
#define portNum 40001
#define maxThread 15
// using namespace std; 

int main(int argc , char * argv[]){
  

    // should set up the initial router 
    router router,r2 ;
    std::cout << "PAST CONSTRUCTOR " << std::endl; 
   router.socketSetUp(portNum);
// try  to add another router to same port 

    r2.addPeer(portNum, 'B'); 

    // adding neighbour sockets 


//     int sockfd;
//     struct sockaddr_in addr, caddr; 
//     char buffer[bufferSize] = {0}; 
//     pthread_t threads[maxThread];

//     // if (sockfd == router.socketSetUp < 0   ){
//     //     std::cerr << " Error creating / binding to socket "<< std::endl ; 
//     // }
//     sockfd =socket(AF_INET, SOCK_DGRAM, 0);

//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(portNum);     // this is wrong need to change the port numb 
//     addr.sin_addr.s_addr =inet_addr("localhost"); // local machine
//     socklen_t sizeAddr = sizeof (addr);
    
//      if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
//     perror("   Did not succesfully bind \n");
//     return 2;
//     }

// while(true)
// {    
 

   

//   // set socket to listen status

//     caddr.sin_family = AF_INET;
//     caddr.sin_port = htons(4000);     // this is wrong need to change the port numb 
//     caddr.sin_addr.s_addr =inet_addr("localhost"); // local machine
//     socklen_t sizecAddr = sizeof (caddr);
 

//     int send = sendto(sockfd,"hello", 5 , 0,(struct sockaddr*)&caddr,  sizecAddr);
//     if (send == -1 ){
//         std:: cerr << " did not send "  << std :: endl; 
//     }


//     recvfrom(sockfd,(char*)buffer,bufferSize ,0,(struct sockaddr*)&addr ,&sizeAddr);

//     std::cout <<"Should be buffer \n "<<  buffer ;

// }
    return 0 ; 

}





// set up a and 
// run throup port number creating different peers with port adrress from router .cpp eg .i
// form file create 


// 
//
