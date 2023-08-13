
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

bool isNullOrWhiteSpace(const std::string& s);
void file2Vector(const std::string& filename, std::vector<std::string>& vec);
void printVec(std::vector<std::string>& vec);
void splitString(std::string s, const std::string& delimiter, std::vector<std::string>& vec);

#endif
