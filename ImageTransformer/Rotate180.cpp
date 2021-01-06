#include "Rotate180.h"

/*
std::unique_ptr<Data> Rotate180::Transform(std::unique_ptr<Data> adaptedData)
{
	
	vector<unsigned char>tmpVec;
	bool hasCountedWidth = false;
	for (int y = (Height - 1); y > -1; y--)
	{
		for (int x = (Width - 1); x > -1; x--)
		{
			pushPixelOntoVector(tmpVec, x, y);
			if (!hasCountedWidth)
				++scaledWidth;
		}
		hasCountedWidth = true;
		++scaledHeight;
	}
	pixelByte = tmpVec;
	

	adaptedData->_header;


	//data needs args for constructor
	//return std::move(std::make_unique<Data>());
	return nullptr;
}
*/


std::vector<Pixel> Rotate180::TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr)
{
	uint32_t imageWidth = hdr->GetWidth();
	uint32_t imageHeight = hdr->GetHeight();
	int curLowerBoundIdx = 0;
	int curUpperBoundIdx = imageHeight;

	for (int widthIdx = 0; widthIdx < imageWidth; ++widthIdx)
	{
		curUpperBoundIdx = imageHeight;
		for (int heightIdx = 0; heightIdx < imageHeight / 2; ++heightIdx)
		{
			curLowerBoundIdx = widthIdx * heightIdx;
			
			try {
				Swap(pixels, curUpperBoundIdx, curLowerBoundIdx);
			}
			catch (const std::out_of_range& oor)
			{
				//either throw to next level up, or just output a message here
			}

			--curUpperBoundIdx;
		}
	}


	return pixels;
}

//not sure if I should be passing by ref or just using the move copy...it might be 
//really slow to execute it a lot
//pass by ref?
//dont make a function at all?
void Rotate180::Swap(std::vector<Pixel>& pixels, int curUpperBoundIdx, int curLowerBoundIdx)
{
	Pixel tmp = pixels[curLowerBoundIdx];
	pixels[curLowerBoundIdx] = pixels[curUpperBoundIdx];
	pixels[curUpperBoundIdx] = tmp;
}


std::unique_ptr<HeaderInfo> Rotate180::TransformHeader(std::unique_ptr<HeaderInfo> header)
{
	//No op function
	return std::move(header);
}
