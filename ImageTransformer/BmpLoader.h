#pragma once
#include "Loader.h"
#include <string>
#include "Data.h"
#include "BmpHeaderInfo.h"
#include <memory>
class BmpLoader :
	public Loader
{
public:

	BmpLoader(const std::string FILENAME);
	std::string getFileName()const;
	std::shared_ptr<Data> Load();
	std::shared_ptr<BmpHeaderInfo> getBmpHeader(int compression); //get the correct header object


private:
	std::string _FILENAME;
};

