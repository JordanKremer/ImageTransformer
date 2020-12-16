/*
Author : Jordan Kremer
11/20/2020
BmpHeaderFactory.cpp

Using the factory design pattern, this class allows for the correct BmpHeader to be 
generated given our raw image data.

*/



#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_32Bit.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}



//Creates a BmpHeaderInfo ptr from the rawData, which is then used
//in the caller function to create a Data object.
std::unique_ptr<BmpHeaderInfo> BmpHeaderFactory::GetBmpHeader(std::vector<unsigned char>& rawData) {

	int compressionFlag = GetCompression(rawData);
	switch(compressionFlag)
	{
		case 0: return std::move(std::make_unique<BmpHeaderInfo>(rawData));
		case 1: return std::move(std::make_unique<BmpHeaderInfo>(rawData));
		case 2: return std::move(std::make_unique<BmpHeaderInfo>(rawData));
		case 3: return std::move(std::make_unique<BmpHeaderInfo_32Bit>(rawData));
		default: throw std::runtime_error("ERROR: FAILED TO GENERATE BMPHEADER, COMPRESSION OUT OF BOUNDS");
	}
}



//Takes the compression bytes from the header, bytes 30-33, and compresses them into
//a single integer. GetBmpHeader is the caller.
int BmpHeaderFactory::GetCompression(std::vector<unsigned char>& rawData)
{
	char ID[2];
	ID[0] = rawData[0];
	ID[1] = rawData[1];

	//Need to expand this validation
	if (!(ID[0] == 'B' && ID[1] == 'M'))
		throw std::runtime_error("ERROR: NOT A BMP");

	//Load compression bytes from the rawData into the integer
	uint32_t compressionFlag;
	for (int idx = 0; idx < 4; ++idx) {
		((unsigned char*)& compressionFlag)[idx] = rawData[idx + 30];
	}

	return compressionFlag;
}