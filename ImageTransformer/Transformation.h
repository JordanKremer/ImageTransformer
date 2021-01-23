/*
Author : Jordan Kremer
11/20/20
Transformation.h

This class is an interface class wherein Transformation subclasses such
as Gaussian blur and Pixelate will derive from.
*/

#pragma once
#include "Pixel.h"
#include "HeaderInfo.h"
#include <memory>
#include <map>
#include <exception>
#include <algorithm>

class Transformation
{
	friend class Applicator;

public:
	virtual std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels) = 0;
	virtual std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr) = 0;
	void SetHeader(const HeaderInfo* toSet) { _hdr = toSet; }
	const HeaderInfo* GetHeader() { return _hdr; };

	inline Pixel& GetPixelAtCoordinate(std::vector<Pixel> pixels, int x, int y)
	{
		uint32_t Width = _hdr->GetWidth();
		uint32_t pixelIdx = Width * y + x;

		return pixels[pixelIdx];
	}

	inline void SetPixelAtCoordinate()
	{
		//TODO
	}

private:
	const HeaderInfo* _hdr;

};

