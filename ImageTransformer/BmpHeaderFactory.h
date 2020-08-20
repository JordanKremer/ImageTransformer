#pragma once
#include <memory>
#include "BmpHeaderInfo.h"
class BmpHeaderFactory
{
public:
	BmpHeaderFactory();
	std::unique_ptr<BmpHeaderInfo> getBmpHeader(std::vector<unsigned char>& hData, int compressionFlag); //subject to change as more types become supported

};


/*
MAKE SINGLETON

*/
