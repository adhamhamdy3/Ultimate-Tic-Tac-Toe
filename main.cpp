#include <iostream>
#include "BoardGame_Classes.h"
#include "Run.h"
using namespace std;


void displayMainMenu() {
    cout << "\n===== Main Menu =====\n";
    cout << "1) Numerical Xo Game\n";
    cout << "2) Connect_4 Game\n";
    cout << "3) Ultimate Xo\n";
    cout << "4)Exit.\n";
    cout << "=====================\n";
    cout << "Enter your choice: ";
}

void numericalXoLoop() {
    RunNumXO();
    while (true) {

        string c;
        cout << "\n--- Numerical Xo Game ---\n";
        cout << "1) Continue the Game\n";
        cout << "2) Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> c;

        if (c == "1") {
            RunNumXO();
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

void connect4Loop() {
    RunConnect4();
    while (true) {
        string c;
        cout << "\n--- Connect_4 Game ---\n";
        cout << "1) Continue the Game\n";
        cout << "2) Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> c;

        if (c == "1") {
            RunConnect4();
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


void UltimateLoop() {
    RunUltimate();
    while (true) {
        string c;
        cout << "\n--- Ultimate Xo Game ---\n";
        cout << "1) Continue the Game\n";
        cout << "2) Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> c;

        if (c == "1") {
            RunUltimate();
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





int main() {
    while (true) {
        string choice;
        displayMainMenu();
        cin >> choice;

        if (choice == "1") {
            numericalXoLoop(); 
        }
        else if (choice == "2") {
            connect4Loop(); 
        }
        else if (choice == "3") {
            UltimateLoop();
        }
        else if (choice == "4") {
            cout << "Exiting the program. Goodbye!\n";
            break; 
        }
        else {
            cout << "Invalid choice. Please select a valid option (1, 2, or 3).\n";
        }
    }

    return 0;
}





