/*
Author : Jordan Kremer
11/20/2020
BmpHeaderFactory.cpp

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
	std::unique_ptr<BmpHeaderInfo> GetBmpHeader(std::vector<unsigned char>& rawData); //subject to change as more types become supported
	int GetCompression(std::vector<unsigned char>& rawData);

};

