#pragma once
#include "Data.h"

Data::Data()
{
}

Data::Data(std::vector<unsigned char>& data, std::vector<Pixel>& pixels, std::unique_ptr<HeaderInfo>& header)
{
	_rawData = data;
	_pixels = pixels;
	_header = std::move(header);
}

const int Data::GetCompression()
{
	return _header->GetCompression();
}
