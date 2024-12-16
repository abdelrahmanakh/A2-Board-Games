
#ifndef _NUMERICAL_H
#define _NUMERICAL_H

#include "BoardGame_Classes.h"
#include <set>

template<typename T>
class Num_Board : public Board<T> {
public:
    Num_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Num_Player : public Player<T> {
public:

    set<char> moves;

    Num_Player(string name, T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);

};

template<typename T>
class Num_Random_Player : public RandomPlayer<T> {
public:
    set<char> moves;

    Num_Random_Player(T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Num_Board
template<typename T>
Num_Board<T>::Num_Board() {
    this->rows = this->columns = 3;
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
bool Num_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        this->n_moves++;
        this->board[x][y] = mark;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void Num_Board<T>::display_board() {
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
bool Num_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] - 3 * '0' == 15) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] - 3 * '0' == 15)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] - 3 * '0' == 15) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] - 3 * '0' == 15)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template<typename T>
bool Num_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Num_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Num_Player
template<typename T>
Num_Player<T>::Num_Player(string name, T symbol) : Player<T>(name, symbol) {
    if (symbol == 'X') {
        for (char i = '1'; i <= '9'; i += 2)
            this->moves.insert(i);
    } else {
        for (char i = '2'; i <= '9'; i += 2)
            this->moves.insert(i);
    }
}

template<typename T>
void Num_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void Num_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char z;
    do {
        cout << "\nPlease enter the number to type: ";
        cin >> z;
    } while (!moves.count(z));
    moves.erase(z);
    setSymbol(z);
}

// Constructor for Num_Random_Player
template<typename T>
Num_Random_Player<T>::Num_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    if (symbol == 'X') {
        for (char i = '1'; i <= '9'; i += 2)
            this->moves.insert(i);
    } else {
        for (char i = '2'; i <= '9'; i += 2)
            this->moves.insert(i);
    }
}

template<typename T>
void Num_Random_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void Num_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    char z;
    do {
        z = rand() % 10 + '0';
    } while (!moves.count(z));
    moves.erase(z);
    setSymbol(z);
}


#endif //_3X3Num_H

