#ifndef GAME_4_WORD_TICTACTOE_H
#define GAME_4_WORD_TICTACTOE_H

#include "BoardGame_Classes.h"
#include "set"

template<typename T>
class Word_Board : public Board<T> {
public:
    set <string> dic;

    Word_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Word_Player : public Player<T> {
public:
    Word_Player(string name, T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);
};

template<typename T>
class Word_Random_Player : public RandomPlayer<T> {
public:
    Word_Random_Player(T symbol);

    void setSymbol(T symbol);

    void getmove(int &x, int &y);
};

#endif


// Implementation...

#include <iomanip>
#include "fstream"

template<typename T>
Word_Board<T>::Word_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    ifstream file("dic.txt");
    string line;
    while (getline(file, line))
        dic.insert(line);
}

template<typename T>
bool Word_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 || !isalpha(symbol))
        return false;
    this->n_moves++;
    this->board[x][y] = toupper(symbol);
    return true;
}

template<typename T>
void Word_Board<T>::display_board() {
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

template<typename T>
bool Word_Board<T>::is_win() {
    string word;
    for (int i = 0; i < this->rows; i++) {
        word = this->board[i][0] + this->board[i][1] + this->board[i][2];
        if (dic.find(word) != dic.end()) return true;

        word = this->board[0][i] + this->board[1][i] + this->board[2][i];
        if (dic.find(word) != dic.end()) return true;
    }


    word = this->board[0][0] + this->board[1][1] + this->board[2][2];
    if (dic.find(word) != dic.end()) return true;

    word = this->board[0][2] + this->board[1][1] + this->board[2][0];
    if (dic.find(word) != dic.end()) return true;

    return false;
}

template<typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//.....................................................................................................................

template<typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Word_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void Word_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "\nPlease enter your character from the English alphabet: ";
    char symbol;
    cin >> symbol;
    setSymbol(symbol);
}

template<typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void Word_Random_Player<T>::setSymbol(T symbol) {
    this->symbol = symbol;
}

template<typename T>
void Word_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    int symbol = rand() % 26 + 65;
    setSymbol((char) symbol);
}
