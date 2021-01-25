/*
Author : Jordan Kremer
11/20/2020
BmpHeaderInfo.h

Includes functionality for BmpHeaderInfo class, including getters for BmpHeader constants
such as width and height of the image. Includes clone().

*/

#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "HeaderInfo.h"


//BITMAPHEADERINFO 
//OS/2 no longer supported, so Windows BITMAPHEADERINFO table used as reference
struct BmpConstants {
	inline static const int ID = 0;
	inline static const int FILE_SIZE = 2;
	inline static const int RESERVED1 = 6;
	inline static const int IMAGE_START_OFFSET = 10;
	inline static const int HEADER_SIZE = 14;
	inline static const int WIDTH = 18;
	inline static const int HEIGHT = 22;
	inline static const int COLOR_PANES = 26;
	inline static const int BITS_PER_PIXEL = 28;
	inline static const int COMPRESSION = 30; //values 0 - 3
	inline static const int IMAGE_SIZE = 34;
	inline static const int HORIZONTAL_RESOLUTION = 38;
	inline static const int VERTICAL_RESOLUTION = 42;
	inline static const int NUM_COLORS_IN_PALETTE = 46;
	inline static const int NUM_IMPORTANT_COLORS_USED = 50;
};


//Container for easier access
struct BasicBmpHeaderComponents{
	std::string _ID;
	uint32_t _filesize;
	uint32_t _imageStartOffset;
	uint32_t _width;
	uint32_t _height;
	uint32_t _bitsPerPixel;
	uint32_t _compression;
	uint32_t _horizontalResolution;
	uint32_t _verticalResolution;
	
};



class BmpHeaderInfo : public HeaderInfo
{
public:

	BmpHeaderInfo();
	BmpHeaderInfo(const std::vector<unsigned char>& data);
	BmpHeaderInfo(const BmpHeaderInfo& toCopy);
	BmpHeaderInfo& operator =(const BmpHeaderInfo& toCopy);
	bool isEqual(const BmpHeaderInfo& toCompare);

	_NODISCARD uint32_t GetWidth() const; 
	_NODISCARD uint32_t GetHeight() const;
	_NODISCARD uint32_t GetCompression() const; 
	_NODISCARD uint32_t GetBitsPerPixel() const;
	//Gets the start of the (RGBA) image bytes within a byte vector after the header bytes
	_NODISCARD uint32_t GetImageStartOffset() const;
	_NODISCARD std::vector<unsigned char> GetRawHeader() const;


	void SetHeight(int newHeight);
	void SetWidth(int newWidth);

	uint32_t HeaderComponentsConstructorHelper(const int bmpConstantStart, const int bmpConstantEnd, const std::vector<unsigned char>& data);
	void HeaderRawImageDataSetterFromIntegerHelper(uint32_t dataToChangeTo, const int bmpConstantStart, const int bmpConstantEnd, std::vector<unsigned char>& rawData);
	
private:
	std::shared_ptr<BasicBmpHeaderComponents> bmpHeaderComponents;
	std::vector<unsigned char> rawData;
};
