//sourcelist.cpp
#include"SourceList.h"
using namespace std;
SourceList::SourceList(string filepath)
{
	ifstream SourceFile(filepath)
	string lineContents;
	while(sourceFile.eof())
	{
		getline(sourceFile,lineContents);
		Source s(lineContents);
		sources.push_back(s);
	}
	sourcesFile.close();
	sort(source.begin(), source.end(),[](Source &s1, Source &s2
	                                        {return s1.getlink_cost()>s2.getlink_cost();
											})) ;
}
Source SourceList::getValedic()
{
	
}
