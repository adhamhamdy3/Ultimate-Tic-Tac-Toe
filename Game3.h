//
// Created by Mohamed on 12/2/2024.
//

#ifndef GAME3_H
#define GAME3_H
#include "BoardGame_Classes.h"

template < typename T>
class  X_O_Board_3 : public Board <T>  {
private:
    T mark1 , mark2;
    int CountX , CountO ;
public:
    X_O_Board_3();
    ~X_O_Board_3();
    bool update_board(int x , int y , T mark)override;
    void display_board()override;
    bool is_win()override;
    bool game_is_over()override;
    bool is_draw()override;



};
template < typename T>
class  X_O_Player_3 : public Player<T> {
public:

    X_O_Player_3(T mark , string name );
     X_O_Player_3(T mark );
    void getmove(int& x , int& y );
};
template <typename T>
class  X_O_RandomPlayer_3  : public RandomPlayer<T> {
public:
     X_O_RandomPlayer_3(T mark , string name );
    void getmove(int &x , int &y)override;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;
int number_of_moves;
template <typename T>
 X_O_Player_3<T>:: X_O_Player_3(T mark, string name) : Player<T>(name, mark) {}

template <typename T>
 X_O_Player_3<T>:: X_O_Player_3(T mark) : Player<T>("Computer", mark) {

}

template < typename T>
void  X_O_Player_3<T>::getmove(int& x , int& y) {
    if (number_of_moves == 24 )return;
    cout << "Enter your next move x and y (0 to 5 inclusive) separated by spaces : ";
    cin >> x >> y ;
}
template<typename T>
 X_O_Board_3<T>:: X_O_Board_3() {
    CountX = CountO = 0;
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

}
template<typename T>
X_O_Board_3<T>::~X_O_Board_3() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
    this->board = nullptr;
}
template <typename T>
bool  X_O_Board_3<T>::update_board(int x, int y, T mark) {
    if (this->n_moves == 24 ) {
        this->n_moves++;
        number_of_moves=this -> n_moves;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
            number_of_moves = this->n_moves;
        }
        else {
            this->n_moves++;
            number_of_moves = this->n_moves;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}
template <typename T>
void  X_O_Board_3<T>::display_board() {
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
bool  X_O_Board_3<T>::is_win() {
    CountX = CountO = 0;
    for (int i = 0 ; i < this->rows;i++) {
        for (int j = 0 ; j < this->columns ; j++) {
            if ( j + 2 < this->columns ) {
                CountX += (this->board[i][j] == 'X' && this->board[i][j + 1 ] == 'X' && this->board[i][j + 2] == 'X');
                CountO += (this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O');
            }
            if (i + 2 < this->rows) {
                CountX += (this->board[i][j] == 'X' && this->board[i + 1 ][j] == 'X' && this->board[i + 2 ][j] == 'X');
                CountO += (this->board[i][j] == 'O' && this->board[i + 1 ][j] == 'O' && this->board[i + 2][j] == 'O');
            }
            if (i + 2 < this->rows && j + 2 < this->columns) {
                CountX += (this->board[i][j] == 'X' && this->board[i + 1 ][j + 1 ] == 'X' && this->board[i + 2 ][j + 2 ] == 'X');
                CountO += (this->board[i][j] == 'O' && this->board[i + 1 ][j + 1 ] == 'O' && this->board[i + 2][j + 2] == 'O');
            }
            if (i - 2 > -1  && j + 2 < this->columns) {
                CountX += (this->board[i][j] == 'X' && this->board[i - 1 ][j + 1 ] == 'X' && this->board[i - 2 ][j + 2 ] == 'X');
                CountO += (this->board[i][j] == 'O' && this->board[i - 1 ][j + 1 ] == 'O' && this->board[i - 2][j + 2] == 'O');
            }

        }
    }
    if (this->n_moves == 24 && CountO > CountX ) {
        return true;
    };
    if (this->n_moves == 25  && CountO < CountX) {
        return true;
    };
    return false;

}
template<typename T>
bool  X_O_Board_3<T>::is_draw() {
    return this->n_moves  >= 24 && CountX == CountO ;
}

template<typename T>
bool  X_O_Board_3<T>::game_is_over() {
    return this->n_moves == 25 ;
}
template <typename T>
 X_O_RandomPlayer_3<T>:: X_O_RandomPlayer_3(T symbol , string name ) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void  X_O_RandomPlayer_3<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //GAME3_H
