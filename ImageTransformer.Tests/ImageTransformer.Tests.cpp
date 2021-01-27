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



#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include <fstream>

#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)

#include "..//ImageTransformer/Source/loader.cpp"
#include "..//ImageTransformer/Source/writer.cpp"
#include "..//ImageTransformer/Source/bmp_adapter.cpp"
#include "..//ImageTransformer/Source/bmp_header_info.cpp"
#include "..//ImageTransformer/Source/bmp_header_info_32_bit.cpp"
#include "..//ImageTransformer/Source/bmp_header_factory.cpp"
#include "..//ImageTransformer/Source/adapter_factory.cpp"
#include "..//ImageTransformer/Source/applicator.cpp"
#include "../ImageTransformer/Source/pixel.cpp"
#include "..//ImageTransformer/Source/generic_image.cpp"
#include "..//ImageTransformer/Source/rotate180.cpp"
#include "..//ImageTransformer/Source/pixelate.cpp"
#include "..//ImageTransformer/Source/gaussian_blur.cpp"
#include "..//ImageTransformer/Source/cell_shade.cpp"
#include "..//ImageTransformer/Source/grey_scale.cpp"
#include "..//ImageTransformer/Source/scale_up.cpp"
/*
* Test cases:
load file: File doesn't exist (what if you don't have permission or some other file error?)
load file: File exists but isn't a valid bitmap (is there more than one case here?)
load file: File exists and is a valid bitmap:
	A) Single pixel. What can I assert about the object created?
	B) Larger image (say 3x3): Are there additional assertions that now make sense such
		as checking the pixel values match expectations) 
*

dont write code that doesn't explicitly fix the test so you guarantee you don't write code
that isn't tested --> it's possible to write a bunch of code that passes the tests but also does other
things, this is bad.
*/

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageTransformerTests
{
	TEST_CLASS(ImageTransformerTests)
	{
	public:
		
		//TEST_CLASS_INITIALIZE  --> initialize objects so the methods don't have to each time?
		//https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
		//https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=vs-2019#:~:text=A%20lambda%20begins%20with%20the,it%20are%20accessed%20by%20value.


		
		//Attempts to load a file that doesn't exist
		TEST_METHOD(Loader_Load_NonexistantFile)
		{
			const std::string FILENAME = "../someFile";
			loader _loader;

			auto func = [&_loader, &FILENAME] { _loader.load(FILENAME); };

			Assert::ExpectException<std::ios_base::failure>(func);
		}


		TEST_METHOD(Loader_Load_existantFile)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			//Get file size
			std::ifstream in;
			in.open(FILENAME, std::ios::binary);
			in.seekg(0, in.end);
			int fileLength = in.tellg();
			in.seekg(0, in.beg);
			in.close();

			//load file-- vector uses move so by val is ok
			std::vector<unsigned char> data = loader::load(FILENAME);

			//check if they are the same size
			Assert::IsTrue(data.size() == fileLength);
		}




		//USE BELOW FOR THE BMP ADAPTER
		
		//The BMP id is the first two bytes in a bmp file
		//"BM" is tested for
		TEST_METHOD(BmpLoader_InvalidBMP_ID)
		{
			bmp_adapter adapter;
			std::vector<unsigned char> testVec;
			testVec.push_back('a');
			testVec.push_back('b');

			auto func = [&] { adapter.adapt_from_raw(testVec); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}
		

		//The bmpheaders have a minimum size of 54 bytes
		TEST_METHOD(BmpLoader_ValidID_HeaderTooSmall)
		{
			bmp_adapter adapter;
			std::vector<unsigned char> testVec;
			testVec.push_back('B');
			testVec.push_back('M');
			for (int count = 0; count < 60; ++count)
			{
				testVec.push_back(0);
			}

			auto func = [&] { adapter.adapt_from_raw(testVec); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}
		


		//Test exception in get_bmp_header() that enforces lower boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsLower)
		{
			bmp_header_factory fac;
			std::vector<unsigned char> tmp(34, -1);
			
			auto func = [&fac, &tmp] {fac.get_bmp_header(tmp); };

			Assert::ExpectException<std::runtime_error>(func);
			
		}


		
		//Test exception in getBmpHeader() that enforces upper boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsUpper)
		{

			bmp_header_factory fac;
			std::vector<unsigned char> tmp(34, 10);

			auto func = [&fac, &tmp] {fac.get_bmp_header(tmp); };


			Assert::ExpectException<std::runtime_error>(func);
		}

		
		//Test if header vector data is properly copied to the constructor in a BmpHeaderInfo_24Bit object



		TEST_METHOD(AdapterFactory_GetAdapter_NotRecognizedType)
		{
			adapter_factory adapter;
			 
			auto func = [&] {adapter.get_adapter("abc"); };

			Assert::ExpectException<std::runtime_error>(func);
		}



		TEST_METHOD(BmpAdapter_Adapt) 
		{
			bmp_adapter adapter;

			auto adaptedData = adapter.adapt_from_raw(loader::load("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp"));
		}


		TEST_METHOD(BmpHeaderInfo_32Bit_FromFile)
		{
			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";
			auto rawData = loader::load(FILENAME);

			bmp_header_info_32_bit bmpHeader32Bit(rawData);

		}


		//test generic_image 
		TEST_METHOD(DataInitialization_test)
		{
			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";
			loader _loader;

			auto rawData = _loader.load(FILENAME);

			bmp_adapter adapter;

			auto adaptedData = adapter.adapt_from_raw(rawData);
			

		}


		TEST_METHOD(Rotate180_TransformPixels)
		{
			rotate180 r;
			std::vector<unsigned char> dummyHdrData(54, 10);

			//Assuming bmpheader
			uint32_t width = 4;
			uint32_t height = 4;
			auto start = 18;

			//load the raw header byte vector with the width and height from uint_32
			for (int i = 0; i < 4; ++i)
			{
				dummyHdrData[start] = ((unsigned char*) &width)[i]; //width
				dummyHdrData[start + 4] = ((unsigned char*) &height)[i]; //height  
				start++;
			}

			//Build Header
			auto bmp_hdr = new bmp_header_info(dummyHdrData);
			r.set_header(bmp_hdr);


			int size = height * width;
			std::vector<pixel> pixels;  //4x4

			int channel_color = 0;

			//load the pixel vector
			for (int i = 0; i < size; ++i)
			{
				std::vector<unsigned char> channel(3, channel_color);
				pixel p(channel, 3);
				pixels.push_back(p);

				++channel_color;
				if(channel_color > 255)
				{
					channel_color = 0;
				} 
			}

			auto p = r.transform_pixels(pixels);


			delete bmp_hdr;
		}

		TEST_METHOD(Writer_WriteToFile)
		{
			bmp_adapter b;

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			auto load_data = loader::load(FILENAME);

			

			auto adaptedGenericImagedData = b.adapt_from_raw(load_data);

			auto adaptedToRaw = b.adapt_to_raw(std::move(adaptedGenericImagedData));
			writer::write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}

		TEST_METHOD(Rotate180_isImageFlipped)
		{
			writer W;
			loader L;
			bmp_adapter b;
			applicator a;
			auto r = std::make_unique<rotate180> ();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";
			// const std::string FILENAME = TEST_CASE_DIRECTORY + 
			auto loadData = L.load(FILENAME);



			auto adaptedGenericImagedData = b.adapt_from_raw(loadData);
			auto transformedImage = a.apply_transformation(std::move(adaptedGenericImagedData), std::move(r));
			  
			auto adaptedToRaw = b.adapt_to_raw(std::move(transformedImage));
			W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write1.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}

		TEST_METHOD(PixelateTest)
		{
			writer W;
			loader L;
			bmp_adapter b;
			applicator a;
			auto r = std::make_unique<pixelate>();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			auto loadData = L.load(FILENAME);



			auto adaptedGenericImagedData = b.adapt_from_raw(loadData);
			auto transformedImage = a.apply_transformation(std::move(adaptedGenericImagedData), std::move(r));

			auto adaptedToRaw = b.adapt_to_raw(std::move(transformedImage));
			W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write1.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}




		TEST_METHOD(GaussianTest)
		{
			writer W;
			loader L;
			bmp_adapter b;
			applicator a;
			auto r = std::make_unique<gaussian_blur>();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write2.bmp";

			auto loadData = L.load(FILENAME);
			auto adaptedGenericImagedData = b.adapt_from_raw(loadData);
			auto transformedImage = a.apply_transformation(std::move(adaptedGenericImagedData), std::move(r));

			auto adaptedToRaw = b.adapt_to_raw(std::move(transformedImage));
			W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write3.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}



		TEST_METHOD(CellShadeTest)
		{
			writer W;
			loader L;
			bmp_adapter b;
			applicator a;
			auto r = std::make_unique<cell_shade>();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			auto loadData = L.load(FILENAME);
			auto adaptedGenericImagedData = b.adapt_from_raw(loadData);
			auto transformedImage = a.apply_transformation(std::move(adaptedGenericImagedData), std::move(r));

			auto adaptedToRaw = b.adapt_to_raw(std::move(transformedImage));
			W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write4.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}


		TEST_METHOD(GreyScaleTest)
		{
			bmp_adapter b;
			auto r = std::make_unique<grey_scale>();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			auto load_data = loader::load(FILENAME);
			auto adapted_generic_imaged_data = b.adapt_from_raw(load_data);
			auto transformed_image = applicator::apply_transformation(std::move(adapted_generic_imaged_data), std::move(r));
			const auto adapted_to_raw = b.adapt_to_raw(std::move(transformed_image));
			writer::write_to_file(adapted_to_raw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write7.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}



		TEST_METHOD(ScaleUpTest)
		{
			bmp_adapter b;
			auto r = std::make_unique<scale_up>();

			const std::string FILENAME = "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";

			auto load_data = loader::load(FILENAME);
			auto adapted_generic_imaged_data = b.adapt_from_raw(load_data);
			auto transformed_image = applicator::apply_transformation(std::move(adapted_generic_imaged_data), std::move(r));

			const auto adapted_to_raw = b.adapt_to_raw(std::move(transformed_image));
			writer::write_to_file(adapted_to_raw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write7.bmp");
			//auto func = [&] {W.write_to_file(adaptedToRaw, "C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_write.bmp"); };
		}



		TEST_METHOD(test4)
		{
			pixel p1(std::vector<unsigned char>(4, 1), 4);

			pixel p2(std::vector<unsigned char>(4, 2), 4);

			p2 = p2 + p1;
		}



		TEST_METHOD(test5)
		{
			auto p1 = std::make_unique<pixel> (std::vector<unsigned char>(4, 1), 4);
			auto p2 = std::make_unique<pixel> (std::vector<unsigned char>(4, 2), 4);

			*p2 = *p2 + *p1;
		}


	};
}
