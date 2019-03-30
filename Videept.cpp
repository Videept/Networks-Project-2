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
#include <fstream> 
#include <string.h>

using namespace std;

#define MAXLINE 1024 
#define MAX_ROUTERS 8

struct sockaddr_in cliaddr, servaddr;
int udpfd;

// Some sort of structure or class will be needed to keep details about 
// immediate neighbours

// Struct to hold router details
struct node {
     char letter ;
     int pNum;  // port number 
	 int numConnec; // number of neighbours it is connected to 
   // sockaddr_in addr; 
} node1; 


// Details of neighbour routers
struct neighbourNode{
    char letter;
    int pNum;
    int cost;
}neighbour[MAX_ROUTERS];

struct edge {
    char src;
    char dest;
    int cost;
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

struct router
{
	char src;
	int portnum;
};

struct DV {
    char node;
    int min_dist;
    char nextNode;
}dvtable[MAX_ROUTERS];


// This function is continuously checking for information on socket
void receive_th() {  
	
	int nready, maxfdp1;
	char buffer[MAXLINE];
	ssize_t n;
	fd_set rset;
	socklen_t len;	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //(INADDR_ANY);
	servaddr.sin_port = htons(node1.pNum);

	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1){
			perror("Bind");
		}
	
	for (;;) {
		
		struct timeval t;
		t.tv_sec = 5;
		t.tv_usec = 0;

		// binding server addr structure to udp sockfd 
		

		// clear the descriptor set 
		FD_ZERO(&rset);

		// get maxfd 
		maxfdp1 = udpfd;
		FD_SET(udpfd, &rset);

		if ((nready = select(maxfdp1 + 1, &rset, NULL, NULL, &t)) == -1) {
			perror("select");
		}

		// if udp socket is readable receive the message. 
		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			bzero(buffer, sizeof(buffer));
			
			// From here we will branch to function that will parse 
			// the DV and place details in routing table
			//parseReceived(buffer);
			
			printf("\nMessage from Router: ");
			n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
				(struct sockaddr*)&cliaddr, &len);
			puts(buffer);

		}
	}
}

void costTable() 
{
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

	
	const char* message = "Hello Router";
	for (;;) {

		struct timeval t;
		t.tv_sec = 10;
		t.tv_usec = 0;
		select(0, NULL, NULL, NULL, &t);

		// Here we will loop through our direct neighbours sending them a DV 
		// every 5s 

		// createDV();

		// Send DV

		for(int i=0; i<node1.numConnec; i++){
			cliaddr.sin_port = htons(neighbour[i].pNum);			
			sendto(udpfd, (const char*)message, sizeof(message), 0,
			(struct sockaddr*)&cliaddr, sizeof(cliaddr));
			cout<<"Sent message to port: "<< neighbour[i].pNum<<endl; 

		}

		
	}

}

void parseTopology(char* file) {
	// From topology file we are only interested in direct neigbours
	// We will receive other neighbours from exchanging DVs
	// If sub string 0 is equal to A then parse that line etc
	// i.e. parse only lies beginning with 'A'
	// Store information in struct or class 

	char letter,dest;
	int portNum;
	int cost;
    char buffer[MAXLINE];
    char createdRouters[MAX_ROUTERS];// not sure if needed

    ifstream tableFile;
    tableFile.open(file);

    if (!tableFile){
		cout << " Fail to open table topology file \n";
	}
    // reads in first line which is description
    tableFile.getline(buffer,MAXLINE);

   if (tableFile.is_open()){
   

        while (tableFile){
            tableFile>> letter;

            if (node1.letter == letter){
                // if its A parse a and add 1 to number connections
                node1.numConnec++; 
                tableFile >>dest>> portNum >>cost ; 
                
                    neighbour[ node1.numConnec-1].letter=dest; neighbour[node1.numConnec-1].pNum =portNum;
                    neighbour[node1.numConnec-1].cost=cost;
            }
            else {
                tableFile.getline(buffer,MAXLINE);
                memset(buffer,0,MAXLINE);
            }
            letter= '0';

        }     
   
   }
	cout << "\n FOR TEST , value of num connec = " <<node1.numConnec<<endl ;
	tableFile.close();
	
}

void createDV() {
	// Use information from routing table to create DV
	// Take the row correlating to that router 
	// Format of DV in Report 
	// Single vector containing distances to all neighbour nodes
}

