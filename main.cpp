#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void registerUser();
bool loginUser();
void displayLoginMenu();
void displayMainMenu();
void SnakeGame();
void TicTacToe();
void displayBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool isFull(char board[3][3]);
void Hangman(); 
void NumberGuess();

int main() {
    srand(time(0));
    int choice;
    bool loggedIn = false;

    do {
        displayLoginMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser();
                if (loggedIn) {
                    cout << "Login successful! Welcome to the Gaming Suite!" << endl;
                } else {
                    cout << "Invalid credentials. Please try again." << endl;
                }
                break;
            case 0:
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (!loggedIn);

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                TicTacToe();
                break;
            case 2:
                SnakeGame();
                break;
            case 3:
                NumberGuess(); 
                break;
            case 0:
                cout << "Exiting the game suite. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayLoginMenu() {
    cout << "===============================" << endl;
    cout << "Welcome to Console Gaming Suite" << endl;
    cout << "===============================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayMainMenu() {
    cout << "=========================" << endl;
    cout << "--Welcome to Console Based Gaming Suite--" << endl;
    cout << "=========================" << endl;
    cout << "1. Tic-Tac-Toe" << endl;
    cout << "2. Snake Game" << endl;
    cout << "3. Number Guessing Game" << endl;
    cout << "3. Hangman" << endl;
    cout << "0. Exit" << endl;
    cout << "Select a game to play: ";
}

void registerUser() {
    string username, password;
    cout << "Register a new account" << endl;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream outFile("users.txt", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        outFile.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

bool loginUser() {
    string username, password, storedUser, storedPass;
    cout << "Login to your account" << endl;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream inFile("users.txt");
    if (inFile.is_open()) {
        while (inFile >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == password) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }

    return false;
}

void TicTacToe() {
    char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
    char currentPlayer = 'X';
    int move;
    bool gameWon = false;

    cout << "Welcome to Tic Tac Toe!" << endl;
    displayBoard(board);

    while (!gameWon && !isFull(board)) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;

        if (move < 1 || move > 9) {
            cout << "Invalid move. Please try again." << endl;
            continue;
        }

        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Spot already taken. Please try again." << endl;
            continue;
        }

        board[row][col] = currentPlayer;
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!" << endl;
            gameWon = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    if (!gameWon) {
        cout << "It's a draw!" << endl;
    }
}

void displayBoard(char board[3][3]) {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "--+---+--" << endl;
    }
    cout << endl;
}

bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool isFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

const int WIDTH = 20;
const int HEIGHT = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100], tailLength;
bool isGameOver;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction currentDirection;

void initializeGame() {
    isGameOver = false;
    currentDirection = STOP;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
}

void render() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#";
            if (i == headY && j == headX) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "F";
            else {
                bool tailFound = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        tailFound = true;
                    }
                }
                if (!tailFound) cout << " ";
            }
            if (j == WIDTH - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (currentDirection != RIGHT) currentDirection = LEFT;
            break;
        case 'd':
            if (currentDirection != LEFT) currentDirection = RIGHT;
            break;
        case 'w':
            if (currentDirection != DOWN) currentDirection = UP;
            break;
        case 's':
            if (currentDirection != UP) currentDirection = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

void updateLogic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (currentDirection) {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    if (headX >= WIDTH || headX < 0 || headY >= HEIGHT || headY < 0) isGameOver = true;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == headX && tailY[i] == headY) isGameOver = true;
    }

    if (headX == fruitX && headY == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
}

void SnakeGame() {
    initializeGame();
    while (!isGameOver) {
        render();
        handleInput();
        updateLogic();
        Sleep(100);
    }
    cout << "Game Over!" << endl;
}

void Hangman() {
    cout << "Hangman is under development!" << endl;
}

void NumberGuess() {
    cout << "Welcome to the Number Guessing Game!" << endl;
    int guess;

    while (true) {
        int secretNumber = rand() % 20 + 1; 
        cout << "Enter a random number (1-20) (-1 to Quit): ";
        cin >> guess;

        if (guess == -1) {
            cout << "You chose to quit. Game Over!" << endl;
            break;
        }

        if (guess == secretNumber) {
            cout << "Congrats! You guessed the correct number: " << secretNumber << endl;
            break;
        } else {
            cout << "Incorrect guess! The secret number was: " << secretNumber << endl;
        }
    }
}
