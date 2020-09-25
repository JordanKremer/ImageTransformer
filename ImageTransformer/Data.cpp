#pragma once
#include "Data.h"

Data::Data()
{
}

Data::Data(std::vector<unsigned char>& data, std::shared_ptr<HeaderInfo> header)
{
	_rawData = data;
	_header = header; 
}
