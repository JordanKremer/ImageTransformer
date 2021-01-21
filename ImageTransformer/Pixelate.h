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
	void AveragePixelValuesBySquareDimensions(Pixel& sumOfBoxOfPixels, int totalPixels);
	void SetRowOfSqaureLenToAverage(std::vector<Pixel>::iterator rowIterator, Pixel& toCopy, int squareLen);
	void SetPixelSquareToAverage(std::vector<std::vector<Pixel>::iterator> boxIterators, Pixel& toCopy, int sideLength_x);
	std::vector<std::vector<Pixel>::iterator> GetIteratorsOfPixelSquare(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, int sideLength_y);
	uint32_t GetSquareIteratorStartIdx(std::pair<int, int> curSquareCoordinate, int row);
	Pixel GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, Pixel sumPixel, int sideLength_x);
	std::vector<Pixel> Average16RGB(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, std::pair<int, int> sideLengths);
	
	int _squareLen;
	int _xEdgeRemainder;
	int _yEdgeRemainder;
};