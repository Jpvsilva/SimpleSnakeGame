// SimpleSnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Header.h"

using namespace std;

void placeFruit()
{
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void setupGame()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    placeFruit();
    score = 0;
}

// Print board
void drawBoard()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

// Keyboard keys handler
void getInputKeys()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) { 
                dir = LEFT; 
            }
            break;
        case 'd':
            if (dir != LEFT) { 
                dir = RIGHT; 
            }
            break;
        case 'w':
            if (dir != DOWN) { 
                dir = UP; 
            }
            break;
        case 's':
            if (dir != UP) { 
                dir = DOWN; 
            }
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void gameLogic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i <= nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (lockWalls) {
        if (x > width || x < 0 || y > height || y < 0)
            gameOver = true;
    }
    else {
        if (x >= width) x = 0;
        else if (x < 0) x = width - 1;

        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;

    }
    
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        placeFruit();
        nTail++;
    }
}

void startGame() {
    setupGame();
    while (!gameOver) {
        drawBoard();
        getInputKeys();
        gameLogic();
        Sleep(100);
    }
}

int main()
{
    char choice;
    char choose = false;
    std::cout << "Welcome To Snake!\n";
    std::cout << "Want to Lock the Walls? (Y/N) ";
    cin >> choice;
    while (!choose){
        switch (toupper(choice)) {
        case 'Y':
            lockWalls = true;
            startGame();
            choose = true;
            break;
        case 'N':
            lockWalls = false;
            startGame();
            choose = true;
            break;
        default:
            std::cout << "Invalid!! Please type Y or N to lock walls. ";
            cin >> choice;
            break;
        }

    }
    return 0;

    std::cout << "Your Score was: " << score << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
