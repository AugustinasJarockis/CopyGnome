#include "StringUtils.h"

std::string Trim(std::string str) {
    return Trim(str, " \t\n\r\f\v");
}

std::string Trim(std::string str, const char* toTrim) {
    return TrimStart(TrimEnd(str, toTrim), toTrim);
}

std::string TrimStart(std::string str, const char* toTrim) {
    str.erase(0, str.find_first_not_of(toTrim));
    return str;
}

std::string TrimEnd(std::string str, const char* toTrim) {
    str.erase(str.find_last_not_of(toTrim) + 1);
    return str;
}