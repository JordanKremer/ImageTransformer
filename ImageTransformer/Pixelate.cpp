#include "Pixelate.h"

Pixelate::Pixelate()
{
	squareLen = 16;
}



std::vector<Pixel> Pixelate::TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr)
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
	}
	*/
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



Pixel Pixelate::Average16RGB(const HeaderInfo* hdr, std::vector<Pixel> pixels, std::pair<uint32_t, uint32_t> startCoordinate) {
	uint32_t tmpR = 0;
	uint32_t tmpG = 0;
	uint32_t tmpB = 0;


	//build dummy tmp pixel
	auto channelCount = pixels[0].GetChannelCount();
	std::vector<unsigned char> channelData;
	for (int i = 0; i < channelCount; ++i)
	{
		channelData.push_back(0);
	}

	Pixel tmpPixel(channelData, channelCount);



	if (xBoundAddition == 0)
		xBoundAddition = 16;
	if (yBoundAddition == 0)
		yBoundAddition = 16;


	//Add pixel values together
	for (uint32_t imageWidth = x; imageWidth < (x+squareLen); imageWidth++)
	{
		for (uint32_t imageHeight = y; imageHeight < (y + squareLen); imageHeight++)
		{

			tmpPixel = tmpPixel + GetPixelAtCoordinate(pixels, hdr, imageWidth, imageHeight);

			/*
			tmpR += returnRedByte(imageWidth, imageHeight);
			tmpG += returnGreenByte(imageWidth, imageHeight);
			tmpB += returnBlueByte(imageWidth, imageHeight);
			*/
		}
	}


	for (auto& channel : tmpPixel.GetAllChannelData())
	{

	}


	tmpR = tmpR / (xBoundAddition * yBoundAddition);
	tmpB = tmpB / (xBoundAddition * yBoundAddition);
	tmpG = tmpG / (xBoundAddition * yBoundAddition);


	//in a 16x 16 block, make all the pixels values the average that was just determined
	for (uint32_t imageWidth = startCoordinate.first; imageWidth <(startCoordinate.first+squareLen); imageWidth++)
	{
		for (uint32_t imageHeight = startCoordinate.second; imageHeight < (startCoordinate.second +squareLen); imageHeight++)
		{
			returnRedByte(imageWidth, imageHeight) = tmpR;
			returnGreenByte(imageWidth, imageHeight) = tmpG;
			returnBlueByte(imageWidth, imageHeight) = tmpB;
		}
	}
}



std::unique_ptr<HeaderInfo> Pixelate::TransformHeader(std::unique_ptr<HeaderInfo> header)
{
	return std::unique_ptr<HeaderInfo>();
}




std::vector<std::vector<Pixel>::iterator> Pixelate::GetIteratorsOfPixelBox(std::vector<Pixel> pixels, int curBox_X, int curBox_Y)
{
	std::vector<std::vector<Pixel>::iterator> boxIterators;
	for (int row = 0; row < squareLen; ++row) //row of box
	{
		std::vector<Pixel>::iterator rowIterator = pixels.begin() + GetBoxIteratorOffset(curBox_X, curBox_Y, row);
	}
}


uint32_t Pixelate::GetBoxIteratorOffset(int curBox_X, int curBox_Y, int row, int width)
{
	return (curBox_X * squareLen) + (((curBox_Y * squareLen) + row) * width);
}