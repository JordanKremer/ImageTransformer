#pragma once
#include "Data.h"

Data::Data()
{
}

Data::Data(std::vector<unsigned char>& data, std::vector<Pixel>& pixels, HeaderInfo& header)
{
	_rawData = data;
	_pixels = pixels;
	_header = header;
}

const int Data::GetCompression()
{
	return _header->GetCompression();
}
