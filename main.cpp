#include "BoardGame_Classes.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "NumXO.h"
#include "Connect4.h"
#include "Game3.h"
#include "Game6.h"
#include "Game7.h"
#include "Pyramid_TicTacToe.h"
#include "Word_TicTacToe.h"
#include"P_TTT_AI_Player.h"
#include <bits/stdc++.h>
using namespace std ;
void DisplayGames() {
    cout << "1) Pyramid Tic Tac Toe." << endl;
    cout << "2) Four-in-a-row." << endl;
    cout << "3) 5 x 5 Tic Tac Toe." << endl;
    cout << "4) Word Tic Tac Toe." << endl;
    cout << "5) Numerical Tic Tac Toe." << endl;
    cout << "6) Misere Tic Tac Toe." << endl;
    cout << "7) 4 x 4 Tic Tac Toe." << endl;
    cout << "8) Ultimate Tic Tac Toe." << endl;
}
void RunProgram() {
    cout << "welcome To our X-O Games \n";
    Player<char>* players[2];
    Board<char>* B ;
    DisplayGames();
    string player1Name, player2Name;
    int choice;
    cout << "Enter Number Of Game  : ";
    cin >> choice;
    while(cin.fail() || (choice < 1 || choice > 8)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input\n";
        DisplayGames();
        cout << "Enter Number Of Game  : ";
        cin >> choice;
    }
    bool f = choice == 1 ;
    int type1 , type2;
    cout << "Enter name Of first player : ";
    cin >> player1Name;
    cout << "1 - human\n2 - Random\n";
    if (f)cout << "3 - AI\n";
    cout << "Enter Type Of first player : ";
    cin >> type1;
    while(cin.fail() || (type1 < 1 || type1 > 3 ) || (type1 == 3 && !f) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input\n";
        cout << "1 - human\n2 - Random\n";
        if (f)cout << "3 - AI\n";
        cin >> type1;
    }
    cout << "Enter name of second player : ";
    cin >> player2Name;
    cout << "1 - human\n2 - Random\n";
    if (f)cout << "3 - AI\n";
    cout << "Enter Type Of second player : ";
    cin >> type2;
    while(cin.fail() || (type2 < 1 || type2 > 3 ) || (type2 == 3 && !f) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input\n";
        cout << "1 - human\n2 - Random\n";
        if (f)cout << "3 - AI\n";
        cin >> type2;
    }

    if (choice == 1 ) {
        B = new Pyramid_TicTacToe_Board<char>();
        if (type1 == 1 )players[0] = new P_TTT_Player<char>(player1Name, 'X');
        else if (type1 == 2 )players[0] = new P_TTT_Random_Player<char>('X');
        else if (type1 == 3 )players[0] = new P_TTT_AI_Player<char>('X') , players[0]->setBoard(B);
        if (type2 == 1 )players[1] = new P_TTT_Player<char>(player2Name, 'O');
        else if (type2 == 2 )players[1] = new P_TTT_Random_Player<char>('O');
        else if (type2 == 3 )players[1] = new P_TTT_AI_Player<char>('O') , players[1]->setBoard(B);
    }
    else if (choice == 2 ) {
        B = new Connect4_Board<char>();
        if (type1 == 1 )players[0] = new Connect4_Player<char>(player1Name, 'X');
        else if (type1 == 2 )players[0] = new Connect4_Random_Player<char>('X');
        if (type2 == 1 )players[1] = new Connect4_Player<char>(player2Name, 'O');
        else if (type2 == 2 )players[1] = new Connect4_Random_Player<char>('O');
    }
    else if (choice == 3 ) {
        B = new X_O_Board_3<char>();
        if (type1 == 1 )players[0] = new X_O_Player_3<char>('X' , player1Name);
        else if (type1 == 2 )players[0] = new X_O_RandomPlayer_3<char>('X' , player1Name);
        if (type2 == 1 )players[1] = new X_O_Player_3<char>('O' , player2Name);
        else if (type2 == 2 )players[1] = new X_O_RandomPlayer_3<char>('O' , player2Name);
    }
    else if (choice == 4 ) {
        B = new Word_TicTacToe_Board<char>();
        if (type1 == 1 )players[0] = new  W_TTT_Player<char>(player1Name, 'X');
        else if (type1 == 2 )players[0] = new W_TTT_Random_Player<char>('X');
        if (type2 == 1 )players[1] = new  W_TTT_Player<char>(player2Name, 'O');
        else if (type2 == 2 )players[1] = new W_TTT_Random_Player<char>('O');
    }
    else if (choice == 5 ) {
        NumXo_Board<int>* b = new NumXo_Board<int>();
        Player<int>* Players[2] = { nullptr, nullptr };
        if (type1 == 1 )Players[0] = new NumXo_Player<int>(player1Name, 1, b);
        else if (type1 == 2 )Players[0] = new NumXo_Random_Player<int>(1, b);
        if (type2 == 1 )Players[1] = new NumXo_Player<int>(player2Name, 2, b);
        else if (type2 == 2 )Players[1] = new NumXo_Random_Player<int>(2, b);
        GameManager<int> Ultimate_TTT(b, Players);
        Ultimate_TTT.run();
        return;
    }
    else if (choice == 6 ) {
        B = new X_O_Board_6<char>();
        if (type1 == 1 )players[0] = new X_O_Player_6<char>('X' , player1Name);
        else if (type1 == 2 )players[0] = new X_O_RandomPlayer_6<char>('X' , player1Name);
        if (type2 == 1 )players[1] = new X_O_Player_6<char>('O' , player2Name);
        else if (type2 == 2 )players[1] = new X_O_RandomPlayer_6<char>('O' , player2Name);
    }
    else if (choice == 7 ) {
        B = new X_O_Board_7<char>();
        if (type1 == 1 )players[0] = new X_O_Player_7<char>('X' , player1Name);
        else if (type1 == 2 )players[0] = new X_O_RandomPlayer_7<char>('X' , player1Name);
        if (type2 == 1 )players[1] = new X_O_Player_7<char>('O' , player2Name);
        else if (type2 == 2 )players[1] = new X_O_RandomPlayer_7<char>('O' , player2Name);
    }
    else if (choice == 8 ) {
        Ultimate_Board<char>* b = new Ultimate_Board<char>();
        if (type1 == 1 )players[0] = new Ultimate_TTT_Player<char>(player1Name, 'X', b);
        else if (type1 == 2 )players[0] = new Ultimate_TTT_Random_Player<char>('X', b);
        if (type2 == 1 )players[1] = new Ultimate_TTT_Player<char>(player2Name, 'O', b);
        else if (type2 == 2 )players[1] = new Ultimate_TTT_Random_Player<char>('O', b);
        GameManager<char> Ultimate_TTT(b, players);
        Ultimate_TTT.run();
        return;

    }
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
int main () {
    cout << "1 - Run The program\n2 - Exit\n";
    int choice;
    cin >> choice;
    while(cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input\n";
        cout << "1 - Run The program\n2 - Exit\n";
        cin >> choice;
    }
    while(choice == 1 ) {
        RunProgram();
        cout << "1 - Run The program\n2 - Exit\n";
        cin >> choice;
        while(cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input\n";
            cout << "1 - Run The program\n2 - Exit\n";
            cin >> choice;
        }
    }
    return 0 ;
}

