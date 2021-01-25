
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


#include "bmp_header_info_32_bit.h"

bmp_header_info_32_bit::bmp_header_info_32_bit()
{
}



bmp_header_info_32_bit::bmp_header_info_32_bit(bmp_header_info_32_bit& to_copy)
{
}



bmp_header_info_32_bit::bmp_header_info_32_bit(std::vector<unsigned char>& header_values):bmp_header_info(header_values)
{
	bmp_constants bmpConstants;
	bmp_header_32_bit_constants bmpConstants_32Bit;

	bmp_header_components_32_bit_ = std::make_unique<bmp_header_components_32_bit>();
	bmp_header_components_32_bit_->_redBitMask = header_components_constructor_helper(bmpConstants_32Bit.RED_CHANNEL_BITMASK, bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, header_values);
	bmp_header_components_32_bit_->_greenBitmask = header_components_constructor_helper(bmpConstants_32Bit.GREEN_CHANNEL_BITMASK, bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, header_values);
	bmp_header_components_32_bit_->_blueBitMask = header_components_constructor_helper(bmpConstants_32Bit.BLUE_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, header_values);
	bmp_header_components_32_bit_->_alphaBitMask = header_components_constructor_helper(bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK, bmpConstants_32Bit.ALPHA_CHANNEL_BITMASK + 4, header_values);

	

	for (int i = 0; i < get_image_start_offset(); ++i)
	{
		//load rawdata and / or add an extra vector that holds this information to BmpHeader32bit
		bmp_header32_bit_raw_header_.push_back(header_values[i]);
	}
}

std::vector<unsigned char> bmp_header_info_32_bit::get_raw_header() const
{
	return bmp_header32_bit_raw_header_;
}



bmp_header_info_32_bit& bmp_header_info_32_bit::operator=(const header_info& to_copy)
{
	return *this;
}



uint32_t bmp_header_info_32_bit::get_red_bit_mask()
{
	return bmp_header_components_32_bit_->_redBitMask;
}



uint32_t bmp_header_info_32_bit::get_green_bit_mask()
{
	return bmp_header_components_32_bit_->_greenBitmask;
}



uint32_t bmp_header_info_32_bit::get_blue_bit_mask()
{
	return bmp_header_components_32_bit_->_blueBitMask;
}



uint32_t bmp_header_info_32_bit::get_alpha_bit_mask()
{
	return bmp_header_components_32_bit_->_alphaBitMask;
}




