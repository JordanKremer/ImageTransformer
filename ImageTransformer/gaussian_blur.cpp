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


#include "gaussian_blur.h"

std::vector<pixel> gaussian_blur::transform_pixels(std::vector<pixel> pixels)
{
	try {
		blur_pixels(pixels);
	}
	catch(std::runtime_error& runError){
		throw runError;
	}
	catch (std::out_of_range& oor)
	{
		throw oor;
	}

	return pixels;
}



std::unique_ptr<header_info> gaussian_blur::transform_header(std::unique_ptr<header_info> hdr)
{
	//No op
	return std::move(hdr);
}



void gaussian_blur::blur_pixels(std::vector<pixel>& pixels)
{

	uint32_t Width = get_header()->get_width();
	uint32_t Height = get_header()->get_height();

	if (Width < 5 || Height < 5)
		throw std::runtime_error("ERROR | GAUSSIANBLUR::BLURPIXELS() : IMAGE TOO SMALL");

	//Start at 2 so that a full square will correlate with the gaussian matrix
	for (int32_t pixelx = 2; pixelx < Width - 2; ++pixelx)
	{
		for (int32_t pixely = 2; pixely < Height - 2; ++pixely)
		{
			pixel_grid_multiply(pixels, pixelx, pixely);
		}
	}
}



void gaussian_blur::pixel_grid_multiply(std::vector<pixel>& pixels, int32_t centerX, int32_t centerY)
{
	int offsetX;
	int offsetY;

	double red = 0;
	double green = 0;
	double blue = 0;
	int channelCount = pixels[0].get_channel_count();
	std::vector<int> channelValuesGaussianSum(channelCount, 0);

	//get corner x and y so we know where to start in the grid
	for (int x = get_x_left(pixels, centerX); x < (5 - get_x_right(pixels, centerX)); x++)
	{
		for (int y = get_y_down(pixels, centerY); y < (5 - get_y_up(pixels, centerY)); y++)
		{

			offsetX = return_offset(x); //return offset from the center of the gaussian block
			offsetY = return_offset(y);
			offsetX = centerX + offsetX;
			offsetY = centerY + offsetY;
			double gCoeff = get_gaussian_num(x, y);

			//Calculate and add gaussian values
			auto pixelChannels = pixels[get_coordinate(offsetX, offsetY)].get_all_channel_data();
			for (int channelIdx = 0; channelIdx < channelCount; ++channelIdx)
			{	
				//Set the channel to the nearest integer after multiplying the gaussian coefficient
				channelValuesGaussianSum[channelIdx] += nearbyint((double)pixelChannels[channelIdx] * (gCoeff / 256));
			}
		}
	}

	

	try {
		pixels[get_coordinate(centerX, centerY)].set_all_channels(channelValuesGaussianSum);
	}
	catch (std::out_of_range& oor)
	{
		throw oor;
	}

	//delete p;
}



//gives free space up to 2 spaces from left
//returns x start value for nested for loop
//for grid computation
int gaussian_blur::get_x_left(std::vector<pixel>& pixels, int32_t centerX)
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
int gaussian_blur::get_x_right(std::vector<pixel>& pixels, int32_t centerX)
{
	auto Width = get_header()->get_width();
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



int gaussian_blur::get_y_up(std::vector<pixel>& pixels, int32_t centerY)
{
	auto Height = get_header()->get_height();

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



int gaussian_blur::get_y_down(std::vector<pixel>& pixels, int32_t centerY)
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
int gaussian_blur::return_offset(int y)
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



double gaussian_blur::get_gaussian_num(int x, int y)
{
	return gaussian_matrix_[x][y];
}
