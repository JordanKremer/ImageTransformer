#include "BmpHeaderInfo_24Bit.h"
#include <stdexcept>

BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(): _compression(0){}



BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(std::vector<char*> hData, int compression):_compression(compression) {
	if (compression != 0)
		throw std::runtime_error("ERROR : BmpHeaderInfo_24Bit(std::vector<char*> hData, int compression) : INVALID COMPRESSION");
	//this may be dangerous, not sure if the values are mutable or not

	/*
	for (auto& d : hData) {
		const char* tmp = d;
		_headerData.push_back(tmp);
	}
	*/
}



std::shared_ptr<const char> getByte(int index) {

}



const int BmpHeaderInfo_24Bit::getCompression() {
	return _compression;
}