#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}


//Creates a BmpHeaderInfo ptr from the rawData, which is then used
//in the caller function to create a Data object.
const BmpHeaderInfo* BmpHeaderFactory::GetBmpHeader(std::vector<unsigned char>& hData) {

	int compressionFlag = GetCompression(hData);
	switch(compressionFlag)
	{
		case 0: return new const BmpHeaderInfo(hData);
		case 1: return new const BmpHeaderInfo(hData);
		case 2: return new const BmpHeaderInfo(hData);
		case 3: return new const BmpHeaderInfo_32Bit(hData);
		default: throw std::runtime_error("ERROR: FAILED TO GENERATE BMPHEADER, COMPRESSION OUT OF BOUNDS");
	}
}

int BmpHeaderFactory::GetCompression(std::vector<unsigned char>& hData)
{
	char ID[2];
	ID[0] = hData[0];
	ID[1] = hData[1];

	//simple header check, not great validation
	//inherit from an exception class and use that inherited class here to throw exception
	//the caller can catch the exception using the base class 
	if (!(ID[0] == 'B' && ID[1] == 'M'))
		throw std::runtime_error("ERROR: NOT A BMP"); //include ID in error?

	uint32_t compressionFlag;
	((unsigned char*)& compressionFlag)[0] = hData[30];
	((unsigned char*)& compressionFlag)[1] = hData[31];
	((unsigned char*)& compressionFlag)[2] = hData[32];
	((unsigned char*)& compressionFlag)[3] = hData[33];

	if (!(compressionFlag == 0 || compressionFlag == 3))
	{
		//if possible, find a better formatting method
		std::string msg = "ERROR: INVALID COMPRESSION: " + compressionFlag;
		throw std::runtime_error(msg);
	}

	return compressionFlag;
}