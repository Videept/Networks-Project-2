//sourceList.h
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
class SourceList
{
	public:
		SourceList(std::string filepath);
		Source getVal1();
		std::vector<Source>getVal2();
		std::vector<Source>getVal3();
		
		//private:
			std::vector<Source>sources;
		};


