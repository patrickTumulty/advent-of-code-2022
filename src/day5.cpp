
#include "aoc_2022.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

void printMatrix(std::vector<std::vector<char>>& stackMatrix)
{
    for (auto& row : stackMatrix)
    {
        for (char element : row)
        {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
}

void getStacksAndInstructions(std::vector<std::string>& lines, std::vector<std::string>& stacks,
                              std::vector<std::string>& instructions)
{
    bool isInstruction = false;
    while (!lines.empty())
    {
        auto firstItem = std::string(*lines.begin());
        lines.erase(lines.begin());

        if (isNullOrWhiteSpace(firstItem))
        {
            isInstruction = true;
            continue;
        }

        if (isInstruction)
            instructions.push_back(firstItem);
        else
            stacks.push_back(firstItem);
    }
}

void parseStackMatrixFromLines(std::vector<std::string>& stacks, std::vector<std::vector<char>>& stackMatrix)
{
    int rowIdx = 0;
    for (const auto& row : stacks)
    {
        stackMatrix.emplace_back();
        for (int i = 0; i < row.size(); i += 4)
        {
            char value = row[i + 1];
            stackMatrix[rowIdx].push_back(value);
        }
        rowIdx++;
    }
    stackMatrix.pop_back();
}

class DSWrapper
{
  public:
    virtual int size() = 0;

    virtual void push(char c) = 0;

    virtual char pop() = 0;
};

class QueueWrapper : public DSWrapper
{
  public:
    explicit QueueWrapper(std::queue<char> q) : q(std::move(q))
    {
    }

    int size() override
    {
        return q.size();
    }

    void push(char c) override
    {
        q.push(c);
    }

    char pop() override
    {
        char value = q.front();
        q.pop();
        return value;
    }

  private:
    std::queue<char> q;
};

class StackWrapper : public DSWrapper
{
  public:
    explicit StackWrapper(std::stack<char> s) : s(std::move(s))
    {
    }

    int size() override
    {
        return s.size();
    }

    void push(char c) override
    {
        s.push(c);
    }

    char pop() override
    {
        char value = s.top();
        s.pop();
        return value;
    }

  private:
    std::stack<char> s;
};

void getFromColumn(int columnIndex, int amount, std::vector<std::vector<char>>& matrix, DSWrapper* ds)
{
    for (auto& row : matrix)
    {
        char* element = &row[columnIndex];
        if (*element == ' ')
            continue;
        ds->push(*element);
        row[columnIndex] = ' ';
        if (ds->size() == amount)
            break;
    }
}

void addToColumn(int columnIndex, std::vector<std::vector<char>>& matrix, DSWrapper* ds)
{
    int numberOfColumns = matrix[0].size();
    int rowIndex = matrix.size() - 1;
    while (ds->size() != 0)
    {
        if (rowIndex < 0)
        {
            auto newRow = std::vector<char>(numberOfColumns);
            std::fill(newRow.begin(), newRow.end(), ' ');
            matrix.insert(matrix.begin(), std::move(newRow));
            rowIndex = 0;
        }

        char* element = &matrix[rowIndex--][columnIndex];
        if (*element == ' ')
        {
            *element = ds->pop();
        }
    }
}

void copyMatrix(const std::vector<std::vector<char>>& original, std::vector<std::vector<char>>& copy)
{
    for (const auto& row : original)
    {
        std::vector<char> rowCopy;
        rowCopy.insert(rowCopy.begin(), row.begin(), row.end());
        copy.push_back(std::move(rowCopy));
    }
}

void processStacks(std::vector<std::vector<char>>& stackMatrix, std::vector<std::string>& instructions, DSWrapper* ds)
{
    for (const auto& instruction : instructions)
    {
        std::vector<std::string> tokens;
        splitString(instruction, " ", tokens);

        int amount = std::stoi(tokens[1]);
        int from = std::stoi(tokens[3]) - 1;
        int to = std::stoi(tokens[5]) - 1;

        getFromColumn(from, amount, stackMatrix, ds);
        addToColumn(to, stackMatrix, ds);
    }
}

void runDay5()
{
    std::vector<std::string> lines;

    file2Vector(std::string("../data/supply_stack.txt"), lines);

    std::vector<std::string> stacks;
    std::vector<std::string> instructions;

    getStacksAndInstructions(lines, stacks, instructions);

    std::vector<std::vector<char>> stackMatrix;
    parseStackMatrixFromLines(stacks, stackMatrix);

    std::cout << "Part 1: Queue" << std::endl;

    std::vector<std::vector<char>> p1Mat;
    copyMatrix(stackMatrix, p1Mat);
    QueueWrapper queueWrapper = QueueWrapper(std::queue<char>());
    DSWrapper* qw = &queueWrapper;
    processStacks(p1Mat, instructions, qw);
    printMatrix(p1Mat);

    std::cout << "Part 2: Stack" << std::endl;

    std::vector<std::vector<char>> p2Mat;
    copyMatrix(stackMatrix, p2Mat);
    StackWrapper stackWrapper = StackWrapper(std::stack<char>());
    DSWrapper* sw = &stackWrapper;
    processStacks(p2Mat, instructions, sw);
    printMatrix(p2Mat);
}
