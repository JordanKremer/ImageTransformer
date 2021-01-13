#include "BmpHeaderInfo_32Bit.h"

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit()
{
}



BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(BmpHeaderInfo_32Bit& to_copy)
{
}



BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(std::vector<unsigned char>& hData):BmpHeaderInfo(hData)
{
	BmpConstants bmpConstants;
	BmpHeader_32BitConstants bmpConstants_32Bit;

	bmpHeaderComponents_32Bit = std::move(std::make_unique<BmpHeaderComponents_32Bit>());
	bmpHeaderComponents_32Bit->_redBitMask = headerComponentsConstructorHelper(bmpConstants_32Bit.RED_CHANNEL_BITMASK, bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_greenBitmask = headerComponentsConstructorHelper(bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_blueBitMask = headerComponentsConstructorHelper(bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_alphaBitMask = headerComponentsConstructorHelper(bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK + 4, hData);

	

	for (int i = 0; i < GetImageStartOffset(); ++i)
	{
		//load rawdata and / or add an extra vector that holds this information to BmpHeader32bit
		bmpHeader32Bit_rawHeader.push_back(hData[i]);
	}
}

const std::vector<unsigned char> BmpHeaderInfo_32Bit::GetRawHeader() const
{
	return bmpHeader32Bit_rawHeader;
}



void BmpHeaderInfo_32Bit::operator=(const HeaderInfo& toCopy)
{
}



const uint32_t BmpHeaderInfo_32Bit::GetRedBitMask()
{
	return bmpHeaderComponents_32Bit->_redBitMask;
}



const uint32_t BmpHeaderInfo_32Bit::GetGreenBitMask()
{
	return bmpHeaderComponents_32Bit->_greenBitmask;
}



const uint32_t BmpHeaderInfo_32Bit::GetBlueBitMask()
{
	return bmpHeaderComponents_32Bit->_blueBitMask;
}



const uint32_t BmpHeaderInfo_32Bit::GetAlphaBitMask()
{
	return bmpHeaderComponents_32Bit->_alphaBitMask;
}




