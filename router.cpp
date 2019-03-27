#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>

using namespace std;

#define PORT 4000 
#define MAXLINE 1024 

struct sockaddr_in cliaddr, servaddr;
int udpfd;
int portnum;

// Some sort of structure or class will be needed to keep details about 
// immediate neighbours
struct neighbour {
	int port;
	char id;
};


// This function is continuously checking for information on socket
void receive_th() {  
	
	int nready, maxfdp1;
	char buffer[MAXLINE];
	ssize_t n;
	fd_set rset;
	socklen_t len;	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(portnum);

	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	for (;;) {
		
		
		// binding server addr structure to udp sockfd 
		bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

		// clear the descriptor set 
		FD_ZERO(&rset);

		// get maxfd 
		maxfdp1 = udpfd;
		FD_SET(udpfd, &rset);

		if ((nready = select(maxfdp1 + 1, &rset, NULL, NULL, NULL)) == -1) {
			perror("select");
		}

		// if udp socket is readable receive the message. 
		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			bzero(buffer, sizeof(buffer));
			
			// From here we will branch to function that will parse 
			// the DV and place details in routing table
			//parseReceived(buffer);
			
			printf("\nMessage from UDP client: ");
			n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
				(struct sockaddr*)&cliaddr, &len);
			puts(buffer);

		}
	}
}

void parseReceived() {
	// In this function we will take what was received
	// in buffer and parse the details.
	// It will need to check if to see if there has been a change
	
	// It will also need to detect if it received a DV or a packet
	// IF Packet branch to 
	// handlePacket(buffer)
}

void handlePacket() {
	// Get DV up and running before tackling this 
}

void send_th() {

	struct neighbour b = { .port = 4001 };
	cliaddr.sin_port = htons(b.port);

	const char* message = "Hello Router";
	for (;;) {

		struct timeval t;
		t.tv_sec = 5;
		t.tv_usec = 0;
		select(0, NULL, NULL, NULL, &t);

		// Here we will loop through our direct neighbours sending them a DV 
		// every 5s 

		sendto(udpfd, (const char*)message, sizeof(message), 0,
			(struct sockaddr*)&cliaddr, sizeof(cliaddr));
	}

}

void parseTopology() {
	// From topology file we are only interested in direct neigbours
	// We will receive other neighbours from exchanging DVs
	// If sub string 0 is equal to A then parse that line etc

}

void createRoutingTable() {
	// Parse information from toplogy and DV into table
	// Use Bellman Ford to 
}


int main(int argc, char *argv[])
{
	
	if (argc > 1) {
		//Check if a file has been entered as argument 
		//Parse topology file
		if (argv[1]) {
			portnum = atoi(argv[1]);
			
			//parseTopology();
		}
	}

	// Set up thread so send and receive can run async
	thread dispatch(send_th);
	thread recv(receive_th);
	
	// Wait until
	dispatch.join();
	recv.join();
	
	
}