#pragma once
#include "Data.h"
#include <string>
class Loader
{
	virtual Data Load(std::string FILENAME) = 0;
};

