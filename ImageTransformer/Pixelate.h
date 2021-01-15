#pragma once
#include "Transformation.h"
class Pixelate :
	public Transformation
{
public:
	Pixelate();
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header);

private:
	Pixel Average16RGB(const HeaderInfo* hdr, std::vector<Pixel> pixels, uint32_t x, uint32_t y, uint8_t xBoundAddition, uint8_t yBoundAddition);
	int squareLen;

};