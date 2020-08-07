#include "pch.h"
#include "CppUnitTest.h"
#include <string>

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

		TEST_METHOD(Data_Instantiate)
		{
			Data* Data = new BmpData();

		}

		TEST_METHOD(BmpLoader_Load)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			/*
			load simple image say 4x4 black dots, then when looking at the image object
			data in the test, it should reflext 255, 255, 255  etc. That will be used to validate it.


			*/
		}

		/*
		Test every line of code --> including in the loader --> write a test for each line of code you are going
		to write

		for instance, when looking at a file, write a test to find it
		write a test if it has a single pixel
		what questions can you ask about the data structure that was built from the loaded file, 
		
		*/

	};
}
