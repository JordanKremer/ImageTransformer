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
	std::vector<std::vector<Pixel>::iterator> GetIteratorsOfPixelBox(std::vector<Pixel> pixels, int curBox_X, int curBox_Y);
	uint32_t GetBoxIteratorStartIdx(int curBox_X, int curBox_Y, int row);
	Pixel GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, Pixel sumPixel);
	Pixel Average16RGB(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> startCoordinate);
	int squareLen;
};