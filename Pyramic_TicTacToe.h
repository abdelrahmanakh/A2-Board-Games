#ifndef GAME_1_PYRAMIC_TICTACTOE_H
#define GAME_1_PYRAMIC_TICTACTOE_H

#include "BoardGame_Classes.h"

template<typename T>
class Pyramic_Board : public Board<T> {
public:
    Pyramic_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Pyramic_Player : public Player<T> {
public:
    Pyramic_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template<typename T>
class Pyramic_Random_Player : public RandomPlayer<T> {
public:
    int rows, columns;

    Pyramic_Random_Player(T symbol);

    void getmove(int &x, int &y);
};

#endif


// Implementation...

#include <iomanip>

template<typename T>
Pyramic_Board<T>::Pyramic_Board() {
    this->rows = 3;
    this->columns = 5;
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
bool Pyramic_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) return false;
    if (x == 0 && y > 0) return false;
    if (x == 1 && y > 2) return false;
    this->n_moves++;
    this->board[x][y] = toupper(symbol);
    return true;
}

template<typename T>
void Pyramic_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout << '\n';
        if (i == 0)
            cout << setw(12 * (2 - i) - 2) << "| ";
        else
            cout << setw(12 * (2 - i)) << "| ";
        for (int j = 0; j < i * 2 + 1; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " | ";
        }
    }
    cout << endl;
}

template<typename T>
bool Pyramic_Board<T>::is_win() {
    auto val = this->board[0][0];
    if (val != 0 && this->board[1][0] == val && this->board[2][0] == val) return true;
    if (val != 0 && this->board[1][2] == val && this->board[2][4] == val) return true;
    if (val != 0 && this->board[1][1] == val && this->board[2][2] == val) return true;

    val = this->board[1][0];
    if (val != 0 && this->board[1][1] == val && this->board[1][2] == val) return true;

    for (int i = 2; i < this->columns; ++i) {
        if (this->board[2][i] == 0) continue;
        if (this->board[2][i - 2] == this->board[2][i] && this->board[2][i - 1] == this->board[2][i]) return true;
    }
    return false;
}

template<typename T>
bool Pyramic_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Pyramic_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//.....................................................................................................................

template<typename T>
Pyramic_Player<T>::Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Pyramic_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template<typename T>
Pyramic_Random_Player<T>::Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->rows = 3;
    this->columns = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void Pyramic_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->rows;
    y = rand() % this->columns;
}
