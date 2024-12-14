#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  

using namespace std;
template <typename T>
class Connect4_Board:public Board<T>{
private:
    int counter[7]{ 0 };
public:
    Connect4_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();


};
template <typename T>
class Connect4_Player : public Player<T> {
public:
    Connect4_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class Connect4_Random_Player : public RandomPlayer<T> {
public:
    Connect4_Random_Player(T symbol);
    void getmove(int& x, int& y);
};






template <typename T>
 Connect4_Board<T>::Connect4_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
            this->board[i][j] = 0;
    }
    this->n_moves = 0;

}

 template <typename T>
 bool Connect4_Board<T>::update_board(int x, int y, T mark) {
     
     if (this->board[0][y]) {
         cout << "Column is Full.\n";
         return false;
     }

     if (!(y < 0 || y >= this->columns)) {

             this->n_moves++;
             this->board[this->rows - counter[y] - 1][y] = toupper(mark);
             counter[y]++;
             return true;
         }
     
       
     
     return false;
 
}

 template <typename T>
 void Connect4_Board<T>::display_board() {
     cout << "  ";
     for (int j = 0; j < this->columns; j++) {
         cout << j << "   ";
     }
     cout << "\n";

     for (int i = 0; i < this->rows; i++) {
         cout << "| ";
         for (int j = 0; j < this->columns; j++) {
             cout << setw(2) << this->board[i][j] << " | ";
         }
         cout << "\n  ";
         for (int j = 0; j < this->columns; j++) {
             cout << "----";
         }
        cout << "-\n";
     }
     cout << endl;
 }


template <typename T>
bool Connect4_Board<T>::is_win() {
    //check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2] && this->board[i][j] == this->board[i][j + 3] )
                return true;

        }
    }
    //check columns
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j <= this->rows - 4; j++) {
       
            if (this->board[j][i] != 0 && this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] && this->board[j + 2][i] == this->board[j + 3][i] )  return true;


        }
    }

    // two checks for diagonals 
    
    //top left
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 3; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] == this->board[i + 3][j + 3] ) {
                return true;
            }

        }
    }
    //top right
    for (int i = 0; i <= 2; i++) {
        for (int j = 3; j < 7; j++) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j - 1] && this->board[i][j] == this->board[i + 2][j - 2] && this->board[i][j] == this->board[i + 3][j - 3] )
                return true;
            

        }
    }
    return false;

}

template <typename T>
bool Connect4_Board<T>::is_draw() {
    if (this->n_moves == 42 && !is_win())
        return true;
    return false;
}

template <typename T>
bool Connect4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) : Player<T>(name, symbol) {

}

template <typename T>
void Connect4_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter y (0,6): ";
    cin >> y;
    if (y < 0 or y>6)cout << "Invalid Enter Y (0,6).\n";
}





template <typename T>
Connect4_Random_Player<T>::Connect4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); 
    
}

template <typename T>
void Connect4_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % 7;
}