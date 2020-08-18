#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

struct Constants {
	inline static const std::string COMPRESSION = "compression";
	inline static const std::string WIDTH = "width";
	inline static const std::string HEIGHT = "height";
};



class BmpHeaderInfo
{
public:

	virtual int getCompression() = 0; //do we want the return type to be const?
	virtual std::vector<unsigned char>::const_iterator getHeaderBegin() = 0;
	virtual std::vector<unsigned char>::const_iterator getHeaderEnd() = 0;

	virtual int getWidth() = 0;
	//virtual unsigned char getHeaderByte(int headerIndex) = 0;
	//= operator = 0
	//>> operator (ifstream& in) = 0
	//const int getWidth() = 0;


	//page 75 modern effective c++
	//USE DELETE after the function declaration if don't want an implicit function to made for, say, the
	//= operator, etc
	//operator&=(BmpHeaderInfo&) = delete;

};

