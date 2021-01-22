#include "Pixelate.h"

Pixelate::Pixelate()
{
	_squareLen = 16;
	_xEdgeRemainder = 0;
	_yEdgeRemainder = 0;



}



//Set edge remainders if there are incomplete squarelen Squarees on the edges of the picture
void Pixelate::SetEdgeRemainders()
{
	auto hdr = GetHeader();
	_xEdgeRemainder = hdr->GetWidth() % 16;
	_yEdgeRemainder = hdr->GetHeight() % 16;
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
	
	SetEdgeRemainders();

	uint32_t Width = hdr->GetWidth();
	uint32_t Height = hdr->GetHeight();

	uint8_t xFullSquares = Width / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t yFullSquares = Height / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t xRemainder = Width % 16;				//Remainder values if 16x16 doesn't fit perfectly
	uint8_t yRemainder = Height % 16;

	//								X (col)   ,    Y(row)
	std::pair<int, int> sideLengths(_squareLen, _squareLen);
	std::pair<int, int> sideLengthsWithRemainderX(_squareLen + xRemainder, _squareLen);
	std::pair<int, int> sideLengthsWithRemainderY(_squareLen, _squareLen + yRemainder);
	std::pair<int, int> sideLengthsWithBothRemainders(_squareLen + xRemainder, _squareLen + yRemainder);


	//NOTE : yFullSquares are rows, xFullSquares are columns, make sure to check that all functions adhere to this
	//As well, make sure to follow curSquareCoordinate . first/second through to ensure 


	//Pixelates 16x16 blocks, + remainder blocks

	//Pass to Average16RGB as [col][row] which is the same as [x][y]

	std::pair<int, int> curSquareCoordinate;

	//rows
	for (int yCurSquare = 0; yCurSquare < yFullSquares; ++yCurSquare)
	{
		//columns
		for (int xCurSquare = 0; xCurSquare < xFullSquares; ++xCurSquare)  
		{
			curSquareCoordinate.first = xCurSquare;
			curSquareCoordinate.second = yCurSquare;

			//Account for all of the scenarios
			//if we are on our last full x (col) square but not our last full y (row) square within a column
			if ((xCurSquare == xFullSquares - 1) && (yCurSquare < (yFullSquares - 1)))
			{
				pixels = Average16RGB(pixels, curSquareCoordinate, sideLengthsWithRemainderX);
			}
			//if we are on our last full y (row) square but not our last full x (col) square within a column
			else if ((xCurSquare == xFullSquares - 1) && (yCurSquare < (yFullSquares - 1)))
			{
				pixels = Average16RGB(pixels, curSquareCoordinate, sideLengthsWithRemainderY);
			}
			//if we are on our last full x (col) square and our last full y (row) square --> corner case
			else if ((xCurSquare == (xFullSquares - 1)) && (yCurSquare == (yFullSquares - 1)))
			{
				pixels = Average16RGB(pixels, curSquareCoordinate, sideLengthsWithBothRemainders);
			}
			//Default case, where the current square is not on an edge
			else {
				pixels = Average16RGB(pixels, curSquareCoordinate, sideLengths);
			}
		}
	}

	return pixels;
}



//Takes a starting coordinate within the image and sums a squares worth of pixels together, takes average of that sum
//and sets all pixels within that square to that average value
std::vector<Pixel> Pixelate::Average16RGB(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, std::pair<int, int> sideLengths) 
{
	auto hdr = GetHeader();
	int sideLength_x = sideLengths.first;  //columns
	int sideLength_y = sideLengths.second; //rows

	//build dummy tmp pixel
	auto channelCount = pixels[0].GetChannelCount();
	std::vector<unsigned char> channelValues(channelCount, 0);
	std::unique_ptr<Pixel> sumOfSquareOfPixels =  std::make_unique<Pixel>(channelValues, channelCount);

	//Get iterators
	//auto squareIterators = GetIteratorsOfPixelSquare(pixels, curSquareCoordinate, sideLength_y);
	std::vector<std::vector<Pixel>::iterator> squareIterators;
	std::vector<Pixel>::iterator yIterator;
	for (int y = 0; y < sideLength_y; ++y) //row of Square
	{
		//This iterator is where the row begins
		yIterator = pixels.begin() + GetSquareIteratorStartIdx(curSquareCoordinate, y);

		squareIterators.push_back(yIterator);
	}


	Pixel tmp;
	//Sum up all channel values in the Square
	for (auto& iter : squareIterators)
	{
		tmp = *sumOfSquareOfPixels;
		sumOfSquareOfPixels = GetRowPixelAdditionReduction(iter, std::move(sumOfSquareOfPixels), sideLength_x);
		*sumOfSquareOfPixels = *sumOfSquareOfPixels + tmp;
	}

	//Divide pixel values by total pixels
	int totalPixels = sideLength_x * sideLength_y;
	auto averagePixel = AveragePixelValuesBySquareDimensions(std::move(sumOfSquareOfPixels), totalPixels);

	//Rewrite pixel values within Square to reflect the new values
	SetPixelSquareToAverage(squareIterators, averagePixel.get(), sideLength_x);

	return pixels;
}




