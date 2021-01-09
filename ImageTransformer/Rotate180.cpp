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
			//either throw to next level up, or just output a message here
			throw oor;
		}

	}

	return pixels;
}



//not sure if I should be passing by ref or just using the move copy...it might be 
//really slow to execute it a lot
//pass by ref?
//dont make a function at all?
void Rotate180::Swap(std::vector<Pixel>& pixels, uint32_t pixelIdxToSwap, int curPixelIdx)
{
	Pixel tmp = pixels[curPixelIdx];
	pixels[curPixelIdx] = pixels[pixelIdxToSwap];
	pixels[pixelIdxToSwap] = tmp;
}


std::unique_ptr<HeaderInfo> Rotate180::TransformHeader(std::unique_ptr<HeaderInfo> header)
{
	//No op function
	return std::move(header);
}



