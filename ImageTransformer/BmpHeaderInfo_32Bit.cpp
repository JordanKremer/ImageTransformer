#include "BmpHeaderInfo_32Bit.h"

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(): _compression(0){}

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(std::vector<char*> hData, int compression): _compression(compression){

}

const int BmpHeaderInfo_32Bit::getCompression() {
	return _compression;
}