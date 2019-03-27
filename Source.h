//class
//source.h
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
class Source
{
	public:
		Source(string sourceInfo);
		string getsource_router();
		string getdest_router();
		string getsource_port();
		string getlink_cost();
		//int getsource_port();
		//int getlink_vector();
	private:
		string source_router;
		string dest_router;
	   // int getsource_port();
	    //int getlink_vector();
	    string source_port;
		string link_cost;
			
		
};
