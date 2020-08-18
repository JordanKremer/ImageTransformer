#pragma once
#include "BmpHeaderInfo.h"

class BmpHeaderInfo_24Bit :
	public BmpHeaderInfo
{
public:

	BmpHeaderInfo_24Bit();
	//BmpHeaderInfo_24Bit(const BmpHeaderInfo_24Bit& to_copy);
	BmpHeaderInfo_24Bit(std::vector<unsigned char> hdata);

	std::vector<unsigned char>::const_iterator getHeaderBegin();
	std::vector<unsigned char>::const_iterator getHeaderEnd();
	int getWidth();
	int getCompression();

	

private:
	int _translateDecimaltoRGBA(uint32_t mask);


	//https://stackoverflow.com/questions/9834067/difference-between-char-and-const-char
	std::vector<unsigned char> _headerData;  //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called
	std::map<const std::string, int> _headerIndexMap;
};

