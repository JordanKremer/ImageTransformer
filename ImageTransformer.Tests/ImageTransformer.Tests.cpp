#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>

//make sure to include each of these when testing other wise a linker error will be thrown
#include "../ImageTransformer/BmpLoader.cpp"
#include "../ImageTransformer/BmpData.cpp"
#include "..//ImageTransformer/BmpHeaderInfo.cpp"
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

		
		TEST_METHOD(BmpLoader_Load_ExistantFile_InvalidBMP_ID)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\test.txt";
			BmpLoader Bmp(FILENAME);

			auto func = [&] { Bmp.Load(); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}

		/*
		//http://entropymine.com/jason/bmpsuite/bmpsuite/html/bmpsuite.html  -->contains bump images of different types
		//only allow for compression of 0 and 3
		TEST_METHOD(BmpLoader_Compression_Check)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\"; //find one with 2 compression flag, or 1
			BmpLoader Bmp(FILENAME);

			auto func = [&] { Bmp.Load(); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}
		*/


		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsLower)
		{

			
			BmpHeaderFactory fac;
			
			auto func = [&fac] {fac.getBmpHeader(-1); };
			

			Assert::ExpectException<std::runtime_error>(func);
			
		}

		
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsUpper)
		{

			BmpHeaderFactory fac;

			auto func = [&fac] {fac.getBmpHeader(5); };


			Assert::ExpectException<std::runtime_error>(func);
		}
		
		//https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapcoreheader
		//can use link for making new tests to check header

//Cannot change return types for each test

/*
given: I try to load a bitmap
when: the filename is wrong
then: what kind of indicator do i want
*/
/*
load simple image say 4x4 black dots, then when looking at the image object
data in the test, it should reflect 255, 255, 255  etc. That will be used to validate it.


*/

		/*
		Test every line (behavior, typically a line or a few lines)
			of code --> including in the loader --> write a test for each line of code you are going
		to write

		for instance, when looking at a file, write a test to find it
		write a test if it has a single pixel
		what questions can you ask about the data structure that was built from the loaded file, 
		
		*/

	};
}
