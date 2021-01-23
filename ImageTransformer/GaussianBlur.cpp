#include "GaussianBlur.h"

void GaussianBlur::BlurPixels(std::vector<Pixel>& pixels)
{

	uint32_t Width = GetHeader()->GetWidth();
	uint32_t Height = GetHeader()->GetHeight();

	if (Width < 5 || Height < 5)
		throw std::runtime_error("ERROR | GAUSSIANBLUR::BLURPIXELS() : IMAGE TOO SMALL");

	//Start at 2 so that a full square will correlate with the gaussian matrix
	for (int32_t pixelx = 2; pixelx < Width - 2; ++pixelx)
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
	int channelCount = pixels[0].GetChannelCount();
	std::vector<int> channelValuesGaussianSum(channelCount, 0);
	//get corner x and y so we know where to start in the grid
	Pixel* p;
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
			auto pixelChannels = pixels[GetCoordinate(x, y)].GetAllChannelData();
			for (int channelIdx = 0; channelIdx < channelCount; ++channelIdx)
			{	
				//Set the channel to the nearest integer after multiplying the gaussian coefficient
				channelValuesGaussianSum[channelIdx] += nearbyint((double)pixelChannels[channelIdx] * (gCoeff / 256));
			}
		}
	}

	p = &pixels[GetCoordinate(centerX, centerY)];

	try {
		p->SetAllChannels(channelValuesGaussianSum);
	}
	catch (std::out_of_range& oor)
	{
		throw oor;
	}

	delete p;
}



//gives free space up to 2 spaces from left
//returns x start value for nested for loop
//for grid computation
int GaussianBlur::GetXLeft(std::vector<Pixel>& pixels, int32_t centerX)
{
	if ((centerX - 2) >= 0)
	{
		return 0; //maximum space, unsure how much space left or right
	}
	else if ((centerX - 2) == -1)
		return 1; //1 space on the left, and starting at grid 1
	else
		return 2; //up against a wall on left

	//use this to be the starting value of X
}



//gives free space up to 2 spaces to the right
//returns x end value for nested for loop
//for grid computation
int GaussianBlur::GetXRight(std::vector<Pixel>& pixels, int32_t centerX)
{
	auto Width = GetHeader()->GetWidth();
	if ((centerX + 2) <= Width)
	{
		return 0; //maximum space, unsure how much space left or right
	}
	else if ((centerX + 2) == (Width + 1))
		return 1; //1 space on the right, and ending at x =4
	else
		return 2; //up against a wall on right, ending at x = 3 so

	//use this to be the starting value of X
}



int GaussianBlur::GetYUp(std::vector<Pixel>& pixels, int32_t centerY)
{
	auto Height = GetHeader()->GetHeight();

	if ((centerY + 2) <= Height)
	{
		return 0; //maximum space, unsure how much space up and down
	}
	else if ((centerY + 2) == (Height + 1))
		return 1; //1 space above available
	else
		return 2; //up against a wall on above, no space available

	//this will be (5 - this val) and end condition for nested loop
}



int GaussianBlur::GetYDown(std::vector<Pixel>& pixels, int32_t centerY)
{
	if ((centerY - 2) >= 0)
	{
		return 0; //maximum space, unsure how much space up and down
	}
	else if ((centerY - 2) == -1)
		return 1; //1 space below
	else
		return 2; //up against a wall below

}


// Returns offset from the center of the gaussian block
int GaussianBlur::ReturnOffset(int y)
{
	if (y == 0)
		return -2;
	else if (y == 1)
		return -1;
	else if (y == 2)
		return 0;
	else if (y == 3)
		return 1;
	else
		return 2;
}



double GaussianBlur::GetGaussianNum(int x, int y)
{
	return _gaussianMatrix[x][y];
}
