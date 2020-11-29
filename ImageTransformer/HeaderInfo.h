/*
Author : Jordan Kremer
11/20/20
HeaderInfo.h

Abstract base class/ template for subclasses such as BmpHeader. Data.h contains this class, so it
is used as a generic way to have any type of HeaderInfo, including those in future
updates.
*/

#pragma once
#include <stdint.h> //for uint_32, causes an Override error without it

class HeaderInfo
{
public:
	//https://isocpp.org/wiki/faq/abcs#copy-of-abc-via-clone
	virtual HeaderInfo* Clone() const = 0;
	_NODISCARD virtual const uint32_t GetCompression() const = 0;
	_NODISCARD virtual const uint32_t GetBitsPerPixel() const = 0;
	_NODISCARD virtual const uint32_t GetImageStartOffset() const = 0;
	_NODISCARD virtual const uint32_t GetWidth() const = 0;
	_NODISCARD virtual const std::vector<unsigned char>& GetRawHeader() const = 0;
};
