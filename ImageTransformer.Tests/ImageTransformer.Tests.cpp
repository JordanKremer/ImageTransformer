#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>


#include "../ImageTransformer/BmpLoader.cpp"
#include "../ImageTransformer/BmpData.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_24Bit.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_32Bit.cpp"
#include "..//ImageTransformer/BmpHeaderFactory.cpp"

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


		TEST_METHOD(BmpLoader_Filename)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			Assert::AreEqual(FILENAME, Bmp.getFileName());
		}


		//Attempts to load a file that doesn't exist
		TEST_METHOD(BmpLoader_Load_NonexistantFile)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);
		
			auto func = [&] { Bmp.Load(); };
			
			Assert::ExpectException<std::ios_base::failure>(func); 
		}

		//The BMP ID is the first two bytes in a bmp file
		//"BM" is tested for
		TEST_METHOD(BmpLoader_Load_ExistantFile_InvalidBMP_ID)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\test.txt";
			BmpLoader Bmp(FILENAME);

			auto func = [&] { Bmp.Load(); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}


		//Test exception in getBmpHeader() that enforces lower boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsLower)
		{

			
			BmpHeaderFactory fac;
			std::vector<char*> tmp;
			
			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp, -1); };
			

			Assert::ExpectException<std::runtime_error>(func);
			
		}


		//Test exception in getBmpHeader() that enforces upper boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsUpper)
		{

			BmpHeaderFactory fac;
			std::vector<char*> tmp;

			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp, 5); };


			Assert::ExpectException<std::runtime_error>(func);
		}


		//Make sure getCompression is returning the correct number
		TEST_METHOD(BmpHeaderInfo_24Bit_getCompressionZeroCheck)
		{
			std::vector<char*> testData;
			int compression = 0;

			BmpHeaderInfo_24Bit testHeader(testData, compression);

			Assert::AreEqual(0, testHeader.getCompression());
		}


		//Test if testHeader constructor throws exception if invalid compression value is used as arg
		TEST_METHOD(BmpHeaderInfo_24Bit_ConstructorDoesNonZeroThrowException)
		{

			auto func = [] {
			
				std::vector<char*> testData; //No need to load vector
				int compression = -1;

				BmpHeaderInfo_24Bit testHeader(testData, compression); 
			
			};
			Assert::ExpectException<std::runtime_error>(func);
		}

		
		//Test if header vector data is properly copied to the constructor in a BmpHeaderInfo_24Bit object
		TEST_METHOD(BmpHeaderInfo_24Bit_isHeaderDataCopiedCorrectly)
		{
			
			std::vector<char*> testData;
			int compression = 0;

			testData.push_back((char*)0);
			testData.push_back((char*)5);
			testData.push_back((char*)10);
			
			BmpHeaderInfo_24Bit testHeader(testData, compression);

			const char* tmp = testHeader.getByte(1);

			Assert::AreEqual(testData[0], testHeader.getByte());

		}






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
