#ifndef NumXo
#define NumXo
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
class NumXo_Board : public Board<T> {
public:
    vector<int> numbers;
    vector<int> freq;
    int count;
    int n_moves;

    NumXo_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int get_cell(int, int);
};

template <typename T>
class NumXo_Player : public Player<T> {
public:
    NumXo_Player(string name, T symbol, NumXo_Board<T>* board);
    void getmove(int& x, int& y);
};

template <typename T>
class NumXo_Random_Player : public RandomPlayer<T> {
public:
    NumXo_Random_Player(T symbol, NumXo_Board<T>* board);
    void getmove(int& x, int& y);
};

template <typename T>
NumXo_Board<T>::NumXo_Board() {
    this->rows = this->columns = 3;
    this->board = new int* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    this->freq = vector<int>(10, 0);
    this->count = 0;
    this->n_moves = 0;
}

template <typename T>
bool NumXo_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0) && mark > 0 && mark <= 9 && this->freq[mark] == 0) {
        this->freq[mark] = 1;
        this->board[x][y] = mark;
        this->count++;
        this->n_moves++;
        return true;
    }

    return false;
}

template <typename T>
void NumXo_Board<T>::display_board() {
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

template <typename T>
bool NumXo_Board<T>::is_win() {

    if ((this->board[0][0] + this->board[1][0] + this->board[2][0] == 15) &&
        this->board[0][0] != 0 && this->board[1][0] != 0 && this->board[2][0] != 0) return true;

    if ((this->board[0][1] + this->board[1][1] + this->board[2][1] == 15) &&
        this->board[0][1] != 0 && this->board[1][1] != 0 && this->board[2][1] != 0) return true;

    if ((this->board[0][2] + this->board[1][2] + this->board[2][2] == 15) &&
        this->board[0][2] != 0 && this->board[1][2] != 0 && this->board[2][2] != 0) return true;

    if ((this->board[0][0] + this->board[0][1] + this->board[0][2] == 15) &&
        this->board[0][0] != 0 && this->board[0][1] != 0 && this->board[0][2] != 0) return true;

    if ((this->board[1][0] + this->board[1][1] + this->board[1][2] == 15) &&
        this->board[1][0] != 0 && this->board[1][1] != 0 && this->board[1][2] != 0) return true;

    if ((this->board[2][0] + this->board[2][1] + this->board[2][2] == 15) &&
        this->board[2][0] != 0 && this->board[2][1] != 0 && this->board[2][2] != 0) return true;

    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) &&
        this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) return true;

    if ((this->board[2][0] + this->board[1][1] + this->board[0][2] == 15) &&
        this->board[2][0] != 0 && this->board[1][1] != 0 && this->board[0][2] != 0) return true;

    return false;
}


template <typename T>
bool NumXo_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumXo_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
int NumXo_Board<T>::get_cell(int x, int y) {
    return this->board[x][y];
}




template <typename T>
NumXo_Player<T>::NumXo_Player(string name, T symbol, NumXo_Board<T>* board) : Player<T>(name, symbol) {
    this->boardPtr = board;
}

template <typename T>
void NumXo_Player<T>::getmove(int& x, int& y) {
    NumXo_Board<T>* numXoBoard = dynamic_cast<NumXo_Board<T>*>(this->boardPtr);
    cout << "Numbers available\n";
    vector<int>& temp1 = numXoBoard->numbers;
    vector<int>& temp2 = numXoBoard->freq;
    for (auto i : temp1) cout << i << " ";
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;


    if (x < 0 or x>2 or y < 0 or y>2) {
        cout << "Wrong Move\n";
        return;
    }
    if (numXoBoard->get_cell(x, y)) {
        cout << "There is Number at this place u can't override over it.\n";
        return;
    }

    int num;
    if (numXoBoard->count % 2 == 0) {

        while (true) {
            cout << "Enter Unsed Odd Number [1,3,5,7,9]\n";

            cin >> num;
            if (num % 2 == 1 and num >= 1 and num <= 9)break;
        }
    }
    else
    {
        while (true) {
            cout << "Enter Unsed Even Number [2,4,6,8]\n";
            cin >> num;
            if (num % 2 == 0 and num >= 2 and num <= 8)break;

        }

    }

    this->symbol = num;
    if (numXoBoard->freq[num])cout << "You Already Used This Number\n";
}

template <typename T>
NumXo_Random_Player<T>::NumXo_Random_Player(T symbol, NumXo_Board<T>* board) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    this->boardPtr = board;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void NumXo_Random_Player<T>::getmove(int& x, int& y) {

    NumXo_Board<T>* numXoBoard = dynamic_cast<NumXo_Board<T>*>(this->boardPtr);
    vector<int>& temp1 = numXoBoard->numbers;
    vector<int>& temp2 = numXoBoard->freq;
    while (true) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        if (numXoBoard->count % 2 == 0) {
            int l = rand() % 10;
            if (l and !temp2[l] and l % 2==1) {
                this->symbol = temp1[l-1];
                break;
            }
        }
        else {
            int l = rand() % 10;
            if (l && !temp2[l] && l%2==0) {
                this->symbol = temp1[l-1];
                break;
            }
        }
    }
}

#endif