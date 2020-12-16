/*
Author : Jordan Kremer
11/20/20
BmpHeaderInfo_32Bit.h

This class is an extension of BmpHeaderInfo. It includes extra data points 
only found in the header of the 32bit bmp images.

*/


#pragma once
#include "BmpHeaderInfo.h"


//32bit bmp images are BGRA within the channel data, despite the order in which 
//the masks appear in the header
struct BmpHeader_32BitConstants {

	inline static const int RED_CHANNEL_BITMASK = 54;
	inline static const int GREEN_CHANNEL_BITMASK = 58;
	inline static const int BLUE_CHANNEL_BITMASK = 62;
	inline static const int	ALPHA_CHANNEL_BITMASK = 64;
};



struct BmpHeaderComponents_32Bit {
	uint32_t _redBitMask;
	uint32_t _greenBitmask;
	uint32_t _blueBitMask;
	uint32_t _alphaBitMask;
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

};

