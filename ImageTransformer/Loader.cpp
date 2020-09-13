#include "Loader.h"
#include <fstream>


Loader::Loader() {}


std::vector<unsigned char>& Loader::Load(std::string filename)
{
	std::ifstream in;

	in.open(filename, std::ios::binary);

	//Specifies that an excecption will be thrown if the failbit is set when trying to
	//open a file,  rather than manually throwing an exception
	//this throws the exception
	//there are other bits that can be set as well to specify other exceptions
	in.exceptions(in.failbit);
	unsigned char dataByte;
	std::vector<unsigned char> loadData;
	while (!in.eof()) {
		in.read((char*)& dataByte, 1);
		loadData.push_back(dataByte);
	}
	in.close();

	return loadData;
}


