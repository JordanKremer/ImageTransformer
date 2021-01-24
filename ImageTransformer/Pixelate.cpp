/*
MIT License

Copyright(c) 2021 Jordan Kremer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


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
	int sideLength_x = sideLengths.first;  //columns
	int sideLength_y = sideLengths.second; //rows


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


	std::vector<int> sumOfRowOfChannelValues(pixels[0].GetChannelCount(), 0);

	for (auto& rowIter : squareIterators)
	{
		sumOfRowOfChannelValues = GetRowPixelAdditionReduction(rowIter, sumOfRowOfChannelValues, sideLength_x);
	}



	//Divide pixel values by total pixels
	int totalPixels = sideLength_x * sideLength_y;
	auto averagePixelChannelValues = AveragePixelValuesBySquareDimensions(sumOfRowOfChannelValues, totalPixels);

	//Rewrite pixel values within Square to reflect the new values
	SetPixelSquareToAverage(squareIterators, averagePixelChannelValues, sideLength_x);

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
std::vector<int> Pixelate::GetRowPixelAdditionReduction(std::vector<Pixel>::iterator yIterator, std::vector<int> sumOfRowOfChannelValues, int sideLength_x)
{
	//Initially intended to use for_each as such:
	//std::for_each(yIterator, std::next(yIterator, sideLength_x),
	//	[&]() {sumPixel = sumPixel + *yIterator; });

	for (int x = 0; x < sideLength_x; ++x)
	{
		sumOfRowOfChannelValues = GetRowPixelAdditionReductionHelper(sumOfRowOfChannelValues, *yIterator);
		yIterator++;
	}

	return sumOfRowOfChannelValues;
}



std::vector<int> Pixelate::GetRowPixelAdditionReductionHelper(std::vector<int> sumOfRowOfChannelValues, Pixel pixel)
{
	int channelCount = sumOfRowOfChannelValues.size();
	if (pixel.GetChannelCount() != channelCount)
		throw std::runtime_error("ERROR | PIXELATE::GETROWPIXELADDITIONREDUCTIONHELPER()");
	
	for (int channelIdx = 0; channelIdx < channelCount; ++channelIdx)
	{
		sumOfRowOfChannelValues[channelIdx] += pixel.GetChannel(channelIdx);
	}

	return sumOfRowOfChannelValues;
}



//Average the pixel value by _squareLen for the temporary holder pixel
std::vector<int> Pixelate::AveragePixelValuesBySquareDimensions(std::vector<int> sumOfRowOfChannelValues, int totalPixels)
{
	int averageOfChannel = 0;
	for (int channelIdx = 0; channelIdx < sumOfRowOfChannelValues.size(); ++channelIdx)
	{
		sumOfRowOfChannelValues[channelIdx] /= totalPixels;
	}

	return sumOfRowOfChannelValues;
}



//For each pixel within the Square, set that pixel equal to toCopy, the average pixel
void Pixelate::SetPixelSquareToAverage(std::vector<std::vector<Pixel>::iterator> squareIterators, std::vector<int> averagePixelChannelValues, int sideLength_x)
{
	for (auto& iter : squareIterators)
	{
		SetRowOfSquareLenToAverage(iter, averagePixelChannelValues, sideLength_x);
	}
}


//Given a row, set all values of that row to the predetermined average pixel
void Pixelate::SetRowOfSquareLenToAverage(std::vector<Pixel>::iterator yIterator, std::vector<int> averagePixelChannelValues, int sideLength_x)
{
	//std::for_each(yIterator, std::next(yIterator, sideLength_x),
	//	[&]() {*yIterator = toCopy; });

	Pixel* p;
	for (int x = 0; x < sideLength_x; ++x)
	{
		p = &*yIterator;
		p->SetAllChannels(averagePixelChannelValues);
		yIterator++;
	}
}



std::unique_ptr<HeaderInfo> Pixelate::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//NO OP
	return std::move(hdr);
}

