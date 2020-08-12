#include "BmpHeaderFactory.h"
#include <stdexcept>


BmpHeaderFactory::BmpHeaderFactory() {}
std::shared_ptr<BmpHeaderInfo> BmpHeaderFactory::getBmpHeader(int compressionFlag) {
	if (compressionFlag < 0 || compressionFlag > 4) {
		std::string msg = "ERROR: COMPRESSION OUT OF BOUNDS : " + compressionFlag;
		throw std::runtime_error("");
	}


}