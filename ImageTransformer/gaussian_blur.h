/*
Author : Jordan Kremer
1/24/2021
gaussian_blur.h

Contains functionality to perform gaussian_blur algorithm on a pixel vector.
*/


#pragma once
#include "transformation.h"
class gaussian_blur :
    public transformation
{
public:
    std::vector<pixel> transform_pixels(std::vector<pixel> pixels);
    std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr);

private:
    //Wrapper function that calls the following helper functions 
    void blur_pixels(std::vector<pixel>& pixels);
    //Utilizes the gaussian_matrix_ to perform the gaussian_blur algorithm
    void pixel_grid_multiply(std::vector<pixel>& pixels, int32_t centerX, int32_t centerY);
    //Gaussian Blur does calculations within a grid, so these following Get functions
    //Help find the edges of the grid in relation to width and height of the image
    int get_x_left(std::vector<pixel>& pixels, int32_t centerX);
    int get_x_right(std::vector<pixel>& pixels, int32_t centerX);
    int get_y_up(std::vector<pixel>& pixels, int32_t centerY);
    int get_y_down(std::vector<pixel>& pixels, int32_t centerY);
    // Returns offset from the center of the gaussian block
    int return_offset(int y);
    //Returns a number from the gaussian_matrix_
    double get_gaussian_num(int x, int y);
   
    
    std::vector<unsigned char> gaussian_vector_;
    double gaussian_matrix_[5][5] = {1, 4, 6, 4, 1,
                                    4, 16, 24, 16, 4,
                                    6, 24, 36, 24, 6,
                                    4, 16, 24, 16, 4,
                                    1, 4, 6, 4, 1 };
};

