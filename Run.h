#pragma once
#include "BoardGame_Classes.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "NumXO.h"
#include "Connect4.h"


void RunNumXO() {
    string playerXName, player2Name, choice;
    Player<int>* players[2] = { nullptr, nullptr };
    NumXo_Board<int>* B = new NumXo_Board<int>();

    cout << "Hi!\n";
    cout << "Welcome to FCAI Numerical Tic Tac Toe Game. :)\n";

    // Setup Player X
    cout << "Enter Player X name: ";
    cin >> playerXName;
    while (true) {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == "1") {
            players[0] = new NumXo_Player<int>(playerXName, 1, B);
            break;
        }
        else if (choice == "2") {
            players[0] = new NumXo_Random_Player<int>(1, B);
            break;
        }
        else {
            cout << "Invalid choice for Player X. Please enter '1' or '2'.\n";
        }
    }

    // Setup Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    while (true) {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if (choice == "1") {
            players[1] = new NumXo_Player<int>(player2Name, 2, B);
            break;
        }
        else if (choice == "2") {
            players[1] = new NumXo_Random_Player<int>(2, B);
            break;
        }
        else {
            cout << "Invalid choice for Player 2. Please enter '1' or '2'.\n";
        }
    }


    GameManager<int> Ultimate_TTT(B, players);
    Ultimate_TTT.run();



    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}






void RunConnect4() {
    string player1Name, player2Name, choice;
    Player<char>* players[2];
    Connect4_Board<char>* B = new Connect4_Board<char>();


    cout << "Hi  ";
    cout << "Welcome to FCAI Connect4 Game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    while (true) {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        if (choice == "1")new Connect4_Player<char>(player1Name, 'X');
        else if (choice == "2")new Connect4_Random_Player<char>('X');
        else
            cout << "Invalid choice for Player 2. Please enter '1' or '2'.\n";

    }



    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    while (true) {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        if (choice == "1")new Connect4_Player<char>(player2Name, 'O');
        else if (choice == "2")new Connect4_Random_Player<char>('O');
        else
            cout << "Invalid choice for Player 2. Please enter '1' or '2'.\n";

    }

    GameManager<char> Connect4_game(B, players);
    Connect4_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}



void RunUltimate() {
    string choice;
    Player<char>* players[2];
    Ultimate_Board<char>* B = new Ultimate_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    while (true) {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer Player\n";
        cin >> choice;
        if (choice == "1") {
            players[0] = new Ultimate_TTT_Player<char>(playerXName, 'X', B);
            break;
        }
        else if (choice == "2") {
            players[0] = new Ultimate_TTT_Random_Player<char>('X', B);
            break;
        }
        else {
            cout << "Invalid choice for Player X. Please enter '1' or '2'.\n";
        }
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    while (true) {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer Player\n";
        cin >> choice;
        if (choice == "1") {
            players[1] = new Ultimate_TTT_Player<char>(player2Name, 'O', B);
            break;
        }
        else if (choice == "2") {
            players[1] = new Ultimate_TTT_Random_Player<char>('O', B);
            break;
        }
        else {
            cout << "Invalid choice for Player 2. Please enter '1' or '2'.\n";
        }
    }

    // Create the game manager and run the game
    GameManager<char> Ultimate_TTT(B, players);
    Ultimate_TTT.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
