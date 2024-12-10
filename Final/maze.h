#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>  
#include <conio.h> 
#include <unordered_map>
#include <ctime>
#include <utility>

using namespace std;

struct Cell {
    int x, y;
    bool visited;
    bool walls[4];
    bool hasReward;
    bool isTrap;

    Cell(int _x, int _y);
};

class Maze {
private:
    int rows, cols;
    Cell*** grid;
    pair<int, int> playerPosition;
    unordered_map<pair<int, int>, char, hash<pair<int, int>>> rewards; // Rewards and traps
    stack<pair<int, int>> moveHistory;
    int playerScore;
    int playerHealth;

    int getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]);
    void removeWalls(Cell& current, Cell& next);
    void movePlayer(char direction);
    void handleRewardsAndTraps();
    void placeRewardsAndTraps();
    void undoMove();
    void displayHint();

public:
    Maze(int r, int c);
    ~Maze();

    void displayMaze();
    void generateMaze();
    void play();
};

#endif
