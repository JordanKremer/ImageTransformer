#include "Loader.h"
#include <fstream>


Loader::Loader() {}


std::vector<unsigned char>& Loader::Load(std::string filename)
{

	std::ifstream in;

	in.open(filename, std::ios::binary);

	//exception is throw when using a loop with while(!in.eof), so using a range based for loop instead
	in.exceptions(in.failbit);


	in.seekg(0, in.end);
	int fileLength = in.tellg();
	in.seekg(0, in.beg);

	unsigned char dataByte;
	std::vector<unsigned char> loadData;
	
	for (int i = 0; i < fileLength; ++i)
	{
		in.read((char*)& dataByte, 1);
		loadData.push_back(dataByte);
	}
	in.close();

	return loadData;
}


