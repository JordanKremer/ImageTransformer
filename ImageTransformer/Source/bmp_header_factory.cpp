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




#include "../Headers/bmp_header_factory.h"
#include "../Headers/bmp_header_info_32_bit.h"
#include <stdexcept>


bmp_header_factory::bmp_header_factory() = default;


//Creates a bmp_header_info ptr from the raw_image_values_, which is then used
//in the caller function to create a generic_image object.
std::unique_ptr<bmp_header_info> bmp_header_factory::get_bmp_header(std::vector<unsigned char>& raw_image_values) {

	const auto compressionFlag = get_compression(raw_image_values);
	switch(compressionFlag)
	{
		case 0: return std::make_unique<bmp_header_info>(raw_image_values);
		case 1: return std::make_unique<bmp_header_info>(raw_image_values);
		case 2: return std::make_unique<bmp_header_info>(raw_image_values);
		case 3: return std::make_unique<bmp_header_info_32_bit>(raw_image_values);
		default: throw std::runtime_error("ERROR: FAILED TO GENERATE BMPHEADER, COMPRESSION OUT OF BOUNDS");
	}
}



//Takes the compression bytes from the header, bytes 30-33, and compresses them into
//a single integer. get_bmp_header is the caller.
int bmp_header_factory::get_compression(std::vector<unsigned char>& raw_image_values)
{
	char ID[2];
	ID[0] = raw_image_values[0];
	ID[1] = raw_image_values[1];

	//Need to expand this validation
	if (!(ID[0] == 'B' && ID[1] == 'M'))
		throw std::runtime_error("ERROR: NOT A BMP");

	//load compression bytes from the raw_image_values_ into the integer
	uint32_t compressionFlag;
	for (int idx = 0; idx < 4; ++idx) {
		((unsigned char*)& compressionFlag)[idx] = raw_image_values[idx + 30];
	}

	return compressionFlag;
}