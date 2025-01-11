#include <iostream>
using namespace std;

void SnakeGame();
void Minesweeper();
void TicTacToe();

void displayMenu() {
   cout << "========================="<<endl;
   cout<<"--Welcome to Console Based Gaming Suite--"<<endl;
   cout << "========================="<<endl;
   cout << "1. Tic-Tac-Toe"<<endl;
   cout << "2. Snake Game"<<endl;
   cout << "3. Hangman"<<endl;
   cout << "0. Exit"<<endl;
   cout << "Select a game to play: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
               // 
                break;
            case 2:
               //  snakeGame();
                break;
            case 3:
               //  hangman();
                break;
            // Add cases for other games
            case 0:
                cout << "Exiting the game suite. Goodbye!"<<endl;
                return 0;
                break;
            default:
                cout << "Invalid choice. Please try again."<<endl;
        }
    } while (choice != 0);
    return 0;
}
