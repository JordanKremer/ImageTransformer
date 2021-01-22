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
	std::vector<int> AveragePixelValuesBySquareDimensions(std::vector<int> sumOfRowOfChannelValues, int totalPixels);
	void SetRowOfSquareLenToAverage(std::vector<Pixel>::iterator rowIterator, std::vector<int> averagePixelChannelValues, int squareLen);
	void SetPixelSquareToAverage(std::vector<std::vector<Pixel>::iterator> boxIterators, std::vector<int> averagePixelChannelValues, int sideLength_x);
	std::vector<std::vector<Pixel>::iterator> GetIteratorsOfPixelSquare(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, int sideLength_y);
	uint32_t GetSquareIteratorStartIdx(std::pair<int, int> curSquareCoordinate, int row);
	std::vector<int> GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, std::vector<int> sumOfRowOfChannelValues, int sideLength_x);
	std::vector<int> GetRowPixelAdditionReductionHelper(std::vector<int> sumOfRowOfChannelValues, Pixel pixel);
	
	std::vector<Pixel> Average16RGB(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, std::pair<int, int> sideLengths);
	

	int _squareLen;
	int _xEdgeRemainder;
	int _yEdgeRemainder;
};