
#ifndef TASK3_5X5_TIC_TAC_TOE_H
#define TASK3_5X5_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template<typename T>
class TicTacToe5x5Board: public Board<T>{
public:
    Player<T>* players[2];
    int lines [2] = {0, 0};
    TicTacToe5x5Board(Player<T>* player1, Player<T>* player2);
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    void count_lines();
    std::string who_win();
    bool is_draw();
    bool game_is_over();
};

template<typename T>
class TicTacToe5x5Player: public Player<T>{
public:
    TicTacToe5x5Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template<typename T>
class TicTacToe5x5RandomPlayer: public RandomPlayer<T>{
public:
    TicTacToe5x5RandomPlayer(T symbol);
    void getmove(int& x, int& y);

};



//-------------------------------------
//Implementation
//-------------------------------------


//TicTacToe5x5Board constructor
template<typename T>
TicTacToe5x5Board<T>::TicTacToe5x5Board(Player<T>* player1, Player<T>* player2){
    this->rows = 5;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] =  0;
        }
    }
    this->n_moves = 0;
    this->players[0] = player1;
    this->players[1] = player2;
}

//Update Board Function
template<typename T>
bool TicTacToe5x5Board<T>::update_board(int x, int y, T symbol) {
    if((x>=0 && x<this->rows && y>=0 && y<this->columns && this->board[x][y] == 0)){
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

//Display board
template<typename T>
void TicTacToe5x5Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

//Count lines for each player
template<typename T>
void TicTacToe5x5Board<T>::count_lines() {
    for (int i = 1; i < this->rows-1; ++i) {
        for (int j = 1; j < this->columns-1; ++j) {
            if(this->board[i][j]==this->board[i][j-1] && this->board[i][j]==this->board[i][j+1]){
                if(this->board[i][j]==this->players[0]->getsymbol())
                    this->lines[0]++;
                else
                    this->lines[1]++;
            }
            if(this->board[i][j]==this->board[i-1][j] && this->board[i][j]==this->board[i+1][j]){
                if(this->board[i][j]==this->players[0]->getsymbol())
                    this->lines[0]++;
                else
                    this->lines[1]++;
            }
            if(this->board[i][j]==this->board[i-1][j-1] && this->board[i][j]==this->board[i+1][j+1]){
                if(this->board[i][j]==this->players[0]->getsymbol())
                    this->lines[0]++;
                else
                    this->lines[1]++;
            }
            if(this->board[i][j]==this->board[i+1][j-1] && this->board[i][j]==this->board[i-1][j+1]){
                if(this->board[i][j]==this->players[0]->getsymbol())
                    this->lines[0]++;
                else
                    this->lines[1]++;
            }
        }
    }
}

//Is draw
template<typename T>
bool TicTacToe5x5Board<T>::is_draw() {
    return false;
    if(!this->game_is_over())
        return false;
    count_lines();
    if (this->lines[0]==this->lines[1])
        return true;
    return false;
}

//Is win
template<typename T>
bool TicTacToe5x5Board<T>::is_win() {
    return false;
    if(!this->game_is_over())
        return false;
    count_lines();
    if (this->lines[0] > this->lines[1])
        return true;
    return false;
}

template<typename T>
string TicTacToe5x5Board<T>::who_win() {
    count_lines();
    if (this->lines[0] > this->lines[1])
        return this->players[0]->getname();
    else if(this->lines[0] < this->lines[1])
        return this->players[1]->getname();
    else
        return "Draw!!";
}

//game_is_over
template<typename T>
bool TicTacToe5x5Board<T>::game_is_over() {
    int empty_squares = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j]==0)
                empty_squares++;
            if (empty_squares>1)
                return false;
        }
    }
    return true;
}

//TicTacToe 5x5 player constructor
template<typename T>
TicTacToe5x5Player<T>::TicTacToe5x5Player(std::string name, T symbol): Player<T>(name, symbol) {}

//Get move
template<typename T>
void  TicTacToe5x5Player<T>::getmove(int &x, int &y) {
    char i,j;
    cout << "Please enter the coordinates of the square that you want (0 to 4)\n";
    while (true) {
        cout<<"x:";
        cin >> i;
        if (i >= '0' && i <= '4') {
            x = i - '0';
            break;
        } else {
            cout << "invalid input\n";
        }
    }
    while (true) {
        cout<<"y:";
        cin >> j;
        if (j >= '0' && j <= '4') {
            y = j - '0';
            break;
        } else {
            cout << "invalid input\n";
        }
    }
}

//:TicTacToe5x5RandomPlayer constructor
template<typename T>
TicTacToe5x5RandomPlayer<T>::TicTacToe5x5RandomPlayer(T symbol):RandomPlayer<T>(symbol){
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void TicTacToe5x5RandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}



#endif //TASK3_5X5_TIC_TAC_TOE_H
