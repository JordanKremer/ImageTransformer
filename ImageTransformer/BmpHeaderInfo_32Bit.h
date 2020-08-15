#pragma once
#include "BmpHeaderInfo.h"

class BmpHeaderInfo_32Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_32Bit();
	BmpHeaderInfo_32Bit(std::vector<char*> hData, int compression);
	const int getCompression();
	std::shared_ptr<const char*> getByte(int headerIndex);

private:

	std::vector<const unsigned char> _headerData; //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called
	std::map<std::string, int> _headerIndexMap;

	const int _compression;
};

