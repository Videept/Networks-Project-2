
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
#include <vector>
#include <fstream> 
#include <string.h>


using namespace std;

void parseTopology();
#define MAXLINE 1024 
#define MAX_ROUTERS 8

struct node {
     char letter ;
     int pNum;  // port number 
	 int numConnec; // number of neighbours it is connected to 
   // sockaddr_in addr; 
} node1; 

// Some sort of structure or class will be needed to keep details about 
// immediate neighbours
struct neighbourNode{
    char letter;
    int pNum;
    int wieght;
}neighbour[MAX_ROUTERS];


int main (){

    cout << "Calling parse toplogy function "<<endl ;
	node1.numConnec=0;
    parseTopology();
	int i;

// check by printing all 
	cout << "Connetions with "<<node1.letter<< "  should be "<< node1.numConnec<<endl;
	for (int i = 0; i<node1.numConnec; i++){
		cout <<"Source:"<<node1.letter<< " dest:" << neighbour[i].letter <<" Port:"<<neighbour[i].pNum << "";
		cout << " with weight:" <<  neighbour[i].wieght<< endl ; 
	}

	
    cout << "Past parse topology \n ";


    return 0;
}




void parseTopology() {
		// From topology file we are only interested in direct neigbours
	// We will receive other neighbours from exchanging DVs
	// If sub string 0 is equal to A then parse that line etc
	// i.e. parse only lies beginning with 'A'
	// Store information in struct or class 

    char letter,dest;
	int portNum;
	int wieght ;
    char buffer[MAXLINE];
    char createdRouters[MAX_ROUTERS];// not sure if needed

    ifstream tableFile;
    tableFile.open("tableTopology.txt");

    if (!tableFile){
		cout << " Fail to open table topology file \n";
	}
    // reads in first line which is description
    tableFile.getline(buffer,MAXLINE);

   if (tableFile.is_open()){
   // tableFile >> letter >>l2>> portNum> >wieght;
				// cout << "Letter 1 : " << letter<<" " <<l2<<"  "<< portNum <<"  " << wieght<< endl  ;
				tableFile >> letter; cout << letter <<endl ;node1.letter=letter;
				tableFile >> dest ; cout << dest<< endl; 
				tableFile >> portNum; cout <<portNum << endl ;node1.pNum=portNum; 
				tableFile >> wieght ; cout << wieght << endl; 
				createdRouters[0]=letter; createdRouters[1]= dest;
                node1.numConnec=1; 
                neighbour[ node1.numConnec-1].letter=dest; neighbour[node1.numConnec-1].pNum =portNum;
                neighbour[node1.numConnec-1].wieght=wieght;

        while (tableFile){
            tableFile>> letter;

            if (node1.letter == letter){
                // if its A parse a and add 1 to number connections
                node1.numConnec++; 
                tableFile >>dest>> portNum >>wieght ; 
                
                    neighbour[ node1.numConnec-1].letter=dest; neighbour[node1.numConnec-1].pNum =portNum;
                    neighbour[node1.numConnec-1].wieght=wieght;
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