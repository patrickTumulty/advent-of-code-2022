
#include "aoc_2022.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct File
{
    std::string name;
    int size;
};

struct Dir
{
    std::string name;
    Dir* parentDir = nullptr;
    std::map<std::string, Dir> childDirectoriesMap;
    std::vector<File> files;
    int size{};
};

void printFileTree(Dir& dir, int indent)
{
    std::string indentStr;
    for (int i = 0; i < indent - 1; i++)
        indentStr.append("\t");
    std::cout << indentStr << "📁 " << dir.name << " : " << dir.size <<std::endl;
    indentStr.append("\t");
    for (const auto& file : dir.files)
    {
        std::cout << indentStr << "📄 " << file.name << " : " << file.size << std::endl;
    }
    int newIndent = indent + 1;
    for (auto& [childDirName, childDir] : dir.childDirectoriesMap)
    {
        printFileTree(childDir, newIndent);
    }
}

void getDirectoriesBelowMaxSize(Dir& dir, std::vector<Dir*>& dirs, int maxSize)
{
    if (dir.size <= maxSize)
    {
        dirs.push_back(&dir);
    }

    for (auto& [childDirName, childDir] : dir.childDirectoriesMap)
    {
        getDirectoriesBelowMaxSize(childDir, dirs, maxSize);
    }
}

void calculateDirectorySizes(Dir& dir)
{
    for (auto& [childDirName, childDir] : dir.childDirectoriesMap)
    {
        calculateDirectorySizes(childDir);
    }

    for (auto& file : dir.files)
    {
        dir.size += file.size;
    }

    for (auto& [childDirName, childDir] : dir.childDirectoriesMap)
    {
        dir.size += childDir.size;
    }
}

void findSmallestDirToDelete(Dir& dir, Dir **smallest, int minimumRequiredSpace, int currentUnusedSpace)
{
    if (*smallest == nullptr)
    {
        *smallest = &dir;
    }
    else if ((dir.size + currentUnusedSpace) >= minimumRequiredSpace)
    {
        *smallest = (*smallest)->size > dir.size ? &dir : *smallest;
    }

    for (auto& [childDirName, childDir] : dir.childDirectoriesMap)
    {
        findSmallestDirToDelete(childDir, smallest, minimumRequiredSpace, currentUnusedSpace);
    }
}

void runDay7()
{
    Dir root = {};
    root.parentDir = nullptr;
    root.name = "root";

    std::vector<std::string> lines;

    file2Vector("../data/dir.txt", lines);

    Dir* currentDir = nullptr;
    std::vector<std::string> tokens;
    for (const auto& line : lines)
    {
        tokens.clear();
        splitString(line, " ", tokens);
        if (tokens[0] == "$")
        {
            if (tokens[1] == "cd")
            {
                std::string dirname = tokens[2];
                if (dirname == "/")
                {
                    currentDir = &root;
                }
                else if (dirname == "..")
                {
                    currentDir = currentDir->parentDir;
                }
                else
                {
                    currentDir = &currentDir->childDirectoriesMap[dirname];
                }
            }
            continue;
        }
        else
        {
            if (tokens[0] == "dir")
            {
                currentDir->childDirectoriesMap.insert(
                    std::pair<std::string, Dir>(tokens[1], (Dir){tokens[1], currentDir}));
            }
            else
            {
                currentDir->files.emplace_back((File){tokens[1], std::stoi(tokens[0])});
            }
        }
    }

    calculateDirectorySizes(root);

    printFileTree(root, 1);

    std::vector<Dir*> dirs;

    getDirectoriesBelowMaxSize(root, dirs, 100000);

    int total = 0;
    for (auto dir : dirs)
    {
        total += dir->size;
    }

    std::cout << "Total: " << total << std::endl;

    std::cout << "Used Space   : " << root.size << std::endl;
    std::cout << "Unused Space : " << 70000000 - root.size << std::endl;

    Dir *smallestDir = nullptr;
    findSmallestDirToDelete(root, &smallestDir, 30000000, 70000000 - root.size);

    if (smallestDir == nullptr)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    std::cout << "Smallest Dir: " << smallestDir->name << " : " << smallestDir->size << std::endl;
}