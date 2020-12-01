#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include <fstream>


//#include "../ImageTransformer/BmpLoader.cpp"
#include "..//ImageTransformer/Loader.cpp"
#include "..//ImageTransformer/BmpAdapter.cpp"
#include "..//ImageTransformer/BmpHeaderInfo.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_24Bit.cpp"
#include "..//ImageTransformer/BmpHeaderInfo_32Bit.cpp"
#include "..//ImageTransformer/BmpHeaderFactory.cpp"
#include "../ImageTransformer/Pixel.cpp"
#include "..//ImageTransformer/Data.cpp"
#include "..//ImageTransformer/PixelFactory.cpp"
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

		TEST_METHOD(Loader_Load_existantFile)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\Imags\\bear1_32.bmp";
			Loader _loader;

			auto func = [&_loader, &FILENAME] { _loader.Load(FILENAME); };

			Assert::ExpectException<std::ios_base::failure>(func);
		}
		
		
		TEST_METHOD(Loader_DoesItLoadBytes)
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";
			Loader _loader;
			
			auto data = _loader.Load(FILENAME);

			bool hasBytes = false;
			
			if (data.size() > 0) {
				hasBytes = true;
			}

			Assert::AreEqual(true, hasBytes);
		}



		TEST_METHOD(Loader_DoesLoaderLoadAllBytes) 
		{
			const std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp";
			
			std::ifstream in;

			in.open(FILENAME, std::ios::binary);
			in.seekg(0, in.end);
			int fileLength = in.tellg();

			Loader loader;
			auto data = loader.Load(FILENAME);
			int size = data.size();
			Assert::AreEqual(size, fileLength);
		}



		//USE BELOW FOR THE BMP ADAPTER
		
		//The BMP ID is the first two bytes in a bmp file
		//"BM" is tested for
		TEST_METHOD(BmpLoader_InvalidBMP_ID)
		{
			BmpAdapter adapter;
			std::vector<unsigned char> testVec;
			testVec.push_back('a');
			testVec.push_back('b');

			auto func = [&] { adapter.AdaptFromRaw(testVec); }; //&Bmp also works, but & catches everything in scope

			Assert::ExpectException<std::runtime_error>(func);
		}
		



		//Test exception in getBmpHeader() that enforces lower boundary for compression args
		/*
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsLower)
		{

			
			BmpHeaderFactory fac;
			std::vector<unsigned char> tmp(34, -1);
			
			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp); };
			

			Assert::ExpectException<std::runtime_error>(func);
			
		}


		//Test exception in getBmpHeader() that enforces upper boundary for compression args
		TEST_METHOD(BmpHeaderFactory_isCompressionOutOfBoundsUpper)
		{

			BmpHeaderFactory fac;
			std::vector<unsigned char> tmp(34, 10);

			auto func = [&fac, &tmp] {fac.getBmpHeader(tmp); };


			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(DoesItConvertFromCharToInt)
		{
			int compression;


		}*/

		
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


		/*
		TEST_METHOD(BmpHeaderInfo_24Bit_getCompressionZeroCheck)
		{
			std::vector<unsigned char> testData{0};

			BmpHeaderInfo_24Bit testHeader(testData);

			//Assert::AreEqual(0, testHeader.GetCompression());
		}



		//TODO, crashes after finishing loading data
		TEST_METHOD(GetCompression)
		{
			//load picture

			std::ifstream in;
		
			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for(int i = 0; i < 54; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}


			in.close();

			//then get compression from the data

			BmpHeaderFactory fac;
			

			Assert::AreEqual(3, fac.GetCompression(loadData));
			
		}


		TEST_METHOD(test_convertBytesToInt)
		{
			//load small amount of data, just a few bytes into a vector

			std::ifstream in;

			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for(int i = 0; i < 34; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}

			uint32_t compressionFlag;
			((unsigned char*)& compressionFlag)[0] = loadData[30];
			((unsigned char*)& compressionFlag)[1] = loadData[31];
			((unsigned char*)& compressionFlag)[2] = loadData[32];
			((unsigned char*)& compressionFlag)[3] = loadData[33];

			int a = compressionFlag;
			Assert::AreEqual(3, a);

			in.close();
		}

		TEST_METHOD(BmpHeaderInfo_ThrowExceptionWhenLoadDataVectorIsTooSmall)
		{
			std::ifstream in;

			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.seekg(0, in.end);
			int end = in.tellg();
			in.seekg(0, in.beg);


			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for (int i = 0; i < 30; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}

			bool throwException = false;

			try {
				BmpHeaderInfo bmpHeader(loadData);
			}
			catch(std::length_error){
				throwException = true;
			}

			Assert::IsTrue(throwException);

		}


		TEST_METHOD(BmpHeaderInfo_OperatorEqual)
		{
			std::ifstream in;

			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.seekg(0, in.end);
			int end = in.tellg();
			in.seekg(0, in.beg);


			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for (int i = 0; i < end; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}

			BmpHeaderInfo bmpHeader1(loadData);
			BmpHeaderInfo bmpHeader2;
			

			//if we use BmpheaderInfo bmpheader2 = bmpHeader1
			//then it will use the copy constructor instead
			bmpHeader2 = bmpHeader1;

			Assert::AreEqual(bmpHeader1.GetCompression(), bmpHeader2.GetCompression());
			Assert::AreEqual(bmpHeader1.GetWidth(), bmpHeader2.GetWidth());
		}

		TEST_METHOD(BmpHeaderInfo_GetCompression)
		{
			std::ifstream in;

			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.seekg(0, in.end);
			int end = in.tellg();
			in.seekg(0, in.beg);


			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for (int i = 0; i < end; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}

			BmpHeaderInfo bmpHeader(loadData);

			const uint32_t compression = bmpHeader.GetCompression();
			uint32_t expected = 3;
			Assert::AreEqual(expected, bmpHeader.GetCompression());
			
		}


		TEST_METHOD(Data_ConstructorFromHeader_BmpHeaderInfo_32Bit_GetCompression)
		{
			std::ifstream in;

			in.open("C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp", std::ios::binary);

			in.seekg(0, in.end);
			int end = in.tellg();
			in.seekg(0, in.beg);


			in.exceptions(in.failbit);
			unsigned char dataByte;
			std::vector<unsigned char> loadData;
			for (int i = 0; i < end; ++i)
			{
				in.read((char*)& dataByte, 1);
				loadData.push_back(dataByte);
			}

			BmpHeaderFactory fac;


			//using a 32bit header with this image
			Data testData(loadData, fac.getBmpHeader(loadData));
			
			Assert::AreEqual(3, testData.GetCompression());
		}



		//TEST FOR ALL PIXEL TYPES (1 - 4 channels, depending on bit count)
		TEST_METHOD(PixelFactory_GetPixel)
		{
			PixelFactory fac;

			int bitsPerPixel = 1; //24 bit image
			int dataIdx = 0;
			std::vector<unsigned char> data;

			//basic rgb data for a 24 bit pixel
			data.push_back(100);
			Pixel pixelChannel = fac.GetPixel(bitsPerPixel, data, dataIdx);


			data.push_back(100);
			bitsPerPixel = 4;
			Pixel pixel2channel_1 = fac.GetPixel(bitsPerPixel, data, dataIdx);

			bitsPerPixel = 8;
			Pixel pixel2channel_2 = fac.GetPixel(bitsPerPixel, data, dataIdx);

			data.push_back(100);
			bitsPerPixel = 16;
			Pixel pixel3channel_1 = fac.GetPixel(bitsPerPixel, data, dataIdx);

			bitsPerPixel = 24;
			Pixel pixel3channel_2 = fac.GetPixel(bitsPerPixel, data, dataIdx);

			data.push_back(100);
			bitsPerPixel = 32;
			Pixel pixel4channel = fac.GetPixel(bitsPerPixel, data, dataIdx);
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
