//constructor
//source.cpp
#include"Source.h"
using namespace std;
Source::Source(string sourceInfo)
{
	stringstream sourceStream(sourceInfo);
	sourceStream>>source_router;
	sourceStream>>dest_router;
	sourceStream>>source_port;
	sourceStream>>link_cost;
}
string Source::getsource_router()
{
	return source_router;
}
string Source::getdest_router()
{
	return dest_router;
}
int Source::getsource_port()
{
	return source_port;
}
int Source::getlink_cost()
{
	return link_cost;
}
