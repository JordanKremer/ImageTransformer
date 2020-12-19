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
	friend class Transformation; //grant access to pixel data to transformation class
	friend class Rotate180;
public:
	Data();
	Data(std::vector<unsigned char> &data, std::vector<Pixel>& pixels, std::unique_ptr<HeaderInfo> header);
	~Data(); //if change _header to unique, no need for destructor

	_NODISCARD const int GetCompression();
	const std::vector<unsigned char> GetRawHeaderReadOnly() const;
	const std::vector<Pixel> GetPixelsReadOnly() const;

private:
	std::unique_ptr<HeaderInfo> _header; //Unique_ptr won't work here
	std::vector<Pixel> _pixels;

};

