#include<iostream>
#include"Source.h"
#include"SourceList.h"
using namespace std;
/*void printSource(Source source)       
{
	//Source source("A B 10001 4");
	cout<<source.getsource_router()<<" ";
	cout<<source.getdest_router()<<" ";
	cout<<source.getsource_port()<<" ";
	cout<<source.getlink_cost()<<" ";
}*/

int main(int argc, const char*argv[])
{
	
	SourceList list("topology.txt");//provide path of the file instead of filename.
	
	/*if(!list.is_open())
	{
	cout<<"ERROR:File OPEN";
	}
	string source_router, dest_router;
	string source_port, link_cost;
	string s_router, d_router, s_port, l_cost;
	while(list.good())
	{
		
	getline(list,source_router,':');
	getline(list,dest_router,':');
	getline(list,source_port,':');
	getline(list,link_cost,':');
		
		//std::cout<<source_router<<"  "<<dest_router<<"  "<<source_port<<"  "<<link_cost<<endl;
		std::cout<<s_router<<"  "<<d_router<<"  "<<s_port<<"  "<<l_cost<<endl;
	}
	list.close();*/
}
	for(Source s:list.sources)
	printSource(s);
	for(int i=0; i<list.size();i++)
	{
		Sources s=list.sources.at(i);
		printSource(s);
	}

	return 0;

}
