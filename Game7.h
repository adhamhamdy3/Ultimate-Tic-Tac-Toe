//
// Created by Mohamed on 12/3/2024.
//

#ifndef GAME7_H
#define GAME7_H
#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board_7:public Board<T> {
public:
    X_O_Board_7 ();
    ~X_O_Board_7 ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player_7 : public Player<T> {
public:
    X_O_Player_7 (T symbol, string name);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_RandomPlayer_7 : public RandomPlayer<T>{
public:
    X_O_RandomPlayer_7 (T symbol , string name);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;
pair < int , int > pos;
// Constructor for X_O_Board
template <typename T>
X_O_Board_7<T>::X_O_Board_7() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->board[0][1] = this->board[0][3] = this->board[3][0] = this->board[3][2] = 'X';
    this->board[0][0] = this->board[0][2] = this->board[3][1] = this->board[3][3] = 'O';

    this->n_moves = 0;
}
template <typename T>
X_O_Board_7<T>::~X_O_Board_7() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
    this->board = nullptr;
}
template <typename T>
bool X_O_Board_7<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && !(pos.first < 0 || pos.first >= this->rows || pos.second < 0 || pos.second >= this->columns)){
    if (
         this->board[x][y] == 0 && ((x == pos.first && abs(y - pos.second) == 1) ||(y == pos.second && abs(x - pos.first) == 1) )
        && this->board[pos.first][pos.second] == mark) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            this->board[pos.first][pos.second] = 0;
        }
        return true;
    }

    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board_7<T>::display_board() {
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
template <typename T>
bool X_O_Board_7<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][2] != 0) ||
            (this->board[i][1] == this->board[i][2] && this->board[i][3] == this->board[i][2] && this->board[i][2] != 0)) {
            return true;
        }
        if ((this->board[0][i] == this->board[1][i] && this->board[2][i] == this->board[1][i] && this->board[1][i] != 0) ||
            (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[3][i] != 0)) {
            return true;
            }
    }
    for (int i = 0 ; i < this->rows;i++) {
        for (int j = 0 ; j < this->columns ; j++) {
            if (i - 2 > -1 && j + 2 < this->columns ) {
                if (this->board[i][j] == this->board[i-1][j + 1 ] && this->board[i -1 ][j + 1 ] == this->board[i-2][j + 2 ] && this->board[i][j] != 0) {
                    return true;
                }
            }
            if (i + 2 < this->rows && j + 2 < this->columns ) {
                if (this->board[i][j] == this->board[i+1][j + 1 ] && this->board[i +1 ][j + 1 ] == this->board[i+2][j + 2 ] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }
    }




    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board_7<T>::is_draw() {
    return false;
}

template <typename T>
bool X_O_Board_7<T>::game_is_over() {
    return false;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player_7<T>::X_O_Player_7(T symbol , string name ) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player_7<T>::getmove(int& x, int& y) {
    cout << "please enter you token position you want to move seperated by spaces : ";
    cin >> pos.first >> pos.second ;
    cout << "\nPlease enter your move x and y  separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_RandomPlayer_7<T>::X_O_RandomPlayer_7( T symbol ,string name) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_RandomPlayer_7<T>::getmove(int& x, int& y) {
    pos.first = rand() % this->dimension;
    pos.second = rand() % this->dimension;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}








#endif //GAME7_H
