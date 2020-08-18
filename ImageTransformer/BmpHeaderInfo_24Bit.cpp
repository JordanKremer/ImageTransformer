#include "BmpHeaderInfo_24Bit.h"
#include <stdexcept>

BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(){}



BmpHeaderInfo_24Bit::BmpHeaderInfo_24Bit(std::vector<unsigned char> hData) {
	
	//	if (compression != 0)
		//	throw std::runtime_error("ERROR : BmpHeaderInfo_24Bit(std::vector<char*> hData, int compression) : INVALID COMPRESSION");
		//this may be dangerous, not sure if the values are mutable or not

		

	
	unsigned char tmp;
	for (auto& d : hData) {
		tmp = d;
		_headerData.push_back(tmp);
	}

	_headerIndexMap.insert(std::pair<const std::string, int>(Constants::COMPRESSION, 0));

	
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

int BmpHeaderInfo_24Bit::getWidth()
{
	return 0;
}




int BmpHeaderInfo_24Bit::getCompression() {
	return _headerData[_headerIndexMap[Constants::COMPRESSION]];
}

