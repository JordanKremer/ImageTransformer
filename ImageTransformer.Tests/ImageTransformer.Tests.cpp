#include "pch.h"
#include "CppUnitTest.h"
#include <string>

#include "../ImageTransformer/BmpLoader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageTransformerTests
{
	TEST_CLASS(ImageTransformerTests)
	{
	public:
		
		TEST_METHOD(BmpLoader1)
		{
			const std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);

			Assert::AreEqual(FILENAME, Bmp.getFileName());
		}
	};
}
