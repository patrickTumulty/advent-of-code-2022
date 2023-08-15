
#include "aoc_2022.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

void runDay6()
{
    std::vector<std::string> lines;

    file2Vector(std::string("../data/signal_data.txt"), lines);

    int counter = 0;
    int messageLength = 14;

    for (const auto& line : lines)
    {
        counter = 0;
        std::queue<char> items;
        std::set<char> signal;
        std::map<char, int> charCount;

        for (char c : line)
        {
            items.push(c);
            signal.insert(c);
            if (charCount.contains(c))
            {
                charCount[c]++;
            }
            else
            {
                charCount.insert(std::pair<char, int>(c, 1));
            }

            counter++;

            if (signal.size() == messageLength)
            {
                std::cout << line << " : " << counter << std::endl;
                break;
            }

            if (items.size() == messageLength)
            {
                char front = items.front();
                charCount[items.front()]--;
                items.pop();

                if (front != c && charCount[front] == 0)
                {
                    signal.erase(front);
                }
            }
        }
    }
}