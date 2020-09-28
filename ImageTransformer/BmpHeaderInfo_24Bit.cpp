#include "BmpHeaderInfo_24Bit.h"
#include <stdexcept>

BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(){}

BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(const BmpHeaderInfo_24Bit& toCopy)
{
	
}

void BmpHeaderInfo_24Bit::operator=(const HeaderInfo& toCopy)
{
}



BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(std::vector<unsigned char> hData) 
{
	
	//	if (compression != 0)
		//	throw std::runtime_error("ERROR : BmpHeaderInfo_24Bit(std::vector<char*> hData, int compression) : INVALID COMPRESSION");
		//this may be dangerous, not sure if the values are mutable or not

		

	
	unsigned char tmp;
	for (auto& d : hData) {
		tmp = d;
		_headerData.push_back(tmp);
	}

}



std::vector<unsigned char>::const_iterator BmpHeaderInfo_24Bit::getHeaderBegin()
{
	// TODO: insert return statement here
	return _headerData.begin();
}



std::vector<unsigned char>::const_iterator BmpHeaderInfo_24Bit::getHeaderEnd()
{
	// TODO: insert return statement here
	return _headerData.end();
}

int BmpHeaderInfo_24Bit::getWidth() const
{
	return 0;
}


BmpHeaderInfo_24Bit::~BmpHeaderInfo_24Bit()
{
}

