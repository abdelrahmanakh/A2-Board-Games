//
// Created by Windows 10 on 12/14/2024.
//

#ifndef TASK3_TOETACTIC_H
#define TASK3_TOETACTIC_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template<typename T>
class ToeTacTicBoard: public Board<T>{
public:
    Player<T>* winner;//for the GameManager run method
    Player<T>* players[2];//for the GameManager run method
    ToeTacTicBoard(Player<T>* player1, Player<T>* player2);
    bool isloser = false; //for the GameManager run method
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template<typename T>
class ToeTacTicPlayer: public Player<T>{
public:
    ToeTacTicPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template<typename T>
class ToeTacTicRandomPlayer: public RandomPlayer<T>{
public:
    ToeTacTicRandomPlayer(T symbol);
    void getmove(int& x, int& y);

};



//-------------------------------------
//Implementation
//-------------------------------------
//ToeTacTicBoard constructor
template<typename T>
ToeTacTicBoard<T>::ToeTacTicBoard(Player<T>* player1, Player<T>* player2){
    this->rows = 3;
    this->columns = 3;
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
bool ToeTacTicBoard<T>::update_board(int x, int y, T symbol) {
    if(isloser)
        return true;
    if((x>=0 && x<this->rows && y>=0 && y<this->columns && this->board[x][y] == 0)){
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

//Display board
template<typename T>
void ToeTacTicBoard<T>::display_board() {
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

//Is draw
template<typename T>
bool ToeTacTicBoard<T>::is_draw() {
    if (this->n_moves==9&&!is_win()){
        return true;
    }
    return false;
}

//Is win
template<typename T>
bool ToeTacTicBoard<T>::is_win() {
    if((this->board[1][1] == this->board[0][0] && this->board[1][1] == this->board[2][2] && this->board[1][1]!=0)||
       (this->board[1][1] == this->board[0][2] && this->board[1][1] == this->board[2][0] && this->board[1][1]!=0)){
        if(this->board[1][1]==this->players[0]->getsymbol()){
            this->winner= this->players[1];
        }
        else
            this->winner = this->players[0];
        this->isloser= true;
        return false;
    }
    for (int i = 0; i < this->rows; ++i) {
        T cell = this->board[i][0];
        if (cell == 0)
            continue;
        int rc = 0,cc=0;
        for (int j = 1; j < this->columns; ++j) {
            if(cell == this->board[i][j]){
                rc++;
            } else{
                rc=0;
            }
            if(rc==2) {
                this->isloser = true;
                if(cell==this->players[0]->getsymbol()){
                    this->winner= this->players[1];
                }
                else
                    this->winner = this->players[0];
                return false;
            }
        }
        cell = this->board[0][i];
        if (cell == 0)
            continue;
        for (int j = 1; j < this->rows; ++j) {
            if(cell == this->board[j][i]){
                cc++;
            } else{
                cc=0;
            }
            if(cc==2) {
                this->isloser = true;
                if(cell==this->players[0]->getsymbol()){
                    this->winner= this->players[1];
                }
                else
                    this->winner = this->players[0];
                return false;
            }
        }
    }
    return false;
}

//game_is_over
template<typename T>
bool ToeTacTicBoard<T>::game_is_over() {
    if (is_draw() || isloser){
        return true;
    }
    return false;
}

//ToeTacTicPlayer constructor
template<typename T>
ToeTacTicPlayer<T>::ToeTacTicPlayer(std::string name, T symbol): Player<T>(name, symbol) {}

//Get move
template<typename T>
void  ToeTacTicPlayer<T>::getmove(int &x, int &y) {
    char i,j;
    cout << "Please enter the coordinates of the square that you want (0 to 2)\n";
    while (true) {
        cout<<"x:";
        cin >> i;
        if (i >= '0' && i <= '2') {
            x = i - '0';
            break;
        } else {
            cout << "invalid input\n";
        }
    }
    while (true) {
        cout<<"y:";
        cin >> j;
        if (j >= '0' && j <= '2') {
            y = j - '0';
            break;
        } else {
            cout << "invalid input\n";
        }
    }
}

//:TicTacToe5x5RandomPlayer constructor
template<typename T>
ToeTacTicRandomPlayer<T>::ToeTacTicRandomPlayer(T symbol):RandomPlayer<T>(symbol){
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void ToeTacTicRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif //TASK3_TOETACTIC_H
