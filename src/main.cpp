#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "raylib.h"

const int ScreenWidth = 800;
const int ScreenHeight = 400;
const float Birdradius = 15.0f;
const float Obstacle = 60.0f;


int health = 3;
float birdX = 150.0f;
float birdY = ScreenHeight / 2.0f;
float birdVelocity = 0.0f
int Score = 0;
float speed = 220.0f;
float upValue = -350.0f;
float gravityValue = 900.0f;
float delayTimer = 0.0f; 

bool gameover = false;
bool gamestart = false;

struct obstacle {
    float x;
    float gapY;
    float gapHeight;
    bool passed false;
};

void gameinput () {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed (KEY_UP)) {
        birdVelocity = upValue;
    }
};


void gamestart () {
    if (IsKeyPressed(KEY_ENTER)) {
        gamestart = true;
    } else {
        gamestart = false;
    }

};

void Bird () {
    birdVelocity += gravityValue * GetFrameTime();
    birdY += birdVelocity * GetFrameTime();
    if (birdY - birdRadius < 0) {
        birdY = birdRadius;
        birdVelocity = 0;
    }
    Color birdColor = (delayTimer > 0.0f) ? Fade(YELLOW, 0.05f) : YELLOW;
    DrawCircle((init)birdX, (int)birdY, birdRadius, birdColor);

};

void score () {
    for (auto &obs : obstacles) {
        if (!obs.passed && (obs.x + obstacleWidth)< birdX) {
            obs.passed = true;
            Score++;
        }
    }
    DrawText(TextFormat(" Score: %d ", Score), 10, 10, 20, BLACK);

};

void environtment () {
    ClearBackground(SKYBLUE);
    DrawRectangle (0, ScreenHeight - 40, ScreenWidth, 40, DARKGREEN );

};

void spawnobstacle () {
    for (auto &obs : obstacles) {
        obs.x -= speed * GetFrameTime();

        if (!obstacles.empty() && obstacle.font().x + obstacleWidth < 0 ) {
            obstacles.erase(obstacles.begin());

        }
        if (obtecles.empty() || obstacles.back().x < ScreenWidth - 280) {
            Obstacle newObs;
            newObs.x = (float)ScreenWidth;
            newObs.gapHeight = 150.0f;
            newObs.gapY = (float)GetRandomValue (100, ScreenHeight - 140);
            obstacles.push_back(newObs);

        }

        for (auto &obs : obstacles) {
            DrawRectangle((int) obs.x, 0. (int)obstacleWidth, (int)(obs.gapY - obs.gapHeight / 2), DARKGREEN);
            DrawRectangle((int) obs.x, (int)(obs.gapY + obs.gapHeight /2), (int)obstacleWidth, (int)(ScreenHeight -  (obsgapY + obs.gapHeight / 2)), DARKGREEN);
            
        }

    }
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
