/*
Author : Jordan Kremer
11/20/20
HeaderInfo.h

Abstract base class/ interface for subclasses such as BmpHeader. GenericImage.h contains this class, so it
is used as a generic way to have any type of HeaderInfo, including those in future
updates.
*/

#pragma once
#include <stdint.h> //for uint_32, causes an Override error without it
#include <vector>
#include <memory>
#include <map>

class HeaderInfo
{
public:
	_NODISCARD virtual const uint32_t GetCompression() const = 0;
	_NODISCARD virtual const uint32_t GetBitsPerPixel() const = 0;
	_NODISCARD virtual const uint32_t GetImageStartOffset() const = 0;
	_NODISCARD virtual const uint32_t GetHeight() const = 0;
	_NODISCARD virtual const uint32_t GetWidth() const = 0;
	_NODISCARD virtual const std::vector<unsigned char> GetRawHeader() const = 0;
	
	virtual void SetHeight(int newHeight) = 0;
	virtual void SetWidth(int newWidth) = 0;

};
