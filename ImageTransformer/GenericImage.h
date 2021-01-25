/*
Author : Jordan Kremer
11/20/20
GenericImage.h

GenericImage is a container for the HeaderInfo data and pixel vector. This GenericImage object is intended
to interact with Transformation objects. This class is intended as read only.

*/

#pragma once
#include <vector>
#include <memory>
#include "HeaderInfo.h"
#include "BmpHeaderInfo.h"
#include "Pixel.h"

class GenericImage
{
	friend class Applicator; 
	//The reason to use friend is so that applicator can have access to the data without 
	//giving the data away to just anyone who asks, and can then apply it to a transformation

public:
	GenericImage(std::vector<unsigned char> &data, std::vector<Pixel>& pixels, std::unique_ptr<HeaderInfo> header);
	~GenericImage();

	_NODISCARD const int GetCompression();
	_NODISCARD const std::vector<unsigned char> GetRawHeaderReadOnly() const;
	_NODISCARD const std::vector<Pixel> GetPixelsReadOnly() const;

private:
	
	std::unique_ptr<HeaderInfo> _header;
	std::vector<Pixel> _pixels;

};
