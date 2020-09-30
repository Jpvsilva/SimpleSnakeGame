#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>

// Game is over or not
bool gameOver;

// Board Width
const int width = 20;

// Board Height
const int height = 20;

// Snake Positions
int x, y;

// Fruit Position 
int fruitX, fruitY;

// Score
int score;

// Tail Size
int tailX[100], tailY[100];
int nTail;

// Tell Snake to turn into the direction we tell
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

//Ability to lock or passthrough walss
boolean lockWalls;