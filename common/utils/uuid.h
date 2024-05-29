#ifndef PL_COMMON_UTILS_UUID_H
#define PL_COMMON_UTILS_UUID_H

#include <regex>
#include <string>

class UUIDHelper
{
public:
    static bool isUUID(const std::string &uuid_string);

private:
    static std::regex uuid_regex;
};

#endif // PL_COMMON_UTILS_UUID_H