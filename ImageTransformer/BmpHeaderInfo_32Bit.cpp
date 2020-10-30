#include "BmpHeaderInfo_32Bit.h"

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit()
{
}

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(BmpHeaderInfo_32Bit& to_copy)
{
}

BmpHeaderInfo_32Bit::BmpHeaderInfo_32Bit(std::vector<unsigned char> hData):BmpHeaderInfo(hData)
{

}

HeaderInfo* BmpHeaderInfo_32Bit::Clone() const
{
	return nullptr;
}

void BmpHeaderInfo_32Bit::operator=(const HeaderInfo& toCopy)
{
}




