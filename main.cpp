#include <iostream>
#include "BoardGame_Classes.h"
#include "Run.h"
using namespace std;

void gameLoop(void (*runGame)()) {
    runGame();
    while (true) {
        string c;
        cout << "\n1) Continue the Game\n";
        cout << "2) Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> c;

        if (c == "1") {
            runGame();
            continue;
        }
        else if (c == "2") {
            break;
        }
        else {
            cout << "Invalid choice. Please select 1 or 2.\n";
        }
    }
}

void displayMainMenu() {
    cout << "\n===== Main Menu =====\n";
    cout<< "1-  Pyramid Tic-Tac-Toe\n";
    cout <<"2-  Four-in-a-row\n";
    cout <<"3-  5 x 5 Tic Tac Toe\n";
    cout <<"4-  Word Tic-tac-toe\n";
    cout <<"5-  Numerical Tic-Tac-Toe\n";
    cout <<"6-  Misere Tic Tac Toe\n";
    cout <<"7-  4 x 4 Tic-Tac-Toe\n";
    cout << "8- Ultimate Tic Tac Toe\n";
    cout << "9) Exit\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

int main() {
    while (true) {
        string choice;
        displayMainMenu();
        cin >> choice;

        if (choice == "1") {
            gameLoop(RunPyramids);
           
        }
        else if (choice == "2") {
            gameLoop(RunConnect4);
        }
        else if (choice == "3") {
            gameLoop(RunGame3);
            
        }
        else if (choice == "4") {
            gameLoop(RunWordXo);
            
        }
        else if (choice == "5") {
           
             gameLoop(RunNumXO);
        }
        else if (choice == "6") {
             gameLoop(RunGame6);
           
        }
        else if (choice == "7") {
             gameLoop(RunGame7);
            
        }
        else if(choice=="8"){
            gameLoop(RunUltimate);
        }
        else if (choice == "9") {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid option (1-9).\n";
        }
    }

    return 0;
}
