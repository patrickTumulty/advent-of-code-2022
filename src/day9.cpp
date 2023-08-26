

#include "aoc_2022.h"
#include "utils.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define MAX_DISTANCE 1.414214f

struct State
{
    std::set<int> visitedLocations;
    int hrow = 0;
    int hcol = 0;
    int trow = 0;
    int tcol = 0;
};

struct Link
{
    int row = 0;
    int col = 0;
};

struct State10Link
{
    std::set<int> visitedLocations;
    int hrow = 0;
    int hcol = 0;
    Link links[9];
};

float getDistance(int x1, int y1, int x2, int y2)
{
    float d1 = (float)(x2 - x1);
    float d2 = (float)(y2 - y1);
    return std::sqrt((d1 * d1) + (d2 * d2));
}

void moveHead(State& state, char direction, int spaces)
{
    int* movementVector = nullptr;
    int movementDirection = 1;
    switch (direction)
    {
        case 'U':
            movementVector = &state.hcol;
            movementDirection = 1;
            break;
        case 'D':
            movementVector = &state.hcol;
            movementDirection = -1;
            break;
        case 'L':
            movementVector = &state.hrow;
            movementDirection = -1;
            break;
        case 'R':
            movementVector = &state.hrow;
            movementDirection = 1;
            break;
    }

    for (int i = 0; i < spaces; i++)
    {
        int hrowPrev = state.hrow;
        int hcolPrev = state.hcol;

        *movementVector += movementDirection;

        float distance = getDistance(state.hrow, state.hcol, state.trow, state.tcol);
        if (distance > MAX_DISTANCE)
        {
            int location = 0;
            location |= (state.trow & 0xFFFF);
            location |= ((state.tcol & 0xFFFF) << 16);
            state.visitedLocations.insert(location);

            state.tcol = hcolPrev;
            state.trow = hrowPrev;
        }
    }
}

void move(int x1, int y1, int x2, int y2)
{

}

void moveHead2(State10Link& state, char direction, int spaces)
{
    int* movementVector = nullptr;
    int movementDirection = 1;
    switch (direction)
    {
        case 'U':
            movementVector = &state.hcol;
            movementDirection = 1;
            break;
        case 'D':
            movementVector = &state.hcol;
            movementDirection = -1;
            break;
        case 'L':
            movementVector = &state.hrow;
            movementDirection = -1;
            break;
        case 'R':
            movementVector = &state.hrow;
            movementDirection = 1;
            break;
    }

    for (int i = 0; i < spaces; i++)
    {
        int hrowPrev = state.hrow;
        int hcolPrev = state.hcol;

        *movementVector += movementDirection;

        int leaderRow = state.hrow;
        int leaderCol = state.hcol;
        int temp = 0;

        for (int i = 0; i < 9; i++)
        {
            Link *link = &state.links[i];

            float distance = getDistance(leaderRow, leaderCol, link->row, link->col);
            if (distance > MAX_DISTANCE)
            {
                if (i == 8)
                {
                    int location = 0;
                    location |= (link->row & 0xFFFF);
                    location |= ((link->col & 0xFFFF) << 16);
                    state.visitedLocations.insert(location);
                }

                temp = link->col;
                link->col = hcolPrev;
                hcolPrev = temp;

                temp = link->row;
                link->row = hrowPrev;
                hrowPrev = temp;
            }

            leaderRow = link->row;
            leaderCol = link->col;
        }
        // printf("%c %d : %zu\n", direction, spaces, state.visitedLocations.size());
    }
}

void runDay9()
{
    std::vector<std::string> lines;
    file2Vector("../data/bridge_test2.txt", lines);

    State state;

    State10Link state10Link;

    for (auto& line : lines)
    {
        std::vector<std::string> tokens;
        splitString(line, " ", tokens);

        char direction = tokens[0].c_str()[0];
        int spaces = std::stoi(tokens[1]);

        moveHead2(state10Link, direction, spaces);
        // moveHead(state, direction, spaces);
    }

    // std::cout << "Tail Locations (P1): " << state.visitedLocations.size() + 1 << std::endl;
    std::cout << "Tail Locations (P2): " << state10Link.visitedLocations.size() + 1 << std::endl;
}
