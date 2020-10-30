#include "BmpHeaderInfo.h"
#include <stdexcept>
//#include <string>

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

BmpHeaderInfo::BmpHeaderInfo(const std::vector<unsigned char>& data)
{
	
	if (data.size() < 54) {
		std::string msg = "ERROR: HEADER DATA IS TOO SMALL:: SIZE: " + data.size();
		throw std::length_error(msg);
	}


	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();
	BmpConstants bmpConstants;

	bmpHeaderComponents->_filesize = headerComponentsConstructorHelper(bmpConstants.FILESIZE, bmpConstants.RESERVED1, data);
	bmpHeaderComponents->_imageStartOffset = headerComponentsConstructorHelper(bmpConstants.IMAGESTARTOFFSET, bmpConstants.HEADERSIZE, data);
	bmpHeaderComponents->_width = headerComponentsConstructorHelper(bmpConstants.WIDTH, bmpConstants.HEIGHT, data);
	bmpHeaderComponents->_height = headerComponentsConstructorHelper(bmpConstants.HEIGHT, bmpConstants.COLORPANES, data);
	bmpHeaderComponents->_bitsPerPixel = headerComponentsConstructorHelper(bmpConstants.BITSPERPIXEL, bmpConstants.COMPRESSION, data);
	bmpHeaderComponents->_compression = headerComponentsConstructorHelper(bmpConstants.COMPRESSION, bmpConstants.IMAGESIZE, data);
	bmpHeaderComponents->_horizontalResolution = headerComponentsConstructorHelper(bmpConstants.HORIZONTALRESOLUTION, bmpConstants.VERTICALRESOLUTION, data);
	bmpHeaderComponents->_verticalResolution = headerComponentsConstructorHelper(bmpConstants.VERTICALRESOLUTION, bmpConstants.NUMCOLORSINPALETTE, data);

}

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



BmpHeaderInfo::BmpHeaderInfo(const BmpHeaderInfo& toCopy)
{
	bmpHeaderComponents = std::make_shared<BasicBmpHeaderComponents>();
	//bmpHeaderComponents = toCopy.bmpHeaderComponents; //not sure if each of these are being copied
	bmpHeaderComponents->_ID = toCopy.bmpHeaderComponents->_ID;
	bmpHeaderComponents->_filesize = toCopy.bmpHeaderComponents->_filesize;
	bmpHeaderComponents->_imageStartOffset = toCopy.bmpHeaderComponents->_imageStartOffset;
	bmpHeaderComponents->_width = toCopy.bmpHeaderComponents->_width;
	bmpHeaderComponents->_height = toCopy.bmpHeaderComponents->_height;
	bmpHeaderComponents->_bitsPerPixel = toCopy.bmpHeaderComponents->_bitsPerPixel;
	bmpHeaderComponents->_compression = toCopy.bmpHeaderComponents->_compression;
	bmpHeaderComponents->_verticalResolution = toCopy.bmpHeaderComponents->_verticalResolution;
	bmpHeaderComponents->_horizontalResolution = toCopy.bmpHeaderComponents->_horizontalResolution;

}

HeaderInfo* BmpHeaderInfo::Clone() const
{
	return new BmpHeaderInfo(*this);
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
	return false;
}


const uint32_t BmpHeaderInfo::GetWidth() const
{
	return bmpHeaderComponents->_width;
}


const uint32_t BmpHeaderInfo::GetHeight() const
{
	return bmpHeaderComponents->_height;
}

const uint32_t BmpHeaderInfo::GetCompression() const
{
	return bmpHeaderComponents->_compression;
}

const uint32_t BmpHeaderInfo::GetBitsPerPixel() const
{
	return bmpHeaderComponents->_bitsPerPixel;
}


const uint32_t BmpHeaderInfo::GetImageStartOffset() const
{
	return bmpHeaderComponents->_imageStartOffset;
}