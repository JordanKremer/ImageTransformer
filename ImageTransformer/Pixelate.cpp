#include "Pixelate.h"

Pixelate::Pixelate()
{
	squareLen = 16;
}



std::vector<Pixel> Pixelate::TransformPixels(std::vector<Pixel> pixels)
{
	//return error if the image is not atleast 16x16?


	/*
	uint8_t xFull16Additions = Width / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t yFull16Additions = Height / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t xRemainder = Width % 16;				//Remainder values if 16x16 doesn't fit perfectly
	uint8_t yRemainder = Height % 16;
	uint8_t boundCheckerX = 0;
	uint8_t boundCheckerY = 0;
	uint8_t to_addY = 16;
	uint8_t to_addX = 16;


	if (xRemainder > yRemainder)
	{
		xRemainder = yRemainder;
	}
	else
		yRemainder = xRemainder;

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
	}*/

	auto hdr = GetHeader();
	if (!hdr) {
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS(): FAILED TO SET HEADER");
	}
	
	uint32_t Width = hdr->GetWidth();
	uint32_t Height = hdr->GetHeight();

	uint8_t xFull16Additions = Width / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t yFull16Additions = Height / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t xRemainder = Width % 16;				//Remainder values if 16x16 doesn't fit perfectly
	uint8_t yRemainder = Height % 16;
	uint8_t boundCheckerX = 0;
	uint8_t boundCheckerY = 0;
	uint8_t to_addY = 16;
	uint8_t to_addX = 16;



	if (xRemainder > yRemainder)
	{
		xRemainder = yRemainder;
	}
	else
		yRemainder = xRemainder;

	
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





//xboundaddition and yboundaddition are the squarelen, which we can get from squarelen from pixelate



Pixel Pixelate::Average16RGB(std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> startCoordinate) {
	
	auto hdr = GetHeader();
	

	//build dummy tmp pixel
	auto channelCount = pixels[0].GetChannelCount();
	std::vector<unsigned char> channelData(channelCount, 0);
	Pixel tmpPixel(channelData, channelCount);



	if (xBoundAddition == 0)
		xBoundAddition = 16;
	if (yBoundAddition == 0)
		yBoundAddition = 16;

	int x = startCoordinate.first;
	int y = startCoordinate.second;


	/*
	//Add pixel values together
	for (uint32_t imageWidth = x; imageWidth < (x+squareLen); imageWidth++)
	{
		for (uint32_t imageHeight = y; imageHeight < (y + squareLen); imageHeight++)
		{
			tmpPixel = tmpPixel + GetPixelAtCoordinate(pixels, imageWidth, imageHeight);
		}
	}



	//Average the pixel channel values, and set the tmp pixel to those values
	auto channelValues = tmpPixel.GetAllChannelData();
	for (int channelIdx = 0; channelIdx < channelCount; ++channelIdx)
	{
		try {
			int tmpChannelValue = channelValues[channelIdx] / (squareLen * squareLen);
			tmpPixel.SetChannel(channelIdx, tmpChannelValue);
		}
		catch (std::out_of_range& oor) {
			throw oor;
		}
	}



	//in a 16x 16 block, make all the pixels values the average that was just determined
	for (uint32_t imageWidth = x; imageWidth <(x+squareLen); ++imageWidth)
	{
		for (uint32_t imageHeight = y; imageHeight < (y +squareLen); ++imageHeight)
		{
			auto p = GetPixelAtCoordinate(pixels, imageWidth, imageHeight);
		}
	}

	*/



	auto boxIterators = GetIteratorsOfPixelBox(pixels, x, y);

	

	for (auto& iter : boxIterators)
	{
		tmpPixel = tmpPixel + GetRowPixelAdditionReduction(iter);
	}
}



std::unique_ptr<HeaderInfo> Pixelate::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//NO OP
	return std::move(hdr);
}




std::vector<std::vector<Pixel>::iterator> Pixelate::GetIteratorsOfPixelBox(std::vector<Pixel> pixels, int curBox_X, int curBox_Y)
{
	std::vector<std::vector<Pixel>::iterator> boxIterators;
	for (int row = 0; row < squareLen; ++row) //row of box
	{
		std::vector<Pixel>::iterator rowIterator = pixels.begin() + GetBoxIteratorStartIdx(curBox_X, curBox_Y, row);
	}
}



//Return the start of row where the iterator will begin, call for each row within box
uint32_t Pixelate::GetBoxIteratorStartIdx(int curBox_X, int curBox_Y, int row)
{
	auto hdr = GetHeader();
	return (curBox_X * squareLen) + (((curBox_Y * squareLen) + row) * hdr->GetWidth());
}



//Add up all of the pixels within the row
Pixel Pixelate::GetRowPixelAdditionReduction(std::vector<Pixel>::iterator rowIterator, Pixel sumPixel)
{
	std::for_each(rowIterator, std::next(rowIterator, squareLen),
		[&]() {sumPixel = sumPixel + *rowIterator; });

	return sumPixel;
}
