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
#include<vector>
#include <fstream> 
#include <string.h>
#include<time.h>
using namespace std;

#define MAX_ROUTERS 8

void writedvtable();

struct edge {
    char src;
    char dest;
    int cost;
};

struct graph {
    int V, E;
    vector<struct edge*> edges;
};

struct DV {
    char node;
    int min_dist;
    char nextNode;
}dvtable[MAX_ROUTERS];

struct graph* initGraph () 
{
    struct graph* g = new graph;
    g->E = 0;
    g->V = 0;
    g->edges.resize(0);
    return g;
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

void writedvtable(char src) {
        cout<<"ROUTER SHORTEST_DISTANCE PREV_NODE\n";
        for(int i = 0; i<MAX_ROUTERS; i++){
            if(dvtable[i].node!=-1) {
                if(dvtable[i].node == src)
                    cout << dvtable[i].node<<"\t\t\t"<< dvtable[i].min_dist << "\t\t\t\t*\n";
                else
                    cout << dvtable[i].node<<"\t\t\t"<< dvtable[i].min_dist << "\t\t\t\t" << dvtable[i].nextNode << "\n";
            }
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
    writedvtable('A');
}


int main()
{
    graph *maingraph=(struct graph*)malloc(sizeof(struct graph));
    initGraph();
    insertEdge(maingraph,'A','B',8);
    insertEdge(maingraph,'B','C',5);
    insertEdge(maingraph,'A','C',14);
    insertEdge(maingraph,'B','D',7);
    insertEdge(maingraph,'A','D',17);
    BellmanFord(maingraph,'A');
}