//
// Created by Mohamed on 12/3/2024.
//

#ifndef GAME6_H
#define GAME6_H
#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board_6:public Board<T> {
public:
    X_O_Board_6 ();
    ~X_O_Board_6 ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player_6 : public Player<T> {
public:
    X_O_Player_6 (T symbol, string name);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_RandomPlayer_6 : public RandomPlayer<T>{
public:
    X_O_RandomPlayer_6 (T symbol , string name);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;
bool there_was_a_winner = false;
// Constructor for X_O_Board
template <typename T>
X_O_Board_6<T>::X_O_Board_6() {
    there_was_a_winner = false;
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board_6<T>::update_board(int x, int y, T mark) {
    if (there_was_a_winner)return true;
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board_6<T>::display_board() {
    if (there_was_a_winner)return ;
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
bool X_O_Board_6<T>::is_win() {
    if (there_was_a_winner)return true;
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
           (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) && !there_was_a_winner ) {
            there_was_a_winner = true;
        }
    }

    if (((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
       (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) && !there_was_a_winner) {
        there_was_a_winner = true ;
       }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board_6<T>::is_draw() {
    return (this->n_moves == 9 && !there_was_a_winner);
}

template <typename T>
bool X_O_Board_6<T>::game_is_over() {
    return false ;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player_6<T>::X_O_Player_6(T symbol, string name) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player_6<T>::getmove(int& x, int& y) {
    if (there_was_a_winner) {
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
 X_O_RandomPlayer_6<T>::X_O_RandomPlayer_6(T symbol , string name) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
X_O_Board_6<T>::~X_O_Board_6() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
    this->board = nullptr;
}
template <typename T>
void X_O_RandomPlayer_6<T>::getmove(int& x, int& y) {
    if (there_was_a_winner) {
        return;
    }
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
