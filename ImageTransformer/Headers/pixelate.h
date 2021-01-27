/*
Author : Jordan Kremer
1/24/2021
pixelate.h

Contains functionality to perform Pixelation algorithm on a pixel vector.

*/


#pragma once
#include "transformation.h"
class pixelate :
	public transformation
{
public:
	pixelate();
	std::vector<pixel> transform_pixels(std::vector<pixel> pixels) override;
	std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr) override;
	
private:
	void set_edge_remainders();
	std::vector<int> average_pixel_values_by_square_dimensions(std::vector<int> sum_of_row_of_channel_values, int total_pixels);
	void set_row_of_square_len_to_average(std::vector<pixel>::iterator row_iterator, std::vector<int> average_pixel_channel_values, int square_len);
	void set_pixel_square_to_average(std::vector<std::vector<pixel>::iterator> box_iterators, std::vector<int> average_pixel_channel_values, int side_length_x);
	std::vector<std::vector<pixel>::iterator> get_iterators_of_pixel_square(std::vector<pixel> pixels, std::pair<int, int> cur_square_coordinate, int side_length_y);
	uint32_t get_square_iterator_start_idx(std::pair<int, int> curSquareCoordinate, int row);
	std::vector<int> get_row_pixel_addition_reduction(std::vector<pixel>::iterator row_iterator, std::vector<int> sum_of_row_of_channel_values, int side_length_x);
	std::vector<int> get_row_pixel_addition_reduction_helper(std::vector<int> sum_of_row_of_channel_values, pixel pixel);
	
	std::vector<pixel> average16_rgb(std::vector<pixel> pixels, std::pair<int, int> cur_square_coordinate, std::pair<int, int> side_lengths);
	

	int square_len_;
	int x_edge_remainder_;
	int y_edge_remainder_;
};
