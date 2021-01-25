/*
Author : Jordan Kremer
11/20/2020
bmp_header_info.h

Includes functionality for bmp_header_info class, including getters for BmpHeader constants
such as width and height of the image. Includes clone().

*/

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "header_info.h"


//BITMAPHEADERINFO 
//OS/2 no longer supported, so Windows BITMAPHEADERINFO table used as reference
struct bmp_constants {
	inline static const int ID = 0;
	inline static const int FILE_SIZE = 2;
	inline static const int RESERVED1 = 6;
	inline static const int IMAGE_START_OFFSET = 10;
	inline static const int HEADER_SIZE = 14;
	inline static const int WIDTH = 18;
	inline static const int HEIGHT = 22;
	inline static const int COLOR_PANES = 26;
	inline static const int BITS_PER_PIXEL = 28;
	inline static const int COMPRESSION = 30; //values 0 - 3
	inline static const int IMAGE_SIZE = 34;
	inline static const int HORIZONTAL_RESOLUTION = 38;
	inline static const int VERTICAL_RESOLUTION = 42;
	inline static const int NUM_COLORS_IN_PALETTE = 46;
	inline static const int NUM_IMPORTANT_COLORS_USED = 50;
};


//Container for easier access
struct basic_bmp_header_components{
	std::string _ID;
	uint32_t _filesize;
	uint32_t _imageStartOffset;
	uint32_t _width;
	uint32_t _height;
	uint32_t _bitsPerPixel;
	uint32_t _compression;
	uint32_t _horizontalResolution;
	uint32_t _verticalResolution;
	
};



class bmp_header_info : public header_info
{
public:
	bmp_header_info();
	bmp_header_info(const std::vector<unsigned char>& data);
	bmp_header_info(const bmp_header_info& toCopy);
	bmp_header_info& operator =(const bmp_header_info& toCopy);
	bool isEqual(const bmp_header_info& toCompare);

	_NODISCARD uint32_t get_width() const; 
	_NODISCARD uint32_t get_height() const;
	_NODISCARD uint32_t get_compression() const; 
	_NODISCARD uint32_t get_bits_per_pixel() const;
	//Gets the start of the (RGBA) image bytes within a byte vector after the header bytes
	_NODISCARD uint32_t get_image_start_offset() const;
	_NODISCARD std::vector<unsigned char> get_raw_header() const;


	void set_height(int new_height);
	void set_width(int new_width);

	uint32_t header_components_constructor_helper(const int bmp_constant_start, const int bmpConstantEnd, const std::vector<unsigned char>& data);
	void header_raw_image_data_setter_from_integer_helper(uint32_t data_to_change_to, const int bmpConstantStart, const int bmpConstantEnd, std::vector<unsigned char>& rawData);
	
private:
	std::shared_ptr<basic_bmp_header_components> bmp_header_components_;
	std::vector<unsigned char> raw_image_values_;
};
