
#include "aoc_2022.h"
#include "utils.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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
    int maxCalories = INT32_MIN;
    for (auto calories : elfCalories)
    {
        maxCalories = std::max(maxCalories, sum(&calories));
    }
    return maxCalories;
}

int getTop3Calories(std::vector<std::vector<int>> elfCalories)
{
    std::vector<int> sums = std::vector<int>();

    for (auto calories : elfCalories)
    {
        sums.push_back(sum(&calories));
    }

    std::sort(sums.begin(), sums.end());
    int len = sums.size();
    return sums[len - 1] + sums[len - 2] + sums[len - 3];
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

    std::cout << "Part 1: Max Calories: " << maxCalories << std::endl;

    int maxThreeCalories = getTop3Calories(elvesCalories);

    std::cout << "Part 2: Max Calories: " << maxThreeCalories << std::endl;
}
