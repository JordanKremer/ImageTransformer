/*
MIT License

Copyright(c) 2021 Jordan Kremer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "BmpHeaderInfo.h"
#include <stdexcept>



BmpHeaderInfo::BmpHeaderInfo()
{
	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();

	bmpHeaderComponents->_filesize = 0;
	bmpHeaderComponents->_imageStartOffset = 0;
	bmpHeaderComponents->_width = 0;
	bmpHeaderComponents->_height = 0;
	bmpHeaderComponents->_bitsPerPixel = 0;
	bmpHeaderComponents->_compression = 0;
	bmpHeaderComponents->_horizontalResolution = 0;
	bmpHeaderComponents->_verticalResolution = 0;
}


//First checks if Header is of correct size for a Bmp header, given 
//the standard formats for Bmp images.
BmpHeaderInfo::BmpHeaderInfo(const std::vector<unsigned char>& data)
{
	
	if (data.size() < 54) {
		std::string msg = "ERROR: HEADER DATA IS TOO SMALL:: SIZE: " + data.size();
		throw std::length_error(msg);
	}

	BmpConstants bmpConstants;
	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();

	bmpHeaderComponents->_filesize = headerComponentsConstructorHelper(bmpConstants.FILESIZE, bmpConstants.RESERVED1, data);
	bmpHeaderComponents->_imageStartOffset = headerComponentsConstructorHelper(bmpConstants.IMAGESTARTOFFSET, bmpConstants.HEADERSIZE, data);
	bmpHeaderComponents->_width = headerComponentsConstructorHelper(bmpConstants.WIDTH, bmpConstants.HEIGHT, data);
	bmpHeaderComponents->_height = headerComponentsConstructorHelper(bmpConstants.HEIGHT, bmpConstants.COLORPANES, data);
	bmpHeaderComponents->_bitsPerPixel = headerComponentsConstructorHelper(bmpConstants.BITSPERPIXEL, bmpConstants.COMPRESSION, data);
	bmpHeaderComponents->_compression = headerComponentsConstructorHelper(bmpConstants.COMPRESSION, bmpConstants.IMAGESIZE, data);
	bmpHeaderComponents->_horizontalResolution = headerComponentsConstructorHelper(bmpConstants.HORIZONTALRESOLUTION, bmpConstants.VERTICALRESOLUTION, data);
	bmpHeaderComponents->_verticalResolution = headerComponentsConstructorHelper(bmpConstants.VERTICALRESOLUTION, bmpConstants.NUMCOLORSINPALETTE, data);

	rawData.reserve(54);

	for (int i = 0; i < 54; ++i)
	{
		rawData.push_back(data[i]);
	}
}


//Converts unsigned char bytes of the rawData into usable integer components that
//can be easily read
uint32_t BmpHeaderInfo::headerComponentsConstructorHelper(const int bmpConstantStart, const int bmpConstantEnd, const std::vector<unsigned char>& data)
{
	uint32_t tmpCharToIntConversion = 0;
	int loadIdx = 0;
	for (int dataIdx = bmpConstantStart; dataIdx < bmpConstantEnd; ++dataIdx)
	{
		((unsigned char*)& tmpCharToIntConversion)[loadIdx] = data[dataIdx];
		++loadIdx;
	}
	return tmpCharToIntConversion;
}

void BmpHeaderInfo::HeaderRawImageDataSetterFromIntegerHelper(uint32_t dataToChangeTo, const int bmpConstantStart, const int bmpConstantEnd, std::vector<unsigned char>& rawData)
{
	BmpConstants con;
	int loadIdx = 0;
	for (int dataIdx = bmpConstantStart; dataIdx < bmpConstantEnd; ++dataIdx)
	{
		rawData[dataIdx] = ((unsigned char*)& dataToChangeTo)[loadIdx];
		++loadIdx;
	}
}


//Copy constructor
BmpHeaderInfo::BmpHeaderInfo(const BmpHeaderInfo& toCopy)
{
	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();
	bmpHeaderComponents->_ID = toCopy.bmpHeaderComponents->_ID;
	bmpHeaderComponents->_filesize = toCopy.bmpHeaderComponents->_filesize;
	bmpHeaderComponents->_imageStartOffset = toCopy.bmpHeaderComponents->_imageStartOffset;
	bmpHeaderComponents->_width = toCopy.bmpHeaderComponents->_width;
	bmpHeaderComponents->_height = toCopy.bmpHeaderComponents->_height;
	bmpHeaderComponents->_bitsPerPixel = toCopy.bmpHeaderComponents->_bitsPerPixel;
	bmpHeaderComponents->_compression = toCopy.bmpHeaderComponents->_compression;
	bmpHeaderComponents->_verticalResolution = toCopy.bmpHeaderComponents->_verticalResolution;
	bmpHeaderComponents->_horizontalResolution = toCopy.bmpHeaderComponents->_horizontalResolution;

	rawData = toCopy.rawData;
}




BmpHeaderInfo& BmpHeaderInfo::operator=(const BmpHeaderInfo& toCopy)
{
	if (this == &toCopy)
		return *this;

	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();
	bmpHeaderComponents->_ID = toCopy.bmpHeaderComponents->_ID;
	bmpHeaderComponents->_filesize = toCopy.bmpHeaderComponents->_filesize;
	bmpHeaderComponents->_imageStartOffset = toCopy.bmpHeaderComponents->_imageStartOffset;
	bmpHeaderComponents->_width = toCopy.bmpHeaderComponents->_width;
	bmpHeaderComponents->_height = toCopy.bmpHeaderComponents->_height;
	bmpHeaderComponents->_bitsPerPixel = toCopy.bmpHeaderComponents->_bitsPerPixel;
	bmpHeaderComponents->_compression = toCopy.bmpHeaderComponents->_compression;
	bmpHeaderComponents->_verticalResolution = toCopy.bmpHeaderComponents->_verticalResolution;
	bmpHeaderComponents->_horizontalResolution = toCopy.bmpHeaderComponents->_horizontalResolution;

	return *this;
}



bool BmpHeaderInfo::isEqual(const BmpHeaderInfo& toCompare)
{
	//TODO
	return false;
}


uint32_t BmpHeaderInfo::GetWidth() const
{
	return bmpHeaderComponents->_width;
}



uint32_t BmpHeaderInfo::GetHeight() const
{
	return bmpHeaderComponents->_height;
}



uint32_t BmpHeaderInfo::GetCompression() const
{
	return bmpHeaderComponents->_compression;
}



uint32_t BmpHeaderInfo::GetBitsPerPixel() const
{
	return bmpHeaderComponents->_bitsPerPixel;
}



uint32_t BmpHeaderInfo::GetImageStartOffset() const
{
	return bmpHeaderComponents->_imageStartOffset;
}



std::vector<unsigned char> BmpHeaderInfo::GetRawHeader() const
{
	return rawData;
}




void BmpHeaderInfo::SetHeight(int newHeight)
{
	//set bmpHeaderComponents and rawData
	BmpConstants con;
	bmpHeaderComponents->_height = newHeight;
    HeaderRawImageDataSetterFromIntegerHelper(newHeight, con.HEIGHT, con.HEIGHT+4, rawData);
	
}



void BmpHeaderInfo::SetWidth(int newWidth)
{
	//set bmpHeaderComponents and rawData
	BmpConstants con;

	bmpHeaderComponents->_width = newWidth;
	HeaderRawImageDataSetterFromIntegerHelper(newWidth, con.WIDTH, con.WIDTH + 4, rawData);
}
