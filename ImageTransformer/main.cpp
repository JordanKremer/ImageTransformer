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
//#include <windows.h>


int main(int argc, char* argv[])
{

	std::string FILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp");
	std::string FILETYPE("bmp");
	std::string TRANSFORMATIONTYPE("rotate180");
	std::string OUTFILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_new.bmp");


	//Not necessesary as the user and/or UI can point to the file location 
	/*
	char pBuf[256];
	size_t len = sizeof(pBuf);
	int bytes = GetModuleFileName(NULL, pBuf, len);
	*/
/*

	std::string FILENAME(argv[1]);
	std::string FILETYPE(argv[2]);
	std::string TRANSFORMATIONTYPE(argv[3]);
	std::string OUTFILENAME(argv[4]);
*/

	auto file_loader = std::make_unique<loader>();
	auto file_writer = std::make_unique<writer>();
	auto adapter_fac = std::make_unique<adapter_factory>();
	auto transform_fac = std::make_unique<transformation_factory>();
	auto transformation_applicator = std::make_unique<applicator>();

	//load -> Adapt to generic -> Transform image -> Adapt back to byte vector -> Write to disk
	try {
		auto raw_image_byte_values = file_loader->load(FILENAME);
		auto adapter = adapter_fac->get_adapter(FILETYPE);
		auto generic_adapted_image = adapter->adapt_from_raw(raw_image_byte_values);
		auto transformer = transform_fac->get_transformation(TRANSFORMATIONTYPE);
		auto transformed_adapted_image = transformation_applicator->apply_transformation(std::move(generic_adapted_image), std::move(transformer));
		auto transformed_raw_pixel_values = adapter->adapt_to_raw(std::move(transformed_adapted_image));

		file_writer->write_to_file(transformed_raw_pixel_values, OUTFILENAME);
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