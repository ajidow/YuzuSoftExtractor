#pragma once
#include <string>
#include <iostream>
#include <rapidjson/document.h>

class JSON_Processor {
public:
	std::string readfile(const char* filename);
	int ParseJson(const char* jsonstr);
};