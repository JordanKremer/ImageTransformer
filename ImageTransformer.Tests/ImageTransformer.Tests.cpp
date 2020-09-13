#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>


//#include "../ImageTransformer/BmpLoader.cpp"
#include "..//ImageTransformer/Loader.cpp"
#include "../ImageTransformer/BmpData.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_24Bit.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_32Bit.cpp"
#include "..//ImageTransformer/BmpHeaderFactory.cpp"
#include "../ImageTransformer/Pixel.cpp"
#include "../ImageTransformer/PixelAlpha.cpp"

/*
* Test cases:
Load file: File doesn't exist (what if you don't have permission or some other file error?)
Load file: File exists but isn't a valid bitmap (is there more than one case here?)
Load file: File exists and is a valid bitmap:
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
			Loader _loader;

			auto func = [&_loader, &FILENAME] { _loader.Load(FILENAME); };

			Assert::ExpectException<std::ios_base::failure>(func);
		}
		

		TEST_METHOD(Loader_DoesItLoadBytes)
		{
			const std::string FILENAME = "../bear1_32.bmp";
			Loader _loader;
			
			auto data = _loader.Load(FILENAME);

			bool hasBytes = false;
			
			if (data.size() > 0) {
				hasBytes = true;
			}

			Assert::AreEqual(true, hasBytes);
		}

		//USE BELOW FOR THE BMP ADAPTER
		/*
		//The BMP ID is the first two bytes in a bmp file
		//"BM" is tested for
		TEST_METHOD(BmpLoader_Load_ExistantFile_InvalidBMP_ID)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\test.txt";
			BmpLoader Bmp(FILENAME);

			auto func = [&] { Bmp.Load(); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}
		*/

		//Test exception in getBmpHeader() that enforces lower boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsLower)
		{

			
			BmpHeaderFactory fac;
			std::vector<unsigned char> tmp;
			
			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp, -1); };
			

			Assert::ExpectException<std::runtime_error>(func);
			
		}


		//Test exception in getBmpHeader() that enforces upper boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsUpper)
		{

			BmpHeaderFactory fac;
			std::vector<unsigned char> tmp;

			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp, 5); };


			Assert::ExpectException<std::runtime_error>(func);
		}

		
		//Test if header vector data is properly copied to the constructor in a BmpHeaderInfo_24Bit object
		TEST_METHOD(BmpHeaderInfo_24Bit_isHeaderDataCopiedCorrectly)
		{
			
			std::vector<unsigned char> testData{0, 5, 10, 20, 30};

			BmpHeaderInfo_24Bit testHeader(testData);

			auto iterStart = testHeader.getHeaderBegin();
			auto iterEnd = testHeader.getHeaderEnd();

			int count = 0;
			for (iterStart; iterStart != iterEnd; ++iterStart) {
				Assert::AreEqual(testData[count], *iterStart);
				++count;
			}
		}



		TEST_METHOD(BmpHeaderInfo_24Bit_getCompressionZeroCheck)
		{
			std::vector<unsigned char> testData{0};

			BmpHeaderInfo_24Bit testHeader(testData);

			Assert::AreEqual(0, testHeader.getCompression());
		}


		TEST_METHOD(Pixel_Constructor)
		{
			Pixel pixel(1, 2, 3);

			Assert::AreEqual(1, pixel.getRed());
			Assert::AreEqual(2, pixel.getGreen());
			Assert::AreEqual(3, pixel.getBlue());
		}

		TEST_METHOD(PixelAlpha_Constructor)
		{
			PixelAlpha pixel(1, 2, 3, 4);

			Assert::AreEqual(1, pixel.getRed());
			Assert::AreEqual(2, pixel.getGreen());
			Assert::AreEqual(3, pixel.getBlue());
			Assert::AreEqual(4, pixel.getAlpha());
		}

		//TODO: Change all of these bmploader tests to loader tests, will need to change asserts to 
//reflect the design changes

		//
		//https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapcoreheader
		//can use link for making new tests to check header

		/*
		
		Loader:
			*check single black pixekl
			*check multiple black pixels
			*check other colors
		
		*/

	};
}
