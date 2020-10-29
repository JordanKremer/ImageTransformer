#pragma once
#include <stdint.h> //for uint_32, causes an Override error without it

class HeaderInfo
{
public:
	//https://isocpp.org/wiki/faq/abcs#copy-of-abc-via-clone
	virtual HeaderInfo* Clone() const = 0;
	_NODISCARD virtual const uint32_t GetCompression() = 0;
	_NODISCARD virtual const uint32_t GetBitsPerPixel() = 0;
	_NODISCARD virtual const uint32_t GetImageStartOffset() = 0;
	_NODISCARD virtual const uint32_t GetWidth() = 0;
};
