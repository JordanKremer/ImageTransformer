#pragma once
#include "BmpHeaderInfo.h"
class BmpHeaderInfo_32Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_32Bit(int compression); 
private:
	int _compression;
	std::vector<const char*> _headerData;
	std::map<std::string, int> _headerIndexMap;
};

