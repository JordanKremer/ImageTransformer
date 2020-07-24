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
			std::string FILENAME = "../someFile";
			BmpLoader Bmp(FILENAME);
			Bmp.getFileName();

			Assert::AreEqual("../someFile", Bmp.getFileName());
		}
	};
}
