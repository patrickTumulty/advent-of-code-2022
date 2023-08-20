
#include "utils.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

bool isNullOrWhiteSpace(const std::string& s)
{
    return s.empty() || std::all_of(s.begin(), s.end(), [](char c) { return std::isspace(c); });
}

void file2Vector(const std::string& filename, std::vector<std::string>& vec)
{
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        vec.push_back(line);
    }
}

void printVec(std::vector<std::string>& vec)
{
    for (const auto& line : vec)
        std::cout << line << std::endl;
}

void splitString(std::string s, const std::string& delimiter, std::vector<std::string>& vec)
{
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        vec.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    vec.push_back(s);
}
