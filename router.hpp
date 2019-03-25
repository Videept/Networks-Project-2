


//#pragma once 
#include <string.h>
#include <vector>
#include <iostream>




class router {
    
public:

    router(char * argv[]);
    int socketSetUp();


    // each router will have 
    int portNumber;
    char letter;
    bool stable; // if the table is in a stable state 


};