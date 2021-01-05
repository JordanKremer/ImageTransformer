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
#include <vector>
#include <memory>
#include <map>

class HeaderInfo
{
public:
	//https://isocpp.org/wiki/faq/abcs#copy-of-abc-via-clone
	_NODISCARD virtual const uint32_t GetCompression() const = 0;
	_NODISCARD virtual const uint32_t GetBitsPerPixel() const = 0;
	_NODISCARD virtual const uint32_t GetImageStartOffset() const = 0;
	_NODISCARD virtual const uint32_t GetWidth() const = 0;
	_NODISCARD virtual const std::vector<unsigned char> GetRawHeader() const = 0;
	//_NODISCARD virtual std::unique_ptr<HeaderInfo> Clone(std::shared_ptr<std::map<int, int>> changeArgs) = 0;


	virtual void SetHeight(int newHeight) = 0;
	virtual void SetWidth(int newWidth) = 0;

};


/*


Various Header constructors?
	Header(new width, new height, header* to_copy)
	header(new width, new height, new filesize, header* to_copy)
		:: IMPORTANT, the new filesize is only for the scaling up or down

	these are virtual functions, which will dynamically dispatch to
	the correct subclasses to deal with this

	that way a JPEG can deal with jpeg construction, bmp can deal
	with bmp, etc 
	

	This will still keep it abstract so that any type can be used
	with the current setup as long as we are using Data as a
	generic
	*/