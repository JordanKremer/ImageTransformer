/*
Author : Jordan Kremer
11/20/20
bmp_header_info_32_bit.h

This class is an extension of bmp_header_info. It includes extra data points only found
in the header of the 32bit bmp images.

*/


#pragma once
#include "bmp_header_info.h"


//32bit bmp images are BGRA within the channel data, despite the order in which 
//the masks appear in the header
struct bmp_header_32_bit_constants {

	inline static const int red_channel_bitmask = 54;
	inline static const int green_channel_bitmask = 58;
	inline static const int blue_channel_bitmask = 62;
	inline static const int	alpha_channel_bitmask = 64;
};



struct bmp_header_components_32_bit {
	uint32_t red_bitmask_;
	uint32_t green_bitmask_;
	uint32_t blue_bitmask_;
	uint32_t alpha_bitmask_;
};



class bmp_header_info_32_bit :
	public bmp_header_info
{
public:
	bmp_header_info_32_bit() = default;
	bmp_header_info_32_bit(bmp_header_info_32_bit& to_copy);
	bmp_header_info_32_bit(std::vector<unsigned char>& header_values);
	bmp_header_info_32_bit& operator=(const header_info& to_copy);
	
	__override _NODISCARD std::vector<unsigned char> get_raw_header() const;

private:
	std::unique_ptr<bmp_header_components_32_bit> bmp_header_components_32_bit_;
	std::vector<unsigned char> bmp_header32_bit_raw_header_; //Different length than bmpheader base class
	uint32_t get_red_bit_mask();
	uint32_t get_green_bit_mask();
	uint32_t get_blue_bit_mask();
	uint32_t get_alpha_bit_mask();
};

