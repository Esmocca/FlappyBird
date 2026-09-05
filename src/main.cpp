#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "raylib.h"

const int ScreenWidth = ;
const int ScreenHeight = ;
const float Birdradius = ;
const float Obstacle = ;


bool gameover = false;
bool gamestart = false;

void gameinput () {

};


void gamestart () {
    if (GetAsyncKeyState(VK_RETURN) & 0X8000) {
        gamestart = true;
        Sleep(500);
    } else {
        gamestart = false;
    }

};

void Bird () {

};

void score () {

};

void environtment () {
    gravity = 6,67 * 10 **-10

};

void spawnobstacle () {

};

void coallision () {

};

void gameover () {
    if (health <= 0) {
        gameover = true;
    } 
};

int main () {
    gamestart();

}