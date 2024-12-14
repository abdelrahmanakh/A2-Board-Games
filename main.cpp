#include <iostream>
#include "5x5_Tic_Tac_Toe.h"
using namespace std;

int main() {

    Player<char>* players[2];
    players[0] = new  TicTacToe5x5Player<char>("player1", 'X');
    players[1] = new  TicTacToe5x5Player<char>("player2", 'O');
    auto* board = new TicTacToe5x5Board<char>(players[0],players[1]);

    GameManager<char> tic(board, players);
    tic.run();
    string name = board->who_win();
    cout<<name;
}
