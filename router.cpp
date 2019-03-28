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
#include<vector>

using namespace std;

#define MAXLINE 1024 
#define MAX_ROUTERS 8

struct sockaddr_in cliaddr, servaddr;
int udpfd;
int portnum;

// Some sort of structure or class will be needed to keep details about 
// immediate neighbours
struct neighbour {
	int port;
	char id;
};

struct edge {
    char v1;
    char v2;
    int weight;
};

struct graph {
    int V, E;
    vector<struct edge*> edges;
};

struct graph* maingraph;

struct graph* initGraph () 
{
    struct graph* g = new graph;
    g->E = 0;
    g->V = 0;
    g->edges.resize(0);
    return g;
}

struct DV {
    char node;
    //int port;
    int shortestDist;
    char nextNode;
}dvinfo[MAX_ROUTERS];


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

void costTable() {
	// MAY NOT BE NEEDED
	// Constructs and maintains table that
	// contains cost to each node in the topology
	// Initially filled with its own row from topology file
}

void routingTable() {
	// Each outer maintains its own routing table
	// A nxn matrix where n is the number of routers in topology
	// Distance to itself is zero
	// Initially distance to all other nodes is zero
}

void nextHopTable() {
	// Constructs and maintains table that
	// contains next hop which will be used to find 
	// the next router to send the packet to 
	// i.e. it will contain the next router along the
	// shortest path to packets destination
}

void parseReceived() {
	// In this function we will take what was received
	// in buffer and parse the details.
	// It will need to check if to see if there has been a change
	// i.e if B says its distance X is 5 and we have distance to 
	// X as 8. Check distance from A to B + 5 and if < 8 update
	// Call bellman ford 

	
	// It will also need to detect if it received a DV or a packet
	// IF Packet branch to 
	// handlePacket(buffer)
}

void handlePacket() {
	// Get DV up and running before tackling this 
	// Will parse header to find destination router
	// Use nextHopTable to find port to send the packet
	// Send packet to this port 
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

		// createDV();

		// Send DV

		sendto(udpfd, (const char*)message, sizeof(message), 0,
			(struct sockaddr*)&cliaddr, sizeof(cliaddr));
	}

}

void parseTopology() {
	// From topology file we are only interested in direct neigbours
	// We will receive other neighbours from exchanging DVs
	// If sub string 0 is equal to A then parse that line etc
	// i.e. parse only lies beginning with 'A'
	// Store information in struct or class 
}

void createDV() {
	// Use information from routing table to create DV
	// Take the row correlating to that router 
	// Format of DV in Report 
	// Single vector containing distances to all neighbour nodes
}


int main(int argc, char *argv[])
{
	
	if (argc > 1) {
		//Check if a file has been entered as argument 
		//Parse topology file
		if (argv[1]) {
			portnum = atoi(argv[1]); // Using port number for initial testing
			
			//parseTopology();
		}

		/*if (argv[2]) {
			// The second argument will contain the id of the router 
			// we are setting up. i.e. A or B or C ....
		}*/
	}

	maingraph = initGraph();

	// Set up thread so send and receive can run async
	thread dispatch(send_th);
	thread recv(receive_th);
	
	// Wait until
	dispatch.join();
	recv.join();
	
	
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
}