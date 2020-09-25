#include "BmpHeaderInfo.h"

BmpHeaderInfo::BmpHeaderInfo()
{
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

