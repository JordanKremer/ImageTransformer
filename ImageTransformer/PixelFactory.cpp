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




#include "PixelFactory.h"

Pixel& PixelFactory::GetPixel(int channelCount, std::vector<unsigned char>& data, int dataIdx)
{

	std::vector<unsigned char> channelData;
	

	if (channelCount == 1 || channelCount == 4) {
		channelData.push_back(data[dataIdx]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if (channelCount == 8)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if(channelCount == 16 || channelCount == 24)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if (channelCount == 32)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else {
		throw std::runtime_error("ERROR: PIXELFACTORY: channelCount OUT OF BOUNDS");
	}
}
