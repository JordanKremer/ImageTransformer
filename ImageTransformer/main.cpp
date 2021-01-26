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


#include <iostream>
#include "applicator.h"
#include "adapter_factory.h"
#include "transformation_factory.h"
#include "transformation.h"
#include "generic_image.h"
#include "loader.h"
#include "writer.h"



int main(int argc, char* argv[])
{

	std::string FILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp");
	std::string FILETYPE("bmp");
	std::string TRANSFORMATIONTYPE("rotate180");
	std::string OUTFILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_new.bmp");

/*

	std::string FILENAME(argv[1]);
	std::string FILETYPE(argv[2]);
	std::string TRANSFORMATIONTYPE(argv[3]);
	std::string OUTFILENAME(argv[4]);
*/

	//load -> Adapt to generic -> Transform image -> Adapt back to byte vector -> Write to disk
	try {
		auto raw_image_byte_values = loader::load(FILENAME);
		auto adapter = adapter_factory::get_adapter(FILETYPE);
		auto generic_adapted_image = adapter->adapt_from_raw(raw_image_byte_values);
		auto transformer = transformation_factory::get_transformation(TRANSFORMATIONTYPE);
		auto transformed_adapted_image = applicator::apply_transformation(std::move(generic_adapted_image), std::move(transformer));
		const auto transformed_raw_pixel_values = adapter->adapt_to_raw(std::move(transformed_adapted_image));
		writer::write_to_file(transformed_raw_pixel_values, OUTFILENAME);
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what();
	}
	catch (const std::runtime_error& error) {
		std::cout << error.what();
	}

	return 0;
}