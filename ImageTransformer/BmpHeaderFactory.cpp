#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}

std::shared_ptr<BmpHeaderInfo> BmpHeaderFactory::getBmpHeader(std::vector<unsigned char>& hData, int compressionFlag) {
	if (compressionFlag < 0 || compressionFlag > 4) {
		std::string msg = "ERROR: COMPRESSION OUT OF BOUNDS : " + compressionFlag;
		throw std::runtime_error(msg);
	}

	if (compressionFlag == 0)
		return std::make_shared<BmpHeaderInfo_24Bit>(hData);
	if (compressionFlag == 3)
		return std::make_shared<BmpHeaderInfo_32Bit>(hData);
	
	throw std::runtime_error("ERROR: FAILED TO GENERATE BMPHEADER");
}