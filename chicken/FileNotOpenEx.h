#pragma once
#include "vcruntime_exception.h"
class FileNotOpenEx :
	public std::exception
{
public:
	FileNotOpenEx() {};
	~FileNotOpenEx() {};
};