
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
/*  not finished - unsure if connecting output is all sebd messages 

work in progress
*/

using namespace std;

#define buffSize 1024
#define portNum 40000
static int clientSockfd;
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
void *comm(void *ptr);
//*change from sock stream to data 


int
main(int atgc,const char* argv[]){
  
 
      pthread_t threads[15];
      // create a socket using TCP IP
    

      // allow others to reuse the address
      int yes= 1 ,ThreadCount = 0;
        // int messageIn, reply ,len; 
      struct sockaddr_in addr,serv;
      socklen_t clientAddrSize = sizeof(addr);


          if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            return 1;
          }



      // bind address the socket to an ip addreess amd port 40000
      
      memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
      memset(serv.sin_zero, '\0', sizeof(serv.sin_zero));

      addr.sin_family = AF_INET;
      addr.sin_port = htons(portNum);     // short, network byte order-convert from little to big endian
      addr.sin_addr.s_addr =INADDR_ANY;  // GIVE ANY ADDRESS 
      
     serv.sin_family = AF_INET;
     serv.sin_port = htons(portNum);
     serv.sin_addr.s_addr = INADDR_ANY; // inet_addr("127.0.0.1");
   

      if (bind(sockfd, (struct sockaddr*)&serv, sizeof(addr)) == -1) {
                perror("error binding to socket");
                return 2;
            }

            


      stringstream ss;

      while (ThreadCount< 10 ){
            
            pthread_create(&threads[ThreadCount],NULL,comm,NULL);
            ThreadCount++;
        }
      

        for(int i = 0; i < 15; i++){
            pthread_join(threads[i], NULL);
          }

       
        return 0;
    
    
}

void *comm (void *pt )
  {
            sleep(1);

            char buffer2[buffSize]  = {0}, buff [buffSize]={0};     
            int messageIn, send , reply ,len,r2; 
            struct sockaddr_in addr,peer;

            socklen_t clientAddrSize = sizeof(addr);
            socklen_t peerAddrSize = sizeof(peer);

            std::stringstream ss;
            bool isEnd = false;

             char ipstr[INET_ADDRSTRLEN] = {'\0'};
             inet_ntop(addr.sin_family, &addr.sin_addr, ipstr, sizeof(ipstr));
            int test_count=0;
            

          while (true){
                // In a loop recv the message 
                // process it
                // if need to send updates send to whoever 
            test_count ++; 
                        bool isEnd = false;
                        char buf[20] = {0};
                        stringstream ss;
                        string input;


                       while (!isEnd) {
                              memset( buf, '\0', sizeof(buf));

                              cout << "send: ";
                              cin >> input;

                              /// change 
                              if (sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&peer,peerAddrSize) == -1) {
                                perror("send");
                              //  return 4;
                              }


                              if (recvfrom(sockfd,buff,buffSize,0,(struct sockaddr *)&addr,&clientAddrSize) == -1){
                                perror("recv");
                                   //    return 5;
                              }

                              ss << buf << endl;
                              cout << "echo: ";
                              cout << buf << endl;

                              if (ss.str() == "close\n")
                                break;

                              ss.str("");
                  } // consider as client hanndeling 


            // cout << "\n Enter message going to send "<< test_count <<  endl ;
            // // fgets(buff,buffSize, stdin);
            // // establishing sender - initialising message communication
            // send = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&peer,peerAddrSize);
           
            // should 
            messageIn = recvfrom(sockfd, (char *)buffer2, buffSize, 0 ,(struct sockaddr *) &addr, &clientAddrSize) ;
            
            memset(buffer2, '\0', buffSize);

            buffer2[messageIn] ='\0';

                if (messageIn == -1) 
                  perror("Error receiving from client \n");
                

            ss << buffer2 << std::endl;
            std::cout << buffer2 << std::endl;
                

            // as udp no reply necessry after reply , if we want any sort of ack/response here - may be useful testing

            reply = sendto(sockfd,"ack",3 ,0 , (struct sockaddr *)&addr,sizeof(addr));

                if (reply ==-1 ){
                    cout << "Error writing to the client "<< endl ; 
                  }


            // printf("Reply sent \n");
            // r2= recvfrom(sockfd,buff,buffSize,0,(struct sockaddr *)&addr,&clientAddrSize);

            }

        
      close(clientSockfd);
      pthread_exit(NULL);    


}

void BellmanFord(struct graph* g, int src)    
{
    int V = g->V;
    int E = g->E;
    
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < MAX_ROUTERS; i++)
    {
        dvinfo[i].node = (char) (i+65);
        dvinfo[i].shortestDist = 10000;
        dvinfo[i].nextNode = -1;
    }
    
    //Assuming A is first vertex and so on...
    dvinfo[src%65].shortestDist = 0;

    // Step 2: Relax all edges |V| - 1 times.
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = g->edges[j]->v1;
            int v = g->edges[j]->v2;
            int weight = g->edges[j]->weight;
            //if (dist[u-65] != 10000 && dist[u-65] + weight < dist[v-65])
            //    dist[v-65] = dist[u-65] + weight;
            if(dvinfo[u%65].shortestDist != 10000 && dvinfo[u%65].shortestDist + weight < dvinfo[v%65].shortestDist) {
                dvinfo[v%65].shortestDist = dvinfo[u%65].shortestDist + weight;
                dvinfo[v%65].nextNode = dvinfo[u%65].node;
            }
        }
    } 

