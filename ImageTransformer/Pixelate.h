#pragma once
#include "Transformation.h"
class Pixelate :
	public Transformation
{
public:
	Pixelate();
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);
	
private:
//	std::vector<std::vector<Pixel>::iterator> GetIteratorsOfPixelBox(std::vector<Pixel> pixels, int curBox_X, int curBox_Y);
//	uint32_t GetBoxIteratorOffset(int curBox_X, int curBox_Y, int row, int width);

	//Pixel Average16RGB(const HeaderInfo* hdr, std::vector<Pixel> pixels, uint32_t x, uint32_t y, uint8_t xBoundAddition, uint8_t yBoundAddition);
	int squareLen;
};