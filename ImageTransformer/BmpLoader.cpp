#pragma once
#include "BmpLoader.h"
#include "BmpHeaderInfo.h"
#include <fstream>

using namespace std;

BmpLoader::BmpLoader(std::string FILENAME) {
	_FILENAME = FILENAME;
}

std::string BmpLoader::getFileName() const {
	return _FILENAME;
}


std::shared_ptr<Data> BmpLoader::Load() {

	ifstream in;

	in.open(_FILENAME, ios::binary);

	//Specifies that an excecption will be thrown if the failbit is set when trying to
	//open a file,  rather than manually throwing an exception
	//this throws the exception
	//there are other bits that can be set as well to specify other exceptions
	in.exceptions(in.failbit); 

	char ID[2];
	in >> ID[0] >> ID[1];
	in.seekg(0); //reset where we are reading from in the file, important

	//simple header check, not great validation
	//inherit from an exception class and use that inherited class here to throw exception
	//the caller can catch the exception using the base class 
	if (!(ID[0] == 'B' && ID[1] == 'M'))
		throw std::runtime_error("ERROR: NOT A BMP"); //include ID in error?

	std::vector<char> headerData;
	unsigned char tmp;
	int bitCount = 0;

	//http://www.fastgraph.com/help/bmp_header_format.html , 30 is the start of the compression bits

	//Do we go to 30 or 34? If we are going to read the last bits of this to get our compression..
	while (bitCount < 30 && in)
	{
		in.read((char*)& tmp, 1);
		headerData.push_back(tmp);
		++bitCount;
	}

	//may need to use UINT32
	int compression;
	in.read((char*)&compression, 4);


	//consider a different structure
	if (!(compression == 0 || compression == 3))
	{
		//if possible, find a better formatting method
		std::string msg = "ERROR: INVALID COMPRESSION: " + compression;
		throw std::runtime_error(msg);
	}





	/*
	in.seekg(10);
	int imageDataOffset;
	in.read((char*)& imageDataOffset, 4);
	if(imageDataOffset < )
	 
	in.seekg(); //
	//get the rest of header data
	while (bitCount < imageDataOffset && in) {
		in.read((char*)& tmp, 1);
		headerData.push_back(tmp);
		++bitCount;
	}
	
	
	//make_shared
	std::shared_ptr<BmpHeaderInfo> _bmpHeader = getBmpHeader(compression);
	*/

	in.close();
	


	return make_shared<Data>();
}


std::shared_ptr<BmpHeaderInfo> BmpLoader::getBmpHeader(int compression) {

	return std::make_shared<BmpHeaderInfo>();
}