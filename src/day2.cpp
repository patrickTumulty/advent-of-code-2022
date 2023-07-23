

// 6 if you win
// 3 if draw
// 0 if you lose
// A and X: Rock (1)
// B and Y: Paper (2)
// C and Z: Scissors (3)

#include "utils.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

typedef enum Move_E
{
    UNKNOWN,
    ROCK,
    PAPER,
    SCISSORS
} Move;

typedef enum RoundResult_E
{
    WIN,
    LOSE,
    DRAW
} RoundResult;

Move getForcedMove(Move opponentMove, RoundResult roundResult)
{
    if (roundResult == DRAW)
        return opponentMove;

    switch (opponentMove)
    {
        case ROCK:
            if (roundResult == WIN)
            {
                return PAPER;
            }
            else
            {
                return SCISSORS;
            }
            break;
        case PAPER:
            if (roundResult == WIN)
            {
                return SCISSORS;
            }
            else
            {
                return ROCK;
            }
            break;
        case SCISSORS:
            if (roundResult == WIN)
            {
                return ROCK;
            }
            else
            {
                return PAPER;
            }
            break;
        case UNKNOWN:
            break;
    }
    return UNKNOWN;
}

RoundResult inputToRoundResult(char input)
{
    switch (input)
    {
        case 'X':
            return LOSE;
        case 'Y':
            return DRAW;
        case 'Z':
            return WIN;
    }
    return LOSE;
}

Move getMove(char input)
{
    switch (input)
    {
        case 'A':
        case 'X':
            return ROCK;
        case 'B':
        case 'Y':
            return PAPER;
        case 'C':
        case 'Z':
            return SCISSORS;
    }
    return UNKNOWN;
}

bool playerWins(Move playerMove, Move opponentMove)
{
    switch (opponentMove)
    {
        case ROCK:
            return playerMove == PAPER;
        case PAPER:
            return playerMove == SCISSORS;
        case SCISSORS:
            return playerMove == ROCK;
        case UNKNOWN:
            break;
    }
    return false;
}

void incrementScore(int* score, Move playerMove)
{
    switch (playerMove)
    {
        case ROCK:
            *score += 1;
            break;
        case PAPER:
            *score += 2;
            break;
        case SCISSORS:
            *score += 3;
            break;
        case UNKNOWN:
            break;
    }
}

void runDay2()
{
    std::vector<std::pair<char, char>> strategyGuide = std::vector<std::pair<char, char>>();

    std::ifstream infile("../data/elf_strategy_guide.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (isNullOrWhiteSpace(line))
        {
            continue;
        }

        strategyGuide.push_back(std::make_pair(line.c_str()[0], line.c_str()[2]));
    }

    // strategyGuide.push_back(std::make_pair('A', 'Y'));
    // strategyGuide.push_back(std::make_pair('B', 'X'));
    // strategyGuide.push_back(std::make_pair('C', 'Z'));

    int score = 0;
    for (std::pair<char, char> p : strategyGuide)
    {
        Move opponentMove = getMove(p.first);
        Move playerMove = getForcedMove(opponentMove, inputToRoundResult(p.second));

        if (playerMove == opponentMove)
        {
            score += 3;
        }
        else if (playerWins(playerMove, opponentMove))
        {
            score += 6;
        }

        incrementScore(&score, playerMove);
    }

    std::cout << "Score: " << score << std::endl;
}