//Returns a vector of iterators that are the start of each row for the current Square
std::vector<std::vector<Pixel>::iterator> Pixelate::GetIteratorsOfPixelSquare(std::vector<Pixel> pixels, std::pair<int, int> curSquareCoordinate, int sideLength_y)
{
	std::vector<std::vector<Pixel>::iterator> squareIterators;
	std::vector<Pixel>::iterator yIterator;
	for (int y = 0; y < sideLength_y; ++y) //row of Square
	{
		//This iterator is where the row begins
		yIterator = pixels.begin() + GetSquareIteratorStartIdx(curSquareCoordinate, y);

		squareIterators.push_back(yIterator);
	}
	
	return squareIterators;
}




//Return the start of row where the iterator will begin, call for each row within Square
uint32_t Pixelate::GetSquareIteratorStartIdx(std::pair<int, int> curSquareCoordinate, int y)
{
	auto curSquare_X = curSquareCoordinate.first;
	auto curSquare_Y = curSquareCoordinate.second;
	auto hdr = GetHeader();
	return (curSquare_X * _squareLen) + (((curSquare_Y * _squareLen) + y) * hdr->GetWidth());
}




//Add up all of the pixels within the row for _squareLen and return it
//Leave as pass by value so that multiple instances can be run simultaneously
std::unique_ptr<Pixel> Pixelate::GetRowPixelAdditionReduction(std::vector<Pixel>::iterator yIterator, std::unique_ptr<Pixel> sumPixel, int sideLength_x)
{
	//Initially intended to use for_each as such:
	//std::for_each(yIterator, std::next(yIterator, sideLength_x),
	//	[&]() {sumPixel = sumPixel + *yIterator; });

	for (int x = 0; x < sideLength_x; ++x)
	{
		*sumPixel = *sumPixel + *yIterator;
		yIterator++;
	}

	return std::move(sumPixel);
}



//Average the pixel value by _squareLen for the temporary holder pixel
std::unique_ptr<Pixel> Pixelate::AveragePixelValuesBySquareDimensions(std::unique_ptr<Pixel> sumOfSquareOfPixels, int totalPixels)
{
	auto pixelValues = sumOfSquareOfPixels->GetAllChannelData();
	int averageOfChannel = 0;
	for (int channelIdx = 0; channelIdx < sumOfSquareOfPixels->GetChannelCount(); ++channelIdx)
	{
		averageOfChannel = pixelValues[channelIdx] / (totalPixels);
		sumOfSquareOfPixels->SetChannel(channelIdx, averageOfChannel);
	}

	return std::move(sumOfSquareOfPixels);
}



//For each pixel within the Square, set that pixel equal to toCopy, the average pixel
void Pixelate::SetPixelSquareToAverage(std::vector<std::vector<Pixel>::iterator> squareIterators, const Pixel* toCopy, int sideLength_x)
{
	for (auto& iter : squareIterators)
	{
		SetRowOfSqaureLenToAverage(iter, toCopy, sideLength_x);
	}
}



void Pixelate::SetRowOfSqaureLenToAverage(std::vector<Pixel>::iterator yIterator, const Pixel* toCopy, int sideLength_x)
{
	//std::for_each(yIterator, std::next(yIterator, sideLength_x),
	//	[&]() {*yIterator = toCopy; });

	for (int x = 0; x < sideLength_x; ++x)
	{
		*yIterator = *toCopy;
		yIterator++;
	}
}



std::unique_ptr<HeaderInfo> Pixelate::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//NO OP
	return std::move(hdr);
}

