#pragma once
#include <memory>
#include "BmpHeaderInfo.h"
class BmpHeaderFactory
{
public:
	BmpHeaderFactory();
	const BmpHeaderInfo& GetBmpHeader(std::vector<unsigned char>& hData); //subject to change as more types become supported
	int GetCompression(std::vector<unsigned char>& hData);

};


/*
MAKE SINGLETON

*/
