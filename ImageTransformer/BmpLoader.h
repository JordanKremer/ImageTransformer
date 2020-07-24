#pragma once
#include "Loader.h"
#include <string>
#include "Data.h"
class BmpLoader :
	public Loader
{
public:
	BmpLoader(std::string FILENAME);
	Data Load();


private:
	std::string _FILENAME;
};

