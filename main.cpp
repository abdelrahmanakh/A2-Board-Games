#include <iostream>
#include "5x5_Tic_Tac_Toe.h"
#include "ToeTacTic.h"
#include "Pyramic_TicTacToe.h"
#include "Word_TicTacToe.h"

using namespace std;

//function to get Players names and symbols
void PlayerMenu(string *arr) {
    string name;
    char symbol1;
    cout << "Please Enter Your Name:";
    cin.ignore();
    getline(cin, name);
    cout << "Please Enter Your Symbol:";
    cin >> symbol1;
    arr[0] = name;
    arr[1] = symbol1;
    cout << "Choose the other Player type:\n1)Human\n2)Random computer\n";
    while (true) {
        char choice;
        cin >> choice;
        if (choice == '1') {
            cout << "Please Enter the name of the other Player:";
            cin.ignore();
            getline(cin, name);
            cout << "Please Enter the symbol of the other Player:";
            cin >> symbol1;
            arr[2] = name;
            arr[3] = symbol1;
            break;
        } else if (choice == '2') {
            cout << "Please Enter the symbol of the Random Player:";
            cin >> symbol1;
            arr[2] = "Random Player";
            arr[3] = symbol1;
            break;
        } else {
            cout << "Please Enter A valid Choice!!\n";
        }
    }
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
            //Mazen
        } else if (choice == '2') {
            //Youssef
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
            //Mazen
        } else if (choice == '5') {
            //Youssef
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
            //Youssef
        } else if (choice == '8') {
            //Mazen
        } else if (choice == '9') {

            return 0;
        } else {
            cout << "Please Enter A valid choice!!\n";
        }
        delete players[0];
        delete players[1];
    }
}
