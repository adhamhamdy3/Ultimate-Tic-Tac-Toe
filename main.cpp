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
    cout << "1) Numerical Xo Game\n";
    cout << "2) Connect_4 Game\n";
    cout << "3) Ultimate Xo\n";
    cout << "4) Game 3\n";
    cout << "5) Game 6\n";
    cout << "6) Game 7\n";
    cout << "7) Exit\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

int main() {
    while (true) {
        string choice;
        displayMainMenu();
        cin >> choice;

        if (choice == "1") {
            gameLoop(RunNumXO);
        }
        else if (choice == "2") {
            gameLoop(RunConnect4);
        }
        else if (choice == "3") {
            gameLoop(RunUltimate);
        }
        else if (choice == "4") {
            gameLoop(RunGame3);
        }
        else if (choice == "5") {
            gameLoop(RunGame6);
        }
        else if (choice == "6") {
            gameLoop(RunGame7);
        }
        else if (choice == "7") {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid option (1-7).\n";
        }
    }

    return 0;
}
