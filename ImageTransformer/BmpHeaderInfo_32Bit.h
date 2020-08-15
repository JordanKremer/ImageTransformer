#pragma once
#include "BmpHeaderInfo.h"

class BmpHeaderInfo_32Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_32Bit();
	BmpHeaderInfo_32Bit(std::vector<char*> hData, int compression);
	const int getCompression();

private:

	std::vector<const char*> _headerData;
	std::map<std::string, int> _headerIndexMap;

	const int _compression;
};

