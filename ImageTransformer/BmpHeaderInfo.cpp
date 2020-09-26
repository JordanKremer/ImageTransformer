#include "BmpHeaderInfo.h"

BmpHeaderInfo::BmpHeaderInfo()
{
}

BmpHeaderInfo::BmpHeaderInfo(const std::vector<unsigned char>& data)
{
	//bmpHeaderComponents->_ID = 
	BmpConstants bmpConstants;

	bmpHeaderComponents->_filesize = headerComponentsConstructorHelper(bmpConstants.FILESIZE, bmpConstants.RESERVED1, data);
	bmpHeaderComponents->_width = headerComponentsConstructorHelper(bmpConstants.WIDTH, bmpConstants.HEIGHT, data);
	bmpHeaderComponents->_height = headerComponentsConstructorHelper(bmpConstants.HEIGHT, bmpConstants.COLORPANES, data);
	bmpHeaderComponents->_compression = headerComponentsConstructorHelper(bmpConstants.COMPRESSION, bmpConstants.IMAGESIZE, data);
	bmpHeaderComponents->_horizontalResolution = headerComponentsConstructorHelper(bmpConstants.HORIZONTALRESOLUTION, bmpConstants.VERTICALRESOLUTION, data);
	bmpHeaderComponents->_verticalResolution = headerComponentsConstructorHelper(bmpConstants.VERTICALRESOLUTION, bmpConstants.NUMCOLORSINPALETTE, data);

}

uint32_t BmpHeaderInfo::headerComponentsConstructorHelper(const int bmpConstantStart, const int bmpConstantEnd, const std::vector<unsigned char>& data)
{
	uint32_t tmpCharToIntConversion;
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
	bmpHeaderComponents->_width = toCopy.bmpHeaderComponents->_width;
	bmpHeaderComponents->_height = toCopy.bmpHeaderComponents->_height;
	bmpHeaderComponents->_compression = toCopy.bmpHeaderComponents->_compression;
	bmpHeaderComponents->_verticalResolution = toCopy.bmpHeaderComponents->_verticalResolution;
	bmpHeaderComponents->_horizontalResolution = toCopy.bmpHeaderComponents->_horizontalResolution;

}

void BmpHeaderInfo::operator=(const HeaderInfo& toCopy)
{
	
}

