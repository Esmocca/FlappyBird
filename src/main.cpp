#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "raylib.h"


const int ScreenWidth = 800;
const int ScreenHeight = 400;
const float Birdradius = 15.0f;
const float Obstacle = 60.0f;


const float birdRadius = 15.0f;
const float obstacleWidth = 60.0f;


int health = 3;
float birdX = 150.0f;
float birdY = ScreenHeight / 2.0f;
float birdVelocity = 0.0f
int Score = 0;
float birdVelocity = 0.0f;
int score = 0;
float speed = 220.0f;
float upValue = -350.0f;
float gravityValue = 900.0f;
float delayTimer = 0.0f; 
float delayTimer = 0.0f;

bool gameover = false;
bool gamestart = false;
bool isGameOver = false;
bool isGameStarted = false;

struct obstacle {
struct Obstacle {
    float x;
    float gapY;
    float gapHeight;
    bool passed false;
    bool passed = false;
};

void gameinput () {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed (KEY_UP)) {
        birdVelocity = upValue;
    }
};
std::vector<Obstacle> obstacles;

void resetGame() {
    health = 3;
    birdY = ScreenHeight / 2.0f;
    birdVelocity = 0.0f;
    score = 0;
    delayTimer = 0.0f;
    obstacles.clear();
    isGameOver = false;
}

void gamestart () {
    if (IsKeyPressed(KEY_ENTER)) {
        gamestart = true;
    } else {
        gamestart = false;
void gameinput() {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) {
        birdVelocity = upValue;
    }
}

};

void Bird () {
void Bird() {
    birdVelocity += gravityValue * GetFrameTime();
    birdY += birdVelocity * GetFrameTime();

    // Batas atas langit-langit
    if (birdY - birdRadius < 0) {
        birdY = birdRadius;
        birdVelocity = 0;
    }
    Color birdColor = (delayTimer > 0.0f) ? Fade(YELLOW, 0.05f) : YELLOW;
    DrawCircle((init)birdX, (int)birdY, birdRadius, birdColor);

};
    // Efek berkedip saat kebal setelah terkena hit
    Color birdColor = (delayTimer > 0.0f) ? Fade(YELLOW, 0.4f) : YELLOW;
    DrawCircle((int)birdX, (int)birdY, birdRadius, birdColor);
    DrawCircleLines((int)birdX, (int)birdY, birdRadius, ORANGE);
}

