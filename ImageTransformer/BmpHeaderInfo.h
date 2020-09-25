#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "HeaderInfo.h"
//BITMAPHEADERINFO 
//OS/2 no longer supported, so Windows BITMAPHEADERINFO table used
struct BmpConstants {
	inline static const int ID = 0;
	inline static const int FILESIZE = 2;
	inline static const int RESERVED1 = 6;
	inline static const int IMAGESTARTOFFSET = 10;
	inline static const int HEADERSIZE = 14;
	inline static const int WIDTH = 18;
	inline static const int HEIGHT = 22;
	inline static const int COLORPANES = 26;
	inline static const int BITSPERPIXEL = 28;
	inline static const int COMPRESSION = 30; //values 0 - 13
	inline static const int IMAGESIZE = 34;
	inline static const int HORIZONTALRESOLUTION = 38;
	inline static const int VERTICALRESOLUTION = 42;
	inline static const int NUMCOLORSINPALETTE = 46;
	inline static const int NUMIMPORTANTCOLORSUSED = 50;
};



struct BasicBmpHeaderComponents{
	std::string _ID;
	int _filesize;
	int _width;
	int _height;
	int _compression;
	int _horizontalResolution;
	int _verticalResolution;
};



class BmpHeaderInfo : public HeaderInfo
{
public:

	BmpHeaderInfo();
	BmpHeaderInfo(const BmpHeaderInfo& toCopy);
	
	void operator=(const HeaderInfo& toCopy);

	_NODISCARD virtual  int getCompression() const = 0; //do we want the return type to be const?
	_NODISCARD virtual std::vector<unsigned char>::const_iterator getHeaderBegin() = 0;
	_NODISCARD virtual std::vector<unsigned char>::const_iterator getHeaderEnd() = 0;

	int getWidth();

	


	//virtual unsigned char getHeaderByte(int headerIndex) = 0;
	//= operator = 0
	//>> operator (ifstream& in) = 0
	//const int getWidth() = 0;


	//page 75 modern effective c++
	//USE DELETE after the function declaration if don't want an implicit function to made for, say, the
	//= operator, etc
	//operator&=(BmpHeaderInfo&) = delete;
private:
	std::shared_ptr<BasicBmpHeaderComponents> bmpHeaderComponents;

};


//https://dzone.com/articles/the-pimpl-pattern-what-you-should-know
//https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/