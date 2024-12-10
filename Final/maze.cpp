#include "maze.h"

Cell::Cell(int _x, int _y) {
    x = _x;
    y = _y;
    visited = false;
    walls[0] = walls[1] = walls[2] = walls[3] = true;
    hasReward = false;
    isTrap = false;
}

Maze::Maze(int r, int c) : rows(r), cols(c), playerScore(0), playerHealth(100) {
    playerPosition = {0, 0};
    grid = new Cell**[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new Cell*[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = new Cell(i, j);
        }
    }
    srand(time(0));
}

Maze::~Maze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Maze::displayMaze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[0] ? "+---" : "+   ");
        }
        cout << "+" << endl;

        for (int j = 0; j < cols; ++j) {
            if (playerPosition.first == i && playerPosition.second == j) {
                cout << (grid[i][j]->walls[3] ? "| P " : "  P ");
            } else if (grid[i][j]->hasReward) {
                cout << (grid[i][j]->walls[3] ? "| R " : "  R ");
            } else if (grid[i][j]->isTrap) {
                cout << (grid[i][j]->walls[3] ? "| T " : "  T ");
            } else {
                cout << (grid[i][j]->walls[3] ? "|   " : "    ");
            }
        }
        cout << "|" << endl;
    }
    for (int j = 0; j < cols; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;

    cout << "Health: " << playerHealth << " | Score: " << playerScore << endl;
}

void Maze::generateMaze() {
    stack<Cell*> cellStack;
    Cell* startCell = grid[0][0];
    startCell->visited = true;
    cellStack.push(startCell);

    while (!cellStack.empty()) {
        Cell* current = cellStack.top();
        Cell* neighbors[4];
        int neighborCount = getUnvisitedNeighbors(current, neighbors);
        if (neighborCount > 0) {
            Cell* next = neighbors[rand() % neighborCount];
            removeWalls(*current, *next);
            next->visited = true;
            cellStack.push(next);
        } else {
            cellStack.pop();
        }
    }

    placeRewardsAndTraps();
}

void Maze::play() {
    char input;
    while (true) {
        system("cls");
        displayMaze();
        cout << "Use WASD to move (W = up, A = left, S = down, D = right), Q to quit, U to undo, H for hint." << endl;
        input = _getch();

        if (input == 'q' || input == 'Q') break;
        if (input == 'u' || input == 'U') {
            undoMove();
            continue;
        }
        if (input == 'h' || input == 'H') {
            displayHint();
            continue;
        }

        movePlayer(input);
        handleRewardsAndTraps();

        if (playerPosition == make_pair(rows - 1, cols - 1)) {
            system("cls");
            displayMaze();
            cout << "Congratulations! You've reached the end of the maze!" << endl;
            break;
        }
    }
}

void Maze::placeRewardsAndTraps() {
    for (int i = 0; i < 5; ++i) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (x == 0 && y == 0) continue;
        grid[x][y]->hasReward = true;
    }

    for (int i = 0; i < 3; ++i) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (x == 0 && y == 0) continue;
        grid[x][y]->isTrap = true;
    }
}

void Maze::movePlayer(char direction) {
    int x = playerPosition.first;
    int y = playerPosition.second;

    moveHistory.push(playerPosition);

    if (direction == 'w' && x > 0 && !grid[x][y]->walls[0]) playerPosition.first--;
    else if (direction == 'a' && y > 0 && !grid[x][y]->walls[3]) playerPosition.second--;
    else if (direction == 's' && x < rows - 1 && !grid[x][y]->walls[2]) playerPosition.first++;
    else if (direction == 'd' && y < cols - 1 && !grid[x][y]->walls[1]) playerPosition.second++;
}

void Maze::undoMove() {
    if (!moveHistory.empty()) {
        playerPosition = moveHistory.top();
        moveHistory.pop();
    } else {
        cout << "No moves to undo!" << endl;
    }
}

void Maze::handleRewardsAndTraps() {
    int x = playerPosition.first;
    int y = playerPosition.second;

    if (grid[x][y]->hasReward) {
        playerScore += 10;
        grid[x][y]->hasReward = false;
        cout << "You collected a reward! Score: " << playerScore << endl;
    } else if (grid[x][y]->isTrap) {
        playerHealth -= 10;
        grid[x][y]->isTrap = false;
        cout << "You hit a trap! Health: " << playerHealth << endl;
    }
}

void Maze::displayHint() {
    cout << "Hint: Move closer to the goal!" << endl;
}
