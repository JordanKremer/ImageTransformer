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

	//simple header check, not great validation
	//inherit from an exception class and use that inherited class here to throw exception
	//the caller can catch the exception using the base class 
	if (ID[0] != 'B' && ID[1] != 'M')
		throw std::runtime_error("ERROR: NOT A BMP"); //include ID in error?
	
	std::vector<char> headerData;
	unsigned char tmp;
	int bitCount = 0;


	while (bitCount < 34 && in)
	{
		in.read((char*)& tmp, 1);
		headerData.push_back(tmp);
		bitCount++;
	}

	//need to read more bytes in
	if (//compression == 3) {

		//keeping reading in the rest of the header
	}
	
	BmpHeaderInfo* headerInfo;
	if (//compression == 0) {
		//headerInfo = new BmpHeaderInfo(headerData);
	}
	else {
		//headerInfo = new BmpHeaderInfo_32bit(headerData);
	}

	in.close();
	


	return make_shared<Data>();
}