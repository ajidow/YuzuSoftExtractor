#pragma once
#include <string>
#include <iostream>
#include <rapidjson/document.h>
#include <string>
#include <sstream>

class JSONProcessor {
public:
	std::string readfile(const char* filename);
	int ParseJson(const char* jsonstr);
	std::string nameInJson[501];
	rapidjson::Document d;
private:
	
};