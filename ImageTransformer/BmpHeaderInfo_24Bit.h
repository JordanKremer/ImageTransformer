#pragma once
#include "BmpHeaderInfo.h"

class BmpHeaderInfo_24Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_24Bit();
	BmpHeaderInfo_24Bit(std::vector<char*> hdata, int compression);
	const int getCompression();
	std::shared_ptr<const char*> getByte(int headerIndex);
	~BmpHeaderInfo_24Bit(); //May need to manually delete the _headerData const char*

private:
	int _translateDecimaltoRGBA(uint32_t mask);

	//https://stackoverflow.com/questions/9834067/difference-between-char-and-const-char
	std::vector<const std::shared_ptr<const char>> _headerData; //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called
	std::map<std::string, int> _headerIndexMap;
	const int _compression;
};

