#pragma once
#include "Loader.h"
#include <string>
#include "Data.h"
class BmpLoader :
	public Loader
{
public:

	BmpLoader(const std::string FILENAME);
	std::string getFileName()const;


private:
	std::string _FILENAME;
};

