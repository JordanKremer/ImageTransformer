/*
Author : Jordan Kremer
11/20/20
BmpHeaderInfo_32Bit.h

This class is an extension of BmpHeaderInfo. It includes extra data points 
only found in the header of the 32bit bmp images.

*/


#pragma once
#include "BmpHeaderInfo.h"



struct BmpHeader_32BitConstants {

	inline static const int RED_CHANNEL_BITMASK = 54;
	inline static const int GREEN_CHANNEL_BITMASK = 58;
	inline static const int BLUE_CHANNEL_BITMASK = 62;
	inline static const int	ALPHA_CHANNEL_BITMASK = 64;
};






class BmpHeaderInfo_32Bit :
	public BmpHeaderInfo
{
public:
	BmpHeaderInfo_32Bit();
	BmpHeaderInfo_32Bit(BmpHeaderInfo_32Bit& to_copy);
	BmpHeaderInfo_32Bit(std::vector<unsigned char>& hData);
	HeaderInfo* Clone() const;
	void operator=(const HeaderInfo& toCopy);

	//unsigned char getHeaderByte(int headerIndex);

private:

	//std::unique_ptr<BasicBmpHeaderComponents> _headerComponents;
	//std::vector<unsigned char> _headerData; //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called

};

