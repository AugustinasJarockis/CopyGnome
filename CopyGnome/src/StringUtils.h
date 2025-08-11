#pragma once

#include <string>

std::string Trim(std::string str);
std::string Trim(std::string str, const char* toTrim);
std::string TrimStart(std::string str, const char* toTrim);
std::string TrimEnd(std::string str, const char* toTrim);