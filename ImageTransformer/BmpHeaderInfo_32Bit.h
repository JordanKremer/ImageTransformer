#pragma once
#include "BmpHeaderInfo.h"

/*
struct BmpHeader_32BitConstants{

}
*/

class BmpHeaderInfo_32Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_32Bit();
	BmpHeaderInfo_32Bit(BmpHeaderInfo_32Bit& to_copy);
	BmpHeaderInfo_32Bit(std::vector<unsigned char> hData);

	std::vector<unsigned char>::const_iterator getHeaderBegin();
	std::vector<unsigned char>::const_iterator getHeaderEnd();

	int getWidth();
	int getCompression(); //
	//unsigned char getHeaderByte(int headerIndex);

private:

	std::vector<unsigned char> _headerData; //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called

};

