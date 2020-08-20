#include "BmpHeaderInfo_32Bit.h"

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit()
{
}

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(BmpHeaderInfo_32Bit& to_copy)
{
}

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(std::vector<unsigned char> hData)
{
}

std::vector<unsigned char>::const_iterator BmpHeaderInfo_32Bit::getHeaderBegin()
{
	std::vector<unsigned char>::const_iterator iter = _headerData.begin();
	return iter;
}

std::vector<unsigned char>::const_iterator BmpHeaderInfo_32Bit::getHeaderEnd()
{
	return std::vector<unsigned char>::const_iterator();
}

int BmpHeaderInfo_32Bit::getWidth() const
{
	return 0;
}

int BmpHeaderInfo_32Bit::getCompression() const
{
	return 0;
}