void writeDVtable()
{
	fstream file;
	char base='A';
	router exrouter;
	char src(exrouter.src);
	string createtable= src+"table.txt";
	file.open(createtable,ios::out); 
	if(!file) 
   { 
       cout<<"Error in creating file!!!";
   }
   if(file.is_open())
   {
	   for(int i=0;i<MAX_ROUTERS;i++)
	   {
		   if(dvtable[i].node!=exrouter.src)
				file<<dvtable[i].node<<"\t"<<dvtable[i].min_dist<<1000+int(src)-int(base)<<1000+int(dvtable[1].node)-int(base)<<"\n";
	   }
   }
   else
   {
	   cout<<"Error in writing to file";
   } 
}


void BellmanFord(struct graph* g, int src)    
{
    int V = g->V;
    int E = g->E;
    
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    
	for (int i = 0; i < MAX_ROUTERS; i++)
    {
        dvtable[i].node = (char) (i+65);
        dvtable[i].min_dist = 10000;
        dvtable[i].nextNode = -1;
    }
    
    //Assuming A is first vertex and so on...
    dvtable[src%65].min_dist = 0;

    // Step 2: Relax all edges |V| - 1 times.
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = g->edges[j]->src;
            int v = g->edges[j]->dest;
            int cost = g->edges[j]->cost;
            //if (dist[u-65] != 10000 && dist[u-65] + cost < dist[v-65])
            //    dist[v-65] = dist[u-65] + cost;
            if(dvtable[u%65].min_dist != 10000 && dvtable[u%65].min_dist + cost < dvtable[v%65].min_dist) {
                dvtable[v%65].min_dist = dvtable[u%65].min_dist + cost;
                dvtable[v%65].nextNode = dvtable[u%65].node;
            }
        }
	} 
}



void insertEdge(struct graph* g, char src, char dest, int cost) {
    int flag = 0;
    edge *e = (struct edge*)malloc(sizeof(struct edge));
    e->src = src;
    e->dest = dest;
    e->cost = cost;
    if(g->V == 0)	//if this is the first edge of our setup
	{
        g->E++;
        g->V+=2;
        g->edges.push_back(e);
        cout<<"Properties of Added Edge: "<<g->edges[0]->src<<"->"<<g->edges[0]->dest<<" cost: "<<g->edges[0]->cost;
    }
    else{
        for(int i = 0; i<g->edges.size(); i++){     //If edge already exists, just update cost
            if(g->edges[i]->src == src) {
                if(g->edges[i]->dest == dest) {
                    cout<<"Edge already exists"<<endl;
                    flag = 1;
                    if(g->edges[i]->cost != cost) {
                        cout<<"Updating cost"<<endl;
                        g->edges[i]->cost = cost;
                        flag = 1;
                    }
                }             
            }
        }
        if(flag == 0) {     //Adding edge if it doesn't already exist in the graph
            int index, v1 = 1, v2= 1;            
            g->E++;
            g->edges.push_back(e);
            for(int i = 0; i<g->edges.size(); i++)	//seeing if vertices have been previously defined
            {
                if(g->edges[i]->src == src|| g->edges[i]->dest == src)
                    v1 = 0;
                if(g->edges[i]->src == dest || g->edges[i]->dest == dest)
                    v2 = 0;
            }                
            g->V = g->V + v1 + v2;
            index = g->edges.size()-1;
            cout<<"Inserted new edge***:"<<g->edges[index]->src<<"->"<<g->edges[index]->dest<<" W: "<<g->edges[index]->cost;
        }
    }
    cout<<"\n";
}


int main(int argc, char *argv[])
{
	char *filename;
	char r_name;
	
	if (argc > 1) {
		//Check if a file has been entered as argument 
		
		if (argv[1]) {
			filename = argv[1]; 
			
		}

		if (argv[2]) {
			// The second argument will contain the id of the router 
			// we are setting up. i.e. A or B or C ....
			node1.letter = argv[2][0];
		}
	}
	
	// Convert letter to int port number 
	node1.pNum = node1.letter + 9935; 
	cout<<"Port Number: "<<node1.pNum<<endl;
	
	//Parse topology file
	parseTopology(filename);


	//maingraph = initGraph();

	// Set up thread so send and receive can run async
	thread recv(receive_th);
	thread dispatch(send_th);
	
	
	// Wait until
	dispatch.join();
	recv.join();
}
