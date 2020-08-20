#pragma once
#include "BmpHeaderInfo.h"

class BmpHeaderInfo_24Bit :
	public BmpHeaderInfo
{
public:

	BmpHeaderInfo_24Bit();
	//BmpHeaderInfo_24Bit(const BmpHeaderInfo_24Bit& to_copy);
	BmpHeaderInfo_24Bit(std::vector<unsigned char> hdata);

	std::vector<unsigned char>::const_iterator getHeaderBegin();
	std::vector<unsigned char>::const_iterator getHeaderEnd();
	int getWidth();
	int getCompression();

	

private:
	int _translateDecimaltoRGBA(uint32_t mask);


	//https://stackoverflow.com/questions/9834067/difference-between-char-and-const-char
	std::vector<unsigned char> _headerData;  //If we don't make them shared_ptrs we risk memory leaks when the vector destructor is called

};

/*
BmpHeader_24Bit:

bmpHEader_24Bit(Bmpheader_24Bit& tocopy)-- > access raw data in this function to copy
getIteratorBegin(index)
getIteratorEnd(index)-- > use these to read raw data if needed for data points not included in the private
section
getWidth
getHeight
etc


private:
	map headerIndex<>
		int width
		int compression
		int mask
		vec<u char> rawData;  -- > used for copyingand writing out, so keep a copy of it in the headerInfo class
		** really only need the useful data points here, such as width, etc
		** the raw data is accessible by keeping it here, and we can use our iterator return
		function to get certain parts of the raw data if we need it for anything * **


		*/