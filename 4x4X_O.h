
#ifndef _4X4X_O_H
#define _4X4X_O_H

#include "BoardGame_Classes.h"
#include <set>

template<typename T>
class _4x4_Board : public Board<T> {
public:
    _4x4_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();

};

template<typename T>
class _4x4_Player : public Player<T> {
public:
    set<pair<int, int>> token;
    T temp_symbol;

    _4x4_Player(string name, T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);

};

template<typename T>
class _4x4_Random_Player : public RandomPlayer<T> {
public:
    set<pair<int, int>> token;
    T temp_symbol;

    _4x4_Random_Player(T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for _4x4_Board
template<typename T>
_4x4_Board<T>::_4x4_Board() {
    this->rows = this->columns = 4;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    for (int i = 0; i < 4; i++) {
        this->update_board(0, i, (i & 1) ? 'X' : 'O');
        this->update_board(3, i, (i & 1) ? 'O' : 'X');
    }
}

template<typename T>
bool _4x4_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
//            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void _4x4_Board<T>::display_board() {
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
bool _4x4_Board<T>::is_win() {
    vector<vector<pair<int, int>>> patterns = {{{0, 0}, {0, 1},  {0, 2}},
                                               {{0, 0}, {1, 0},  {2, 0}},
                                               {{0, 0}, {1, 1},  {2, 2}},
                                               {{0, 0}, {1, -1}, {2, -2}}};
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
bool _4x4_Board<T>::is_draw() {
    return false;
}

template<typename T>
bool _4x4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for _4x4_Player
template<typename T>
_4x4_Player<T>::_4x4_Player(string name, T symbol) : Player<T>(name, symbol) {
    temp_symbol = symbol;
    if (symbol == 'X') {
        this->token.insert({0, 1});
        this->token.insert({0, 3});
        this->token.insert({3, 0});
        this->token.insert({3, 2});
    } else {
        this->token.insert({0, 0});
        this->token.insert({0, 2});
        this->token.insert({3, 1});
        this->token.insert({3, 3});
    }
}

template<typename T>
void _4x4_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void _4x4_Player<T>::getmove(int &x, int &y) {

    int x1, y1;
    setSymbol(temp_symbol);
    do {
        cout << "\nPlease enter the token you want to move x and y (0 to 3) separated by spaces: ";
        cin >> x >> y;
        cout << "\nPlease enter an open adjacent square x and y (0 to 3) separated by spaces: ";
        cin >> x1 >> y1;
    } while ((abs(x - x1) + abs(y - y1) != 1) || !token.count({x, y}) ||
             !this->boardPtr->update_board(x1, y1, this->symbol));
    token.erase({x, y});
    token.insert({x1, y1});
    setSymbol(0);
}

// Constructor for _4x4_Random_Player
template<typename T>
_4x4_Random_Player<T>::_4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    temp_symbol = symbol;
    if (symbol == 'X') {
        this->token.insert({0, 1});
        this->token.insert({0, 3});
        this->token.insert({3, 0});
        this->token.insert({3, 2});
    } else {
        this->token.insert({0, 0});
        this->token.insert({0, 2});
        this->token.insert({3, 1});
        this->token.insert({3, 3});
    }
}

template<typename T>
void _4x4_Random_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void _4x4_Random_Player<T>::getmove(int &x, int &y) {
    int x1, y1;
    setSymbol(temp_symbol);
    do {
        x = rand() % 4;
        y = rand() % 4;
        x1 = rand() % 4;
        y1 = rand() % 4;
    } while ((abs(x - x1) + abs(y - y1) != 1) || !token.count({x, y}) ||
             !this->boardPtr->update_board(x1, y1, this->symbol));
    token.erase({x, y});
    token.insert({x1, y1});
    setSymbol(0);
}


#endif //_4X4X_O_H

