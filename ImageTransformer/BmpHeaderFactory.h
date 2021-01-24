/*
Author : Jordan Kremer
11/20/2020
BmpHeaderFactory.h

Using the factory design pattern, this class allows for the correct BmpHeader to be
generated given our raw image data.
*/



#pragma once
#include <memory>
#include "BmpHeaderInfo.h"
class BmpHeaderFactory
{
public:
	BmpHeaderFactory();
	//Subject to change as more subtypes become supported
	std::unique_ptr<BmpHeaderInfo> GetBmpHeader(std::vector<unsigned char>& rawData);
	//Different compression values for different bmp subtypes (4, 8, 24, 32 bit bmp files)
	int GetCompression(std::vector<unsigned char>& rawData);

};

