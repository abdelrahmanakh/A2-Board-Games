#include <iostream>
#include "5x5_Tic_Tac_Toe.h"
#include "Four_in_a_row.h"
#include "ToeTacTic.h"
#include "Num_Tic_Tac_Toe.h"
#include "Pyramic_TicTacToe.h"
#include "4x4X_O.h"
#include "Word_TicTacToe.h"
#include "Ultimate_TicTacToe.h"

using namespace std;

//function to get Players names and symbols
void PlayerMenu(string *arr) {
    string name;
    cout << "Please Enter Your Name:";
    cin.ignore();
    getline(cin, name);
    arr[0] = name;
    arr[1] = 'X';
    cout << "Choose the other Player type:\n1)Human\n2)Random computer\n";
    while (true) {
        char choice;
        cin >> choice;
        if (choice == '1') {
            cout << "Please Enter the name of the other Player:";
            cin.ignore();
            getline(cin, name);
            arr[2] = name;
            arr[3] = 'O';
            break;
        } else if (choice == '2') {
            arr[2] = "Random Player";
            arr[3] = 'O';
            break;
        } else {
            cout << "Please Enter A valid Choice!!\n";
        }
    }
    cout << arr[0] << ": X\n" << arr[2] << ": O\n";
}

int main() {
    cout << "Welcome to our Board-Games please choose one of the following:";
    Player<char> *players[2];
    string data[4];
    while (true) {
        cout << "\n1)Pyramic Tic-Tac-Toe"
                "\n2)Four-in-a-row"
                "\n3)5 x 5 Tic Tac Toe"
                "\n4)Word Tic Tac Toe"
                "\n5)Numerical Tic-Tac-Toe"
                "\n6)Misere Tic Tac Toe"
                "\n7)4 x 4 Tic Tac Toe"
                "\n8)Ultimate Tic Tac Toe\n"
                "9)Exit\n";
        char choice;
        cin >> choice;
        if (choice == '1') {
            PlayerMenu(data);
            players[0] = new Pyramic_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new Pyramic_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new Pyramic_Player<char>(data[2], data[3][0]);
            }
            auto *board = new Pyramic_Board<char>();
            GameManager<char> Pyramic_TicTacToe_game(board, players);
            Pyramic_TicTacToe_game.run();
            delete board;
        } else if (choice == '2') {
            PlayerMenu(data);
            players[0] = new Four_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new Four_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new Four_Player<char>(data[2], data[3][0]);
            }
            auto *board = new Four_Board<char>();
            GameManager<char> Four(board, players);
            Four.run();
            delete board;
        } else if (choice == '3') {
            PlayerMenu(data);
            players[0] = new TicTacToe5x5Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new TicTacToe5x5RandomPlayer<char>(data[3][0]);
            } else {
                players[1] = new TicTacToe5x5Player<char>(data[2], data[3][0]);
            }
            auto *board = new TicTacToe5x5Board<char>(players[0], players[1]);
            GameManager<char> TicTacToe5x5(board, players);
            TicTacToe5x5.run();
            string winner = board->who_win();
            cout << "The Winner is: " << winner << "\n";
            delete board;
        } else if (choice == '4') {
            PlayerMenu(data);
            players[0] = new Word_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new Word_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new Word_Player<char>(data[2], data[3][0]);
            }

            auto *board = new Word_Board<char>();
            GameManager<char> Word_TicTacToe_game(board, players);
            Word_TicTacToe_game.run();
            delete board;
        } else if (choice == '5') {
            PlayerMenu(data);
            players[0] = new Num_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new Num_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new Num_Player<char>(data[2], data[3][0]);
            }
            auto *board = new Num_Board<char>();
            GameManager<char> Num(board, players);
            Num.run();
            delete board;
        } else if (choice == '6') {
            PlayerMenu(data);
            players[0] = new ToeTacTicPlayer<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new ToeTacTicRandomPlayer<char>(data[3][0]);
            } else {
                players[1] = new ToeTacTicPlayer<char>(data[2], data[3][0]);
            }
            auto *board = new ToeTacTicBoard<char>(players[0], players[1]);
            GameManager<char> ToeTacTic(board, players);
            ToeTacTic.run();
            if (board->isloser) {
                string winner = board->winner->getname();
                cout << "The Winner is: " << winner << "\n";
            }
            delete board;
        } else if (choice == '7') {
            PlayerMenu(data);
            players[0] = new _4x4_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new _4x4_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new _4x4_Player<char>(data[2], data[3][0]);
            }
            auto *board = new _4x4_Board<char>();
            GameManager<char> _4x4(board, players);
            players[0]->setBoard(board);
            players[1]->setBoard(board);
            _4x4.run();
            delete board;
        } else if (choice == '8') {
            PlayerMenu(data);
            players[0] = new Ultimate_Player<char>(data[0], data[1][0]);
            if (data[2] == "Random Player") {
                players[1] = new Ultimate_Random_Player<char>(data[3][0]);
            } else {
                players[1] = new Ultimate_Player<char>(data[2], data[3][0]);
            }

            auto *board = new Ultimate_Board<char>();
            GameManager<char> Ultimate_TicTacToe_game(board, players);
            Ultimate_TicTacToe_game.run();
            delete board;
        } else if (choice == '9') {
            return 0;
        } else {
            cout << "Please Enter A valid choice!!\n";
        }
        delete players[0];
        delete players[1];
    }
}
