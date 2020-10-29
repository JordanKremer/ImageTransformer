#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}

const BmpHeaderInfo& BmpHeaderFactory::GetBmpHeader(std::vector<unsigned char>& hData) {

	int compressionFlag = GetCompression(hData);



	if (compressionFlag < 0 || compressionFlag > 4) {
		std::string msg = "ERROR: COMPRESSION OUT OF BOUNDS : " + compressionFlag;
		throw std::runtime_error(msg);
	}

	if (compressionFlag < 3 && compressionFlag >= 0) {
		//return std::make_unique<BmpHeaderInfo>(hData);
		BmpHeaderInfo header(hData);
		return header;
	}
	else if (compressionFlag == 3) {
		//return std::make_unique<BmpHeaderInfo_32Bit>(hData);
		BmpHeaderInfo_32Bit header(hData);
		return header;
	}
	else
		throw std::runtime_error("ERROR: FAILED TO GENERATE BMPHEADER");
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


	//This correctly reads 3 for the 32 bit bear images because we start our read at byte 30, then the next 4 bytes contain the compression


	//how to convert 4 bytes to an int...
	/*
	int compressionFlag = int((unsigned char)(hData[30]) << 24 |
		(unsigned char)(hData[31]) << 16 |
		(unsigned char)(hData[32]) << 8 |
		(unsigned char)(hData[33]));
		*/

	uint32_t compressionFlag;
	((unsigned char*)& compressionFlag)[0] = hData[30];
	((unsigned char*)& compressionFlag)[1] = hData[31];
	((unsigned char*)& compressionFlag)[2] = hData[32];
	((unsigned char*)& compressionFlag)[3] = hData[33];

	//consider a different structure
	if (!(compressionFlag == 0 || compressionFlag == 3))
	{
		//if possible, find a better formatting method
		std::string msg = "ERROR: INVALID COMPRESSION: " + compressionFlag;
		throw std::runtime_error(msg);
	}

	return compressionFlag;
}