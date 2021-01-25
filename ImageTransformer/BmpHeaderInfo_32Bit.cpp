
/*
MIT License

Copyright(c) 2021 Jordan Kremer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


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

	bmpHeaderComponents_32Bit = std::make_unique<BmpHeaderComponents_32Bit>();
	bmpHeaderComponents_32Bit->_redBitMask = HeaderComponentsConstructorHelper(bmpConstants_32Bit.RED_CHANNEL_BITMASK, bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_greenBitmask = HeaderComponentsConstructorHelper(bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_blueBitMask = HeaderComponentsConstructorHelper(bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, hData);
	bmpHeaderComponents_32Bit->_alphaBitMask = HeaderComponentsConstructorHelper(bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK + 4, hData);

	

	for (int i = 0; i < GetImageStartOffset(); ++i)
	{
		//load rawdata and / or add an extra vector that holds this information to BmpHeader32bit
		bmpHeader32Bit_rawHeader.push_back(hData[i]);
	}
}

std::vector<unsigned char> BmpHeaderInfo_32Bit::GetRawHeader() const
{
	return bmpHeader32Bit_rawHeader;
}



void BmpHeaderInfo_32Bit::operator=(const HeaderInfo& toCopy)
{
}



uint32_t BmpHeaderInfo_32Bit::GetRedBitMask()
{
	return bmpHeaderComponents_32Bit->_redBitMask;
}



uint32_t BmpHeaderInfo_32Bit::GetGreenBitMask()
{
	return bmpHeaderComponents_32Bit->_greenBitmask;
}



uint32_t BmpHeaderInfo_32Bit::GetBlueBitMask()
{
	return bmpHeaderComponents_32Bit->_blueBitMask;
}



uint32_t BmpHeaderInfo_32Bit::GetAlphaBitMask()
{
	return bmpHeaderComponents_32Bit->_alphaBitMask;
}




