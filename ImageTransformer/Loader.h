#pragma once
#include "Data.h"
#include <string>
class Loader
{
	virtual Data Load() = 0;
	virtual std::string getFileName() const = 0;
};

