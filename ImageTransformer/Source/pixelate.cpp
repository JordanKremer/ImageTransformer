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


#include "../Headers/pixelate.h"

pixelate::pixelate()
{
	square_len_ = 16;
	x_edge_remainder_ = 0;
	y_edge_remainder_ = 0;
}



//Set edge remainders if there are incomplete squarelen Squarees on the edges of the picture
void pixelate::set_edge_remainders()
{
	auto hdr = get_header();
	x_edge_remainder_ = hdr->get_width() % 16;
	y_edge_remainder_ = hdr->get_height() % 16;
}



std::vector<pixel> pixelate::transform_pixels(std::vector<pixel> pixels)
{
	
	auto hdr = get_header();
	if (!hdr) {
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS(): FAILED TO SET HEADER");
	}

	if (hdr->get_width() < 16 || hdr->get_height() < 16)
	{
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS() : WIDTH || HEIGHT TOO SMALL");
	}
	
	set_edge_remainders();

	uint32_t Width = hdr->get_width();
	uint32_t Height = hdr->get_height();

	uint8_t xFullSquares = Width / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t yFullSquares = Height / 16;			//Given a 16x16 block, how many full blocks are available for x
	uint8_t xRemainder = Width % 16;				//Remainder values if 16x16 doesn't fit perfectly
	uint8_t yRemainder = Height % 16;

	//								X (col)   ,    Y(row)
	std::pair<int, int> sideLengths(square_len_, square_len_);
	std::pair<int, int> sideLengthsWithRemainderX(square_len_ + xRemainder, square_len_);
	std::pair<int, int> sideLengthsWithRemainderY(square_len_, square_len_ + yRemainder);
	std::pair<int, int> sideLengthsWithBothRemainders(square_len_ + xRemainder, square_len_ + yRemainder);


	//NOTE : yFullSquares are rows, xFullSquares are columns, make sure to check that all functions adhere to this
	//As well, make sure to follow curSquareCoordinate . first/second through to ensure 


	//Pixelates 16x16 blocks, + remainder blocks

	//Pass to average16_rgb as [col][row] which is the same as [x][y]

	std::pair<int, int> curSquareCoordinate;

	//rows
	for (int yCurSquare = 0; yCurSquare < yFullSquares; ++yCurSquare)
	{
		//columns
		for (int xCurSquare = 0; xCurSquare < xFullSquares; ++xCurSquare)  
		{
			curSquareCoordinate.first = xCurSquare;
			curSquareCoordinate.second = yCurSquare;

			//Account for all of the scenarios
			//if we are on our last full x (col) square but not our last full y (row) square within a column
			if ((xCurSquare == xFullSquares - 1) && (yCurSquare < (yFullSquares - 1)))
			{
				pixels = average16_rgb(pixels, curSquareCoordinate, sideLengthsWithRemainderX);
			}
			//if we are on our last full y (row) square but not our last full x (col) square within a column
			else if ((xCurSquare == xFullSquares - 1) && (yCurSquare < (yFullSquares - 1)))
			{
				pixels = average16_rgb(pixels, curSquareCoordinate, sideLengthsWithRemainderY);
			}
			//if we are on our last full x (col) square and our last full y (row) square --> corner case
			else if ((xCurSquare == (xFullSquares - 1)) && (yCurSquare == (yFullSquares - 1)))
			{
				pixels = average16_rgb(pixels, curSquareCoordinate, sideLengthsWithBothRemainders);
			}
			//Default case, where the current square is not on an edge
			else {
				pixels = average16_rgb(pixels, curSquareCoordinate, sideLengths);
			}
		}
	}

	return pixels;
}



//Takes a starting coordinate within the image and sums a squares worth of pixels together, takes average of that sum
//and sets all pixels within that square to that average value
std::vector<pixel> pixelate::average16_rgb(std::vector<pixel> pixels, std::pair<int, int> cur_square_coordinate, std::pair<int, int> side_lengths) 
{
	int sideLength_x = side_lengths.first;  //columns
	int sideLength_y = side_lengths.second; //rows


	//Get iterators
	//auto squareIterators = get_iterators_of_pixel_square(pixels, cur_square_coordinate, sideLength_y);
	std::vector<std::vector<pixel>::iterator> squareIterators;
	std::vector<pixel>::iterator yIterator;
	for (int y = 0; y < sideLength_y; ++y) //row of Square
	{
		//This iterator is where the row begins
		yIterator = pixels.begin() + get_square_iterator_start_idx(cur_square_coordinate, y);

		squareIterators.push_back(yIterator);
	}


	std::vector<int> sumOfRowOfChannelValues(pixels[0].get_channel_count(), 0);

	for (auto& rowIter : squareIterators)
	{
		sumOfRowOfChannelValues = get_row_pixel_addition_reduction(rowIter, sumOfRowOfChannelValues, sideLength_x);
	}



	//Divide pixel values by total pixels
	int totalPixels = sideLength_x * sideLength_y;
	auto averagePixelChannelValues = average_pixel_values_by_square_dimensions(sumOfRowOfChannelValues, totalPixels);

	//Rewrite pixel values within Square to reflect the new values
	set_pixel_square_to_average(squareIterators, averagePixelChannelValues, sideLength_x);

	return pixels;
}




