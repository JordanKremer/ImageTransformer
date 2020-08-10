#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include "../ImageTransformer/BmpLoader.cpp"
#include "..//ImageTransformer/BmpData.cpp"

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
		
		TEST_METHOD(BmpLoader_instantiate)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			Assert::AreEqual(FILENAME, Bmp.getFileName());
		}

		//Attempts to load a file that doesn't exist
		TEST_METHOD(BmpLoader_Load_Nonexistant_File)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			try {
				std::cout << "test";
				auto myData = Bmp.Load();
			}
			catch (const char* msg)
			{	
				std::cout << msg;
				Assert::AreEqual("Failure to open file / File doesn't exist", msg);
			}
			
		}

		TEST_METHOD(BmpLoader_Load_Existant_File)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			try {
				std::cout << "test";
				auto myData = Bmp.Load();
			}
			catch (const char* msg)
			{
				std::cout << msg;
				Assert::AreEqual("Failure to open file / File doesn't exist", msg);
			}
		}

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
