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
	void SetEdgeRemainders();
	void AveragePixelValuesByBoxDimensions(Pixel& sumOfBoxOfPixels, std::pair<int, int> sideLengths);
	void SetRowOfSqaureLenToAverage(std::vector<Pixel>::iterator rowIterator, Pixel& toCopy, int squareLen);
	void SetPixelBoxToAverage(std::vector<std::vector<Pixel>::iterator> boxIterators, Pixel& toCopy, int sideLength_x);
	std::vector<std::vector<Pixel>::iterator> GetIteratorsOfPixelBox(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> boxCoordinate, int squareLen);
	uint32_t GetBoxIteratorStartIdx(std::pair<uint32_t, uint32_t> boxCoordinate, int row);
	Pixel GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, Pixel sumPixel, int sideLength_x);
	void Average16RGB(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> startCoordinate, std::pair<int, int> sideLengths);
	
	int squareLen;
	int xEdgeRemainder;
	int yEdgeRemainder;
};