void score () {
void updateScore() {
    for (auto &obs : obstacles) {
        if (!obs.passed && (obs.x + obstacleWidth)< birdX) {
        if (!obs.passed && (obs.x + obstacleWidth) < birdX) {
            obs.passed = true;
            Score++;
            score++;
        }
    }
    DrawText(TextFormat(" Score: %d ", Score), 10, 10, 20, BLACK);
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
}

};

void environtment () {
void environtment() {
    ClearBackground(SKYBLUE);
    DrawRectangle (0, ScreenHeight - 40, ScreenWidth, 40, DARKGREEN );
    DrawRectangle(0, ScreenHeight - 40, ScreenWidth, 40, DARKGREEN);
}

};
void spawnAndMoveObstacles() {
    float dt = GetFrameTime();

void spawnobstacle () {
    if (obstacles.empty() || obstacles.back().x < ScreenWidth - 250) {
        Obstacle newObs;
        newObs.x = (float)ScreenWidth;
        newObs.gapHeight = 130.0f;
        newObs.gapY = (float)GetRandomValue(90, ScreenHeight - 130);
        newObs.passed = false;
        obstacles.push_back(newObs);
    }

    for (auto &obs : obstacles) {
        obs.x -= speed * GetFrameTime();
        obs.x -= speed * dt;
    }

        if (!obstacles.empty() && obstacle.font().x + obstacleWidth < 0 ) {
            obstacles.erase(obstacles.begin());
    if (!obstacles.empty() && (obstacles.front().x + obstacleWidth) < 0) {
        obstacles.erase(obstacles.begin());
    }

        }
        if (obtecles.empty() || obstacles.back().x < ScreenWidth - 280) {
            Obstacle newObs;
            newObs.x = (float)ScreenWidth;
            newObs.gapHeight = 150.0f;
            newObs.gapY = (float)GetRandomValue (100, ScreenHeight - 140);
            obstacles.push_back(newObs);
    for (const auto &obs : obstacles) {
        float topHeight = obs.gapY - obs.gapHeight / 2.0f;
        float bottomY = obs.gapY + obs.gapHeight / 2.0f;
        float bottomHeight = (ScreenHeight - 40) - bottomY;

        }
        DrawRectangle((int)obs.x, 0, (int)obstacleWidth, (int)topHeight, DARKGREEN);
        DrawRectangleLines((int)obs.x, 0, (int)obstacleWidth, (int)topHeight, BLACK);

        for (auto &obs : obstacles) {
            DrawRectangle((int) obs.x, 0. (int)obstacleWidth, (int)(obs.gapY - obs.gapHeight / 2), DARKGREEN);
            DrawRectangle((int) obs.x, (int)(obs.gapY + obs.gapHeight /2), (int)obstacleWidth, (int)(ScreenHeight -  (obsgapY + obs.gapHeight / 2)), DARKGREEN);
            
        }

        DrawRectangle((int)obs.x, (int)bottomY, (int)obstacleWidth, (int)bottomHeight, DARKGREEN);
        DrawRectangleLines((int)obs.x, (int)bottomY, (int)obstacleWidth, (int)bottomHeight, BLACK);
    }
};
}

void coallision () {
void collision() {
    if (delayTimer > 0.0f) {
        delayTimer -= GetFrameTime();
        return;
    }

    Rectangle birdRect = { birdX - birdRadius, birdY - birdRadius, birdRadius * 2, birdRadius * 2 };
    bool hit = false;

    if (birdY + birdRadius >= ScreenHeight - 40) {
        hit = true;

        birdY = ScreenHeight - 40 - birdRadius;
        birdVelocity = 0;
    }

    for (auto &obs : obstacles) {
        Rectangle topRect = { obs.x, 0, obstacleWidth, obs.gapY - obs.gapHeight / 2 };
        Rectangle bottomRect = { obs.x, obs.gapY + obs.gapHeight / 2, obstacleWidth, ScreenHeight - (obs.gapY + obs.gapHeight / 2) };
    for (const auto &obs : obstacles) {
        float topHeight = obs.gapY - obs.gapHeight / 2.0f;
        float bottomY = obs.gapY + obs.gapHeight / 2.0f;
        float bottomHeight = (ScreenHeight - 40) - bottomY;

        Rectangle topRect = { obs.x, 0, obstacleWidth, topHeight };
        Rectangle bottomRect = { obs.x, bottomY, obstacleWidth, bottomHeight };

        if (CheckCollisionRecs(birdRect, topRect) || CheckCollisionRecs(birdRect, bottomRect)) {
            hit = true;
        }
    }

    if (hit){
    if (hit && delayTimer <= 0.0f) {
        health--;
        delayTimer = 1.0f;
    }

};

void gameover () {
    if (health <= 0) {
        gameover = true;
        DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 30, 30, RED);
        DrawText("Tekan ENTER untuk main lagi", screenWidth / 2 - 150, screenHeight / 2 + 10, 20, BLACK);
        isGameOver = true;
    }
}

        if (isKeyPressed(KEY_ENTER)) {
            health = 3;
            birdY = ScreenHeight / 2.0f;
            birdVelocity = 0.0f;
            Score = 0;
            delayTimer = 0.0f;
            obstacles.clear();
            gameover = false;
            gamestart = false;
        }
    } 
};
void handleGameOver() {
    DrawText("GAME OVER", ScreenWidth / 2 - 100, ScreenHeight / 2 - 40, 30, RED);
    DrawText("Tekan ENTER untuk main lagi", ScreenWidth / 2 - 140, ScreenHeight / 2 + 10, 20, DARKGRAY);

int main () {
    if (IsKeyPressed(KEY_ENTER)) {
        resetGame();
    }
}

int main() {
    InitWindow(ScreenWidth, ScreenHeight, "Flappy Bird");
    SetTargetFPS(60);
    while (windowShouldClose() == false) {

    while (!WindowShouldClose()) {
        BeginDrawing();
        environtment();
        if (!gamestart) {
            DrawText("Tekan ENTER untuk mulai", ScreenWidth / 2 - 150, ScreenHeight / 2 - 30, 20, BLACK);

        if (!isGameStarted) {

            DrawText("FLAPPY BIRD", ScreenWidth / 2 - 120, ScreenHeight / 2 - 60, 35, DARKBLUE);
            DrawText("Tekan ENTER atau SPASI untuk mulai", ScreenWidth / 2 - 170, ScreenHeight / 2, 20, BLACK);

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                isGameStarted = true;
                resetGame();
            }
        } else {
            gameinput();
            Bird();
            spawnobstacle();
            coallision();
            score();
            gameover();
            if (!isGameOver) {
                gameinput();
                Bird();
                spawnAndMoveObstacles();
                collision();
                updateScore();
                DrawText(TextFormat("Health: %d", health), ScreenWidth - 120, 10, 20, MAROON);
            } else {

            DrawText(TextFormat("Health: %d", health), screenWidth - 120, 10, 20, MAROON);
                Bird();

                for (const auto &obs : obstacles) {
                    float topHeight = obs.gapY - obs.gapHeight / 2.0f;
                    float bottomY = obs.gapY + obs.gapHeight / 2.0f;
                    float bottomHeight = (ScreenHeight - 40) - bottomY;
                    DrawRectangle((int)obs.x, 0, (int)obstacleWidth, (int)topHeight, DARKGREEN);
                    DrawRectangle((int)obs.x, (int)bottomY, (int)obstacleWidth, (int)bottomHeight, DARKGREEN);
                }
                updateScore();
                handleGameOver();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;

}
