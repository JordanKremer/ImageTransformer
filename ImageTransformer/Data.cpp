#pragma once
#include "Data.h"

Data::Data()
{
}

Data::Data(std::vector<unsigned char>& data, std::unique_ptr<HeaderInfo> header)
{
	_rawData = data;

	_header = std::move(header);
}

const int Data::GetCompression()
{
	return _header->GetCompression();
}
