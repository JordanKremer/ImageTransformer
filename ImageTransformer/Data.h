/*
Author : Jordan Kremer
11/20/20
Data.h

Data is a container for the HeaderInfo data and pixel vector. This Data object is intended
to interact with Transformation objects. This class is intended as read only.

*/

#pragma once
#include <vector>
#include <memory>
#include "HeaderInfo.h"
#include "BmpHeaderInfo.h"
#include "Pixel.h"

class Data
{
public:
	Data();
	Data(std::vector<unsigned char> &data, std::vector<Pixel>& pixels, const HeaderInfo* header);
	~Data(); //if change _header to unique, no need for destructor

	_NODISCARD const int GetCompression();
	const std::vector<unsigned char> GetHeader() const;
	const std::vector<Pixel> GetPixels() const;

private:
	HeaderInfo* _header; //Unique_ptr won't work here
	std::vector<Pixel> _pixels;

};

