#include "BmpHeaderFactory.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}



std::shared_ptr<BmpHeaderInfo> BmpHeaderFactory::getBmpHeader(int compressionFlag) {
	if (compressionFlag < 0 || compressionFlag > 4) {
		std::string msg = "ERROR: COMPRESSION OUT OF BOUNDS : " + compressionFlag;
		throw std::runtime_error("");
	}

	if (compressionFlag == 0)
		return std::make_shared<BmpHeaderInfo>();
	if (compressionFlag == 3)
		return std::make_shared<BmpHeaderInfo_32Bit>();

	return NULL;
}