
#include "aoc_2022.h"
#include "utils.h"
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

void incrementTreeScore(std::vector<std::vector<int>>& visibleScore, const std::stack<int>& visibleStack, int i, int j)
{
    int* score;
    if (!visibleStack.empty())
    {
        score = &visibleScore[i][j];
        *score = *score == 0 ? (int)visibleStack.size() : *score * (int)visibleStack.size();
    }
}

void emptyStack(std::stack<int>& s)
{
    while (!s.empty())
        s.pop();
}

void evaluateTree(std::stack<int>& visibleStack, int tree)
{
    if (visibleStack.empty())
    {
        visibleStack.push(tree);
    }
    else if (tree >= visibleStack.top())
    {
        visibleStack.push(tree);
    }
}

void checkRows(const std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& visible)
{
    std::stack<int> forwardStack;
    std::stack<int> reverseStack;

    for (int i = 0; i < grid.size(); i++)
    {
        emptyStack(forwardStack);
        emptyStack(reverseStack);
        int rowLength = grid[i].size();
        for (int j = 0; j < rowLength; j++)
        {
            int value = grid[i][j];
            if (forwardStack.empty() || forwardStack.top() < value)
            {
                forwardStack.push(value);
                visible[i][j] = 1;
            }

            int rvalue = grid[i][(rowLength - 1) - j];
            if (reverseStack.empty() || reverseStack.top() < rvalue)
            {
                reverseStack.push(rvalue);
                visible[i][(rowLength - 1) - j] = 1;
            }
        }
    }
}

void checkCols(const std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& visible)
{
    std::stack<int> forwardStack;
    std::stack<int> reverseStack;

    for (int i = 0; i < grid[0].size(); i++)
    {
        emptyStack(forwardStack);
        emptyStack(reverseStack);
        int colLength = grid.size();
        for (int j = 0; j < colLength; j++)
        {
            int value = grid[j][i];
            if (forwardStack.empty() || forwardStack.top() < value)
            {
                forwardStack.push(value);
                visible[j][i] = 1;
            }

            int rvalue = grid[(colLength - 1) - j][i];
            if (reverseStack.empty() || reverseStack.top() < rvalue)
            {
                reverseStack.push(rvalue);
                visible[(colLength - 1) - j][i] = 1;
            }
        }
    }
}

void printGrid(const std::vector<std::vector<int>>& grid)
{
    for (const auto& row : grid)
    {
        for (int item : row)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

void initAndFillGrid(const std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& zeroGrid, int value)
{
    for (const auto& row : grid)
    {
        std::vector<int> rowVec = std::vector<int>(row.size());
        std::fill(rowVec.begin(), rowVec.end(), value);
        zeroGrid.push_back(std::move(rowVec));
    }
}

void runPart2(std::vector<std::vector<int>>& grid)
{
    std::vector<std::vector<int>> visibleScore;
    initAndFillGrid(grid, visibleScore, 0);

    std::stack<int> visibleStack;
    int counter = 0;

    int highestScore = INT32_MIN;

    for (int i = 1; i < grid.size() - 1; i++)
    {
        for (int j = 1; j < grid[i].size() - 1; j++)
        {
            int currentTree = grid[i][j];

            // Forward
            emptyStack(visibleStack);
            counter = j + 1;

            while (counter < grid[i].size())
            {
                int tree = grid[i][counter];
                visibleStack.push(tree);
                if (tree >= currentTree)
                {
                    break;
                }

                counter++;
            }
            incrementTreeScore(visibleScore, visibleStack, i, j);

            // Backward
            emptyStack(visibleStack);
            counter = j - 1;
            while (counter > -1)
            {
                int tree = grid[i][counter];
                visibleStack.push(tree);

                if (tree >= currentTree)
                {
                    break;
                }

                counter--;
            }
            incrementTreeScore(visibleScore, visibleStack, i, j);

            // Up
            emptyStack(visibleStack);
            counter = i - 1;
            while (counter > -1)
            {
                int tree = grid[counter][j];
                visibleStack.push(tree);

                if (tree >= currentTree)
                {
                    break;
                }

                counter--;
            }
            incrementTreeScore(visibleScore, visibleStack, i, j);

            // Down
            emptyStack(visibleStack);
            counter = i + 1;
            while (counter < grid.size())
            {
                int tree = grid[counter][j];
                visibleStack.push(tree);

                if (tree >= currentTree)
                {
                    break;
                }

                counter++;
            }
            incrementTreeScore(visibleScore, visibleStack, i, j);

            highestScore = std::max(highestScore, visibleScore[i][j]);
        }
    }

    printGrid(visibleScore);

    std::cout << "Highest Visibility Score: " << highestScore << std::endl;
}

void runDay8()
{
    std::vector<std::string> lines;
    file2Vector("../data/trees.txt", lines);

    std::vector<std::vector<int>> grid;
    int i = 0;
    for (auto const& line : lines)
    {
        grid.emplace_back();
        for (char c : line)
            grid[i].push_back(c - '0');
        i++;
    }

    //    printGrid(grid);

    std::vector<std::vector<int>> visible;
    initAndFillGrid(grid, visible, 0);

    checkRows(grid, visible);
    checkCols(grid, visible);

    printGrid(visible);

    int count = 0;
    for (const auto& row : visible)
        for (int element : row)
            count += element;

    std::cout << "Total Visible: " << count << std::endl;

    std::cout << "Part: 2" << std::endl;

    runPart2(grid);
}
