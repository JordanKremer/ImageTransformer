#pragma once
#include "BmpHeaderInfo.h"
class BmpHeaderInfo_24Bit :
	public BmpHeaderInfo
{
public:

private:
	int _translateDecimaltoRGBA(uint32_t mask);

	//https://stackoverflow.com/questions/9834067/difference-between-char-and-const-char
	std::vector<const char*> _headerData;
	std::map<std::string, int> _headerIndexMap;
};

