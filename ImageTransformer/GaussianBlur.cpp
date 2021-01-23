#include "GaussianBlur.h"

void GaussianBlur::BlurPixels(std::vector<Pixel>& pixels)
{

	uint32_t Width = GetHeader()->GetWidth();
	uint32_t Height = GetHeader()->GetHeight();

	if (Width < 5 || Height < 5)
		throw std::runtime_error("ERROR | GAUSSIANBLUR::BLURPIXELS() : IMAGE TOO SMALL");

	//Start at 2 so that a full square will correlate with the gaussian matrix
	for (int32_t pixelx = 2; pixelx <  - 2; ++pixelx)
	{
		for (int32_t pixely = 2; pixely < Height - 2; ++pixely)
		{
			PixelGridMultiply(pixels, pixelx, pixely);
		}
	}
}

void GaussianBlur::PixelGridMultiply(std::vector<Pixel>& pixels, int32_t centerX, int32_t centerY)
{
	int offsetX;
	int offsetY;

	double red = 0;
	double green = 0;
	double blue = 0;

	//get corner x and y so we know where to start in the grid
	for (int x = GetXLeft(pixels, centerX); x < (5 - GetXRight(pixels, centerX)); x++)
	{
		for (int y = GetYDown(pixels, centerY); y < (5 - GetYUp(pixels, centerY)); y++)
		{

			offsetX = ReturnOffset(x); //return offset from the center of the gaussian block
			offsetY = ReturnOffset(y);
			offsetX = centerX + offsetX;
			offsetY = centerY + offsetY;
			double gCoeff = GetGaussianNum(x, y);

			//Calculate and add gaussian values
			auto pixel = GetPixelAtCoordinate(pixels, x, y);
			int tmp;
			
			for (int channelIdx = 0; channelIdx < pixel.GetChannelCount(); ++channelIdx)
			{	
				//Set the channel to the nearest integer after multiplying the gaussian coefficient
				pixel.SetChannel(channelIdx, nearbyint((double)pixel.GetChannel(channelIdx) * (gCoeff / 256)));
			}
		}
	}

	//sets RGB at given x and y
	setPixelBytetoRGBComputation(red, green, blue, centerX, centerY);
}

double GaussianBlur::GetGaussianNum(int x, int y)
{
	return _gaussianMatrix[x][y];
}
