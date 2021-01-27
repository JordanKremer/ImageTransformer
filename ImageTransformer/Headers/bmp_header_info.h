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
	inline static const int id = 0;
	inline static const int file_size = 2;
	inline static const int reserved1 = 6;
	inline static const int image_start_offset = 10;
	inline static const int header_size = 14;
	inline static const int width = 18;
	inline static const int height = 22;
	inline static const int color_panes = 26;
	inline static const int bits_per_pixel = 28;
	inline static const int compression = 30; //values 0 - 3
	inline static const int image_size = 34;
	inline static const int horizontal_resolution = 38;
	inline static const int vertical_resolution = 42;
	inline static const int num_colors_in_palette = 46;
	inline static const int num_important_colors_used = 50;
};


//Container for easier access
struct basic_bmp_header_components{
	std::string id;
	uint32_t file_size;
	uint32_t image_start_offset;
	uint32_t width;
	uint32_t height;
	uint32_t bits_per_pixel;
	uint32_t compression;
	uint32_t horizontal_resolution;
	uint32_t vertical_resolution;
	
};



class bmp_header_info : public header_info
{
public:
	bmp_header_info();
	virtual ~bmp_header_info() = default;
	
	bmp_header_info(const std::vector<unsigned char>& raw_image_values);
	bmp_header_info(const bmp_header_info& to_copy);
	bmp_header_info& operator =(const bmp_header_info& to_copy);
	bool is_equal(const bmp_header_info& to_compare);

	_NODISCARD uint32_t get_width() const override; 
	_NODISCARD uint32_t get_height() const override;
	_NODISCARD uint32_t get_compression() const override; 
	_NODISCARD uint32_t get_bits_per_pixel() const override;
	_NODISCARD uint32_t get_image_start_offset() const override; 	//Gets the start of the (RGBA) image bytes within a byte vector after the header bytes
	_NODISCARD std::vector<unsigned char> get_raw_header() const override;


	void set_height(int new_height) override;
	void set_width(int new_width) override;

	static uint32_t header_components_constructor_helper(const int bmp_constant_start, const int bmp_constant_end, const std::vector<unsigned char>& raw_image_values);
	static void header_raw_image_data_setter_from_integer_helper(uint32_t data_to_change_to, const int bmp_constant_start, const int bmp_constant_end, std::vector<unsigned char>& raw_image_values);
	
private:
	std::shared_ptr<basic_bmp_header_components> bmp_header_components_;
	std::vector<unsigned char> raw_image_values_;
};
