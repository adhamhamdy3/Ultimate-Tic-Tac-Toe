#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iomanip>
#include <map>
#include <utility>

template<typename T>
class Local_Board : public Board<T> {
private:
    void initBoard();
public:
    T winner;
    Local_Board();
    ~Local_Board();
    bool update_board(const int& x, const int& y, const T& symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
//    void cleanUp();
//    void resetBoard() override;
};

template<typename T>
Local_Board<T>::~Local_Board() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }

    delete this->board;
}

template<typename T>
bool Local_Board<T>::game_is_over() {
    return this->is_win() || this->is_draw();

}

template<typename T>
bool Local_Board<T>::is_draw() {
    return (this->n_moves == 9 && !(this->is_win()));

}

template<typename T>
bool Local_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            if(this->board[i][0] != ' '){
                this->winner = this->board[i][0];
            }
            else {
                this->winner = this->board[0][i];
            }
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        if(this->board[0][0] != ' '){
            this->winner = this->board[0][0];
        }
        else {
            this->winner = this->board[0][2];
        }
        return true;
    }

    return false;
}

template<typename T>
void Local_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " ||";
        }
        cout << "\n-----------------------------";
    }
    //cout << endl;
}

template<typename T>
bool Local_Board<T>::update_board(const int &x, const int &y, const T &symbol) {
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || symbol == ' ')){
        if (symbol == ' '){
            this->n_moves--;
            this->board[x][y] = ' ';
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol); // loop better
        }
        return true;
    }
    return false;
}

template<typename T>
void Local_Board<T>::initBoard() {
    this->board = new char*[this->rows];

    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];

        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = ' ';
        }
    }
}

template<typename T>
Local_Board<T>::Local_Board() {
    this->rows = this->columns = 3;
    this->n_moves = 0;
    winner = ' ';
    initBoard();
}

/*==================================================================================================*/

template<typename T>
class Ultimate_Board : public Board<T> {
public:
    T ultimateWinner;
    Local_Board<T>* boards[3][3];
public:
    int currentBoard_X, currentBoard_Y;
    T localWinners[3][3];
    Ultimate_Board();
    ~Ultimate_Board();
    bool canPickBoard;
    bool update_board(const int& x, const int& y, const T& symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void pickBoard();
    bool isEmpty() const;
};

template<typename T>
bool Ultimate_Board<T>::isEmpty() const{
    return this->currentBoard_X == -1 && this->currentBoard_Y == -1;
}

template<typename T>
void Ultimate_Board<T>::pickBoard() {
    cout << "Enter your board coordinates (x, y)" << endl;
    int x, y;
    cin >> x >> y;
    this->currentBoard_X = x;
    this->currentBoard_Y = y;
    this->canPickBoard = false;
}

template<typename T>
bool Ultimate_Board<T>::is_draw() {
    bool draw = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(this->localWinners[i][j] == ' '){
                draw = false;
            }
        }
    }

    return ((this->n_moves == 81 || draw) && !this->is_win());
}

template<typename T>
bool Ultimate_Board<T>::game_is_over() {
    return this->is_win() || this->is_draw();
}

template<typename T>
bool Ultimate_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->localWinners[i][0] == this->localWinners[i][1] && this->localWinners[i][1] == this->localWinners[i][2] && this->localWinners[i][0] != ' ') ||
            (this->localWinners[0][i] == this->localWinners[1][i] && this->localWinners[1][i] == this->localWinners[2][i] && this->localWinners[0][i] != ' ')) {

            this->ultimateWinner = this->localWinners[i][0];
            return true;
        }
    }

    if ((this->localWinners[0][0] == this->localWinners[1][1] && this->localWinners[1][1] == this->localWinners[2][2] && this->localWinners[0][0] != ' ') ||
        (this->localWinners[0][2] == this->localWinners[1][1] && this->localWinners[1][1] == this->localWinners[2][0] && this->localWinners[0][2] != ' ')) {

        this->ultimateWinner = this->localWinners[1][1];
        return true;
    }

    return false;
}

template<typename T>
void Ultimate_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->boards[i][j]->display_board();
        }
        cout << "==========================================================================================" << endl;
    }
    cout << endl;
}

template<typename T>
bool Ultimate_Board<T>::update_board(const int &x, const int &y, const T &symbol) {
    bool isEnabled = (this->localWinners[this->currentBoard_X][this->currentBoard_Y] == ' ');

    if (!isEnabled){
        canPickBoard = true;
        return false;
    }

    bool ret = this->boards[this->currentBoard_X][this->currentBoard_Y]->update_board(x, y, symbol);
    if (ret){
        if (this->boards[this->currentBoard_X][this->currentBoard_Y]->is_win()){
            this->localWinners[this->currentBoard_X][this->currentBoard_Y] = this->boards[this->currentBoard_X][this->currentBoard_Y]->winner;
            this->canPickBoard = true;
        }
        this->currentBoard_X = x;
        this->currentBoard_Y = y;
        this->n_moves++;
    }
    return ret;
}

template<typename T>
Ultimate_Board<T>::~Ultimate_Board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            delete this->boards[i][j];
        }
    }
}

template<typename T>
Ultimate_Board<T>::Ultimate_Board() {
    this->rows = this->columns = 3;
    this->canPickBoard = true;
    this->currentBoard_X = this->currentBoard_Y = -1;
    this->board = nullptr;

    this->ultimateWinner = ' ';

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->boards[i][j] = new Local_Board<T>();
            this->localWinners[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

/*=======================================================================================*/

template<typename T>
class Ultimate_TTT_Player : public Player<T>{
public:
    Ultimate_TTT_Player(const string& name, const T& s);
    void getmove(int &x, int &y) override;
};

template<typename T>
void Ultimate_TTT_Player<T>::getmove(int &x, int &y) {
    auto* ultimateBoard = dynamic_cast<Ultimate_Board<T>*>(this->boardPtr);
    if (ultimateBoard) {
        if (ultimateBoard->canPickBoard) {
            cout << "You can pick any local board you want to pick a cell from." << endl;
            ultimateBoard->pickBoard();
        } else {
            cout << "You are allowed to pick from local board at coordinates ("
                 << ultimateBoard->currentBoard_X << ", " << ultimateBoard->currentBoard_Y << ") only.";
        }
    } else {
        cout << "Error: Board is not an Ultimate Board.\n";
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


template<typename T>
Ultimate_TTT_Player<T>::Ultimate_TTT_Player(const string &name, const T &s) : Player<T>(name, s) {}

#endif //ULTIMATE_TIC_TAC_TOE_H
