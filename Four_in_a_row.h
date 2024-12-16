
#ifndef _4_IN_A_ROW_H
#define _4_IN_A_ROW_H

#include "BoardGame_Classes.h"

template<typename T>
class Four_Board : public Board<T> {
public:
    Four_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();

};

template<typename T>
class Four_Player : public Player<T> {
public:
    Four_Player(string name, T symbol);

    void getmove(int &x, int &y);

};

template<typename T>
class Four_Random_Player : public RandomPlayer<T> {
public:
    Four_Random_Player(T symbol);

    void getmove(int &x, int &y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Four_Board
template<typename T>
Four_Board<T>::Four_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Four_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)
        && (x == 5 || this->board[x + 1][y])) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void Four_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template<typename T>
bool Four_Board<T>::is_win() {
    vector<vector<pair<int, int>>> patterns = {{{0, 0}, {0, 1},  {0, 2},  {0, 3}},
                                               {{0, 0}, {1, 0},  {2, 0},  {3, 0}},
                                               {{0, 0}, {1, 1},  {2, 2},  {3, 3}},
                                               {{0, 0}, {1, -1}, {2, -2}, {3, -3}}};
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++) {
            for (auto pat: patterns) {
                bool valid = this->board[i][j];
                for (auto [di, dj]: pat) {
                    if (i + di < 0 || i + di >= this->rows || j + dj < 0 || j + dj >= this->columns
                        || this->board[i + di][j + dj] != this->board[i][j])
                        valid = false;
                }
                if (valid)
                    return true;
            }
        }
    return false;
}

// Return true if 9 moves are done and no winner
template<typename T>
bool Four_Board<T>::is_draw() {
    return (this->n_moves == 6 * 7 && !is_win());
}

template<typename T>
bool Four_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Four_Player
template<typename T>
Four_Player<T>::Four_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Four_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x and y (x from 0 to 5, y from 0 to 6) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Four_Random_Player
template<typename T>
Four_Random_Player<T>::Four_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template<typename T>
void Four_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % 6;  // Random number between 0 and 5
    y = rand() % 7; // Random number between 0 and 6
}


#endif //_3X3Four_H

