#include "Pixelate.h"

Pixelate::Pixelate()
{
	squareLen = 16;
	xEdgeRemainder = 0;
	yEdgeRemainder = 0;

	SetEdgeRemainders();
}



//Set edge remainders if there are incomplete squarelen boxes on the edges of the picture
void Pixelate::SetEdgeRemainders()
{
	auto hdr = GetHeader();
	xEdgeRemainder = hdr->GetWidth() % 16;
	yEdgeRemainder = hdr->GetHeight() % 16;
}



std::vector<Pixel> Pixelate::TransformPixels(std::vector<Pixel> pixels)
{
	
	auto hdr = GetHeader();
	if (!hdr) {
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS(): FAILED TO SET HEADER");
	}

	if (hdr->GetWidth() < 16 || hdr->GetHeight() < 16)
	{
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS() : WIDTH || HEIGHT TOO SMALL");
	}
	



	uint32_t Width = hdr->GetWidth();
	uint32_t Height = hdr->GetHeight();

	uint8_t xFullSquares = Width / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t yFullSquares = Height / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t xRemainder = Width % 16;				//Remainder values if 16x16 doesn't fit perfectly
	uint8_t yRemainder = Height % 16;
	uint8_t boundCheckerX = 0;
	uint8_t boundCheckerY = 0;

	
	//Pixelates 16x16 blocks, + remainder blocks
	for (uint32_t x = 0; x < (Width); x += to_addX)
	{
		for (uint32_t y = 0; y < (Height); y += to_addY)
		{
			if (xRemainder > 0)
			{
				if (boundCheckerY == (yFull16Additions))	//If we have reached the amount of full 16x16 blocks
					to_addY = (yRemainder);					//then pixelate the remainder pixels
			}
			average16RGB(x, y, to_addX, to_addY);	//Averages the RGB values within given bounds, saves pixel data
			boundCheckerY++;
		}

		boundCheckerY = 0;
		to_addY = 16;
		boundCheckerX++;

		if (xRemainder > 0)
		{
			if (boundCheckerX == (xFull16Additions))
				to_addX = (xRemainder);
		}
	}
	
	return pixels;
}



//Takes a starting coordinate within the image and sums a squares worth of pixels together, takes average of that sum
//and sets all pixels within that square to that average value
void Pixelate::Average16RGB(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> startCoordinate, std::pair<int, int> sideLengths) {
	
	//TODO
	//CHECK IF COORDINATES ARE WITHIN RANGE OF PIXEL  VECTOR
	//MIGHT NEED BOTH X AND Y LENGTHS AS SEPARATE VARIABLES


	auto hdr = GetHeader();
	int sideLength_x = sideLengths.first;
	int sideLength_y = sideLengths.second;

	//build dummy tmp pixel
	auto channelCount = pixels[0].GetChannelCount();
	std::vector<unsigned char> channelValues(channelCount, 0);
	Pixel sumOfBoxOfPixels(channelValues, channelCount);

	//Get iterators
	auto boxIterators = GetIteratorsOfPixelBox(pixels, startCoordinate, sideLength_y);

	//Sum up all channel values in the box
	for (auto& iter : boxIterators)
	{
		sumOfBoxOfPixels = sumOfBoxOfPixels + GetRowPixelAdditionReduction(iter, sumOfBoxOfPixels, sideLength_x); //tmpPixel by value, returns integer
	}

	//Divide pixel values by pixel box length
	AveragePixelValuesByBoxDimensions(sumOfBoxOfPixels, squareLen);

	//Rewrite pixel values within box to reflect the new values
	SetPixelBoxToAverage(boxIterators, sumOfBoxOfPixels);
}




//Returns a vector of iterators that are the start of each row for the current box
std::vector<std::vector<Pixel>::iterator> Pixelate::GetIteratorsOfPixelBox(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> boxCoordinate, int sideLength_y)
{

	std::vector<std::vector<Pixel>::iterator> boxIterators;
	std::vector<Pixel>::iterator rowIterator;
	for (int row = 0; row < sideLength_y; ++row) //row of box
	{
		//This iterator is where the row begins
		rowIterator = pixels.begin() + GetBoxIteratorStartIdx(boxCoordinate, row);

		boxIterators.push_back(rowIterator);
	}
}



//Return the start of row where the iterator will begin, call for each row within box
uint32_t Pixelate::GetBoxIteratorStartIdx(std::pair<uint32_t, uint32_t> boxCoordinate, int row)
{
	auto curBox_X = boxCoordinate.first;
	auto curBox_Y = boxCoordinate.second;
	auto hdr = GetHeader();
	return (curBox_X * squareLen) + (((curBox_Y * squareLen) + row) * hdr->GetWidth());
}




//Add up all of the pixels within the row for squareLen and return it
//Leave as pass by value so that multiple instances can be run simultaneously
Pixel Pixelate::GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, Pixel sumPixel, int sideLength_x)
{
	std::for_each(rowIterator, std::next(rowIterator, sideLength_x),
		[&]() {sumPixel = sumPixel + *rowIterator; });

	return sumPixel;
}



//Average the pixel value by squareLen for the temporary holder pixel
void Pixelate::AveragePixelValuesByBoxDimensions(Pixel& sumOfBoxOfPixels, std::pair<int, int> sideLengths)
{
	int sideLength_x = sideLengths.first;
	int sideLength_y = sideLengths.second;

	auto pixelValues = sumOfBoxOfPixels.GetAllChannelData();
	int averageOfChannel = 0;
	for (int channelIdx = 0; channelIdx < sumOfBoxOfPixels.GetChannelCount(); ++channelIdx)
	{
		averageOfChannel = pixelValues[channelIdx] / (sideLengths.first * sideLengths.second);
		sumOfBoxOfPixels.SetChannel(channelIdx, averageOfChannel);
	}
}



void Pixelate::SetPixelBoxToAverage(std::vector<std::vector<Pixel>::iterator> boxIterators, Pixel& toCopy, int sideLength_x)
{
	for (auto& iter : boxIterators)
	{
		SetRowOfSqaureLenToAverage(iter, toCopy, sideLength_x);
	}
}



void Pixelate::SetRowOfSqaureLenToAverage(std::vector<Pixel>::iterator rowIterator, Pixel& toCopy, int sideLength_x)
{
	std::for_each(rowIterator, std::next(rowIterator, sideLength_x),
		[&]() {*rowIterator = toCopy; });
}



std::unique_ptr<HeaderInfo> Pixelate::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//NO OP
	return std::move(hdr);
}

