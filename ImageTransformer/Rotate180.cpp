#include "Rotate180.h"



std::vector<Pixel> Rotate180::TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr)
{
	uint32_t imageWidth = hdr->GetWidth();
	uint32_t imageHeight = hdr->GetHeight();
	uint32_t pixelIdxToSwap;
	int curWidth;
	int curHeight;
	int mirrorHeight;
	int mirrorWidth;


	if (imageHeight * imageWidth > pixels.size())
		throw std::runtime_error("ERROR: INVALID IMAGE DIMENSIONS, CANNOT TRANSFORM");

	for (uint32_t curPixelIdx = 0; curPixelIdx < pixels.size(); ++curPixelIdx)
	{
		curWidth = curPixelIdx % imageWidth;
		curHeight = curPixelIdx / imageHeight;

		mirrorWidth = imageWidth - curWidth;
		mirrorHeight = imageHeight - curHeight;
		pixelIdxToSwap = mirrorHeight * imageWidth + mirrorWidth;
		
		try {
			Swap(pixels, pixelIdxToSwap, curPixelIdx);
		}
		catch (const std::out_of_range& oor)
		{
			throw oor;
		}

	}

	return pixels;
}



void Rotate180::Swap(std::vector<Pixel>& pixels, uint32_t pixelIdxToSwap, int curPixelIdx)
{
	if (curPixelIdx > pixels.size() || pixelIdxToSwap > pixels.size())
		throw std::out_of_range("ERROR: SWAP PIXEL FAILURE IN ROTATE180 TRANSFORMATION");
	
	Pixel tmp = pixels[curPixelIdx];
	pixels[curPixelIdx] = pixels[pixelIdxToSwap];
	pixels[pixelIdxToSwap] = tmp;
}


std::unique_ptr<HeaderInfo> Rotate180::TransformHeader(std::unique_ptr<HeaderInfo> header)
{
	//No op function
	return std::move(header);
}



