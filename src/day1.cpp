
#include "aoc_2022.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool isNullOrWhiteSpace(const std::string& s)
{
    return s.empty() || std::all_of(s.begin(), s.end(), [](char c) { return std::isspace(c); });
}

std::vector<std::vector<int>> fileToIntVector(std::string filename)
{
    std::vector<std::vector<int>> output;
    std::vector<int> temp;

    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (isNullOrWhiteSpace(line))
        {
            output.push_back(std::move(temp));
            temp = std::vector<int>();
        }
        else
        {
            temp.push_back(std::stoi(line));
        }
    }

    return output;
}

int sum(std::vector<int>* vec)
{
    int sum = 0;
    for (auto value : *vec)
    {
        sum += value;
    }
    return sum;
}

int calorieCounter(std::vector<std::vector<int>> elfCalories)
{
    int maxCalories = INT_MIN;
    for (auto calories : elfCalories)
    {
        maxCalories = std::max(maxCalories, sum(&calories));
    }
    return maxCalories;
}

void runDay1()
{
    // auto elvesCalories = std::vector<std::vector<int>>();

    // elvesCalories.push_back({1000, 2000, 3000});
    // elvesCalories.push_back({4000});
    // elvesCalories.push_back({5000, 6000});
    // elvesCalories.push_back({7000, 8000, 9000});
    // elvesCalories.push_back({10000});

    auto elvesCalories = fileToIntVector("../data/elf_calories.txt");

    int maxCalories = calorieCounter(elvesCalories);

    std::cout << "Max Calories: " << maxCalories << std::endl;
}
