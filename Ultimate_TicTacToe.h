#ifndef GAME_8_Ultimate_TICTACTOE_H
#define GAME_8_Ultimate_TICTACTOE_H

#include "BoardGame_Classes.h"

template<typename T>
class Ultimate_Board : public Board<T> {
public:
    int summary_rows, summary_columns;
    T **summary_board;

    Ultimate_Board();

    bool update_board(int x, int y, T symbol);

    void update_summary_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_summary_win(int x, int y);

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template<typename T>
class Ultimate_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Random_Player(T symbol);

    void getmove(int &x, int &y);
};

#endif


// Implementation...

#include <iomanip>

template<typename T>
Ultimate_Board<T>::Ultimate_Board() {
    this->summary_rows = this->summary_columns = 3;
    this->summary_board = new char *[this->summary_rows];
    for (int i = 0; i < this->summary_rows; ++i) {
        this->summary_board[i] = new char[this->summary_columns];
        for (int j = 0; j < this->summary_columns; ++j) {
            this->summary_board[i][j] = 0;
        }
    }

    this->rows = this->columns = 9;
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
void Ultimate_Board<T>::update_summary_board(int x, int y, T symbol) {
    int nx = x / 3, ny = y / 3;
    if (is_summary_win(nx, ny)) {
        this->summary_board[nx][ny] = toupper(symbol);
        ++this->n_moves;
    } else {
        bool full = true;
        for (int i = 0; i < this->summary_rows; ++i) {
            for (int j = 0; j < this->summary_columns; ++j) {
                full &= (this->board[nx * 3 + i][ny * 3 + j] != 0);
            }
        }
        if (full)
            ++this->n_moves;
    }
}

template<typename T>
bool Ultimate_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 ||
        this->summary_board[x / 3][y / 3] != 0)
        return false;
    this->board[x][y] = toupper(symbol);
    update_summary_board(x, y, symbol);
    return true;
}

template<typename T>
void Ultimate_Board<T>::display_board() {
    cout << "SUMMARY BOARD";
    for (int i = 0; i < this->summary_rows; ++i) {
        cout << "\n| ";
        for (int j = 0; j < this->summary_columns; ++j) {
            cout << this->summary_board[i][j] << " | ";
        }
    }

    cout << "\n\nVIEW BOARD";
    for (int i = 0; i < this->rows; ++i) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j];
            if (j == 2 || j == 5) cout << "  ||  ";
            else cout << " | ";
        }
        if (i == 2 || i == 5)
            cout << "\n-----------------------------------------------------------------------------------------------";
    }
    cout << "\n\n";
}

template<typename T>
bool Ultimate_Board<T>::is_summary_win(int x, int y) {
    int nx = x * 3, ny = y * 3;
    for (int i = 0; i < this->summary_rows; i++) {
        if ((this->board[i + nx][ny] == this->board[i + nx][1 + ny] &&
             this->board[i + nx][1 + ny] == this->board[i + nx][2 + ny] && this->board[i + nx][ny] != 0) ||
            (this->board[nx][i + ny] == this->board[1 + nx][i + ny] &&
             this->board[1 + nx][i + ny] == this->board[2 + nx][i + ny] && this->board[nx][i + ny] != 0)) {
            return true;
        }
    }

    if ((this->board[nx][ny] == this->board[1 + nx][1 + ny] &&
         this->board[1 + nx][1 + ny] == this->board[2 + nx][2 + ny] && this->board[nx][ny] != 0) ||
        (this->board[nx][2 + ny] == this->board[1 + nx][1 + ny] &&
         this->board[1 + nx][1 + ny] == this->board[2 + nx][ny] && this->board[nx][2 + ny] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool Ultimate_Board<T>::is_win() {
    for (int i = 0; i < this->summary_rows; i++) {
        if ((this->summary_board[i][0] == this->summary_board[i][1] &&
             this->summary_board[i][1] == this->summary_board[i][2] && this->summary_board[i][0] != 0) ||
            (this->summary_board[0][i] == this->summary_board[1][i] &&
             this->summary_board[1][i] == this->summary_board[2][i] && this->summary_board[0][i] != 0)) {
            return true;
        }
    }

    if ((this->summary_board[0][0] == this->summary_board[1][1] &&
         this->summary_board[1][1] == this->summary_board[2][2] && this->summary_board[0][0] != 0) ||
        (this->summary_board[0][2] == this->summary_board[1][1] &&
         this->summary_board[1][1] == this->summary_board[2][0] && this->summary_board[0][2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool Ultimate_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//.....................................................................................................................

template<typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Ultimate_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x (0 to 8) and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

template<typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void Ultimate_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}