//Returns a vector of iterators that are the start of each row for the current Square
std::vector<std::vector<pixel>::iterator> pixelate::get_iterators_of_pixel_square(std::vector<pixel> pixels, std::pair<int, int> cur_square_coordinate, int side_length_y)
{
	std::vector<std::vector<pixel>::iterator> squareIterators;
	std::vector<pixel>::iterator yIterator;
	for (int y = 0; y < side_length_y; ++y) //row of Square
	{
		//This iterator is where the row begins
		yIterator = pixels.begin() + get_square_iterator_start_idx(cur_square_coordinate, y);

		squareIterators.push_back(yIterator);
	}
	
	return squareIterators;
}




//Return the start of row where the iterator will begin, call for each row within Square
uint32_t pixelate::get_square_iterator_start_idx(std::pair<int, int> curSquareCoordinate, int y)
{
	auto curSquare_X = curSquareCoordinate.first;
	auto curSquare_Y = curSquareCoordinate.second;
	auto hdr = get_header();
	return (curSquare_X * square_len_) + (((curSquare_Y * square_len_) + y) * hdr->get_width());
}




//Add up all of the pixels within the row for square_len_ and return it
//Leave as pass by value so that multiple instances can be run simultaneously
std::vector<int> pixelate::get_row_pixel_addition_reduction(std::vector<pixel>::iterator yIterator, std::vector<int> sum_of_row_of_channel_values, int side_length_x)
{
	//Initially intended to use for_each as such:
	//std::for_each(yIterator, std::next(yIterator, side_length_x),
	//	[&]() {sumPixel = sumPixel + *yIterator; });

	for (int x = 0; x < side_length_x; ++x)
	{
		sum_of_row_of_channel_values = get_row_pixel_addition_reduction_helper(sum_of_row_of_channel_values, *yIterator);
		yIterator++;
	}

	return sum_of_row_of_channel_values;
}



std::vector<int> pixelate::get_row_pixel_addition_reduction_helper(std::vector<int> sum_of_row_of_channel_values, pixel pixel)
{
	int channelCount = sum_of_row_of_channel_values.size();
	if (pixel.get_channel_count() != channelCount)
		throw std::runtime_error("ERROR | PIXELATE::GETROWPIXELADDITIONREDUCTIONHELPER()");
	
	for (int channelIdx = 0; channelIdx < channelCount; ++channelIdx)
	{
		sum_of_row_of_channel_values[channelIdx] += pixel.get_channel(channelIdx);
	}

	return sum_of_row_of_channel_values;
}



//Average the pixel value by square_len_ for the temporary holder pixel
std::vector<int> pixelate::average_pixel_values_by_square_dimensions(std::vector<int> sum_of_row_of_channel_values, int total_pixels)
{
	int averageOfChannel = 0;
	for (int channelIdx = 0; channelIdx < sum_of_row_of_channel_values.size(); ++channelIdx)
	{
		sum_of_row_of_channel_values[channelIdx] /= total_pixels;
	}

	return sum_of_row_of_channel_values;
}



//For each pixel within the Square, set that pixel equal to toCopy, the average pixel
void pixelate::set_pixel_square_to_average(std::vector<std::vector<pixel>::iterator> squareIterators, std::vector<int> average_pixel_channel_values, int side_length_x)
{
	for (auto& iter : squareIterators)
	{
		set_row_of_square_len_to_average(iter, average_pixel_channel_values, side_length_x);
	}
}


//Given a row, set all values of that row to the predetermined average pixel
void pixelate::set_row_of_square_len_to_average(std::vector<pixel>::iterator yIterator, std::vector<int> average_pixel_channel_values, int sideLength_x)
{
	//std::for_each(yIterator, std::next(yIterator, sideLength_x),
	//	[&]() {*yIterator = toCopy; });

	pixel* p;
	for (int x = 0; x < sideLength_x; ++x)
	{
		p = &*yIterator;
		p->set_all_channels(average_pixel_channel_values);
		yIterator++;
	}
}



std::unique_ptr<header_info> pixelate::transform_header(std::unique_ptr<header_info> hdr)
{
	//NO OP
	return std::move(hdr);
}

