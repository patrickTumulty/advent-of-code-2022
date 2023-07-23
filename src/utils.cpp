
#include "utils.h"

bool isNullOrWhiteSpace(const std::string& s)
{
    return s.empty() || std::all_of(s.begin(), s.end(), [](char c) { return std::isspace(c); });
}
