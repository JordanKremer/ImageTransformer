#pragma once
#include <memory>
#include "BmpHeaderInfo.h"
class BmpHeaderFactory
{
public:
	BmpHeaderFactory();
	std::shared_ptr<BmpHeaderInfo> getBmpHeader(std::vector<char*>& hData, int compressionFlag); //subject to change as more types become supported

};

