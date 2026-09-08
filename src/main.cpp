#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

// ukuran layar
const int screenWidth = 800;
const int screenHeight = 450;
const float birdRadius = 20.0f;
const float obstacleWidth = 60.0f;

// variabel yang digunakan (di-rename agar tidak bentrok dgn nama fungsi)
int health = 3;
float birdX = 150.0f;              // posisi X burung (tetap, dunia yg bergerak)
float birdY = screenHeight / 2.0f; // posisi Y burung
float birdVelocity = 0.0f;         // kecepatan vertikal burung saat ini
int scoreValue = 0;
float speed = 220.0f;        // kecepatan gerak dunia/obstacle (px/detik)
float upValue = -350.0f;     // kekuatan lompat (negatif = ke atas)
float gravityValue = 900.0f; // percepatan gravitasi (px/detik^2)
float invulnTimer = 0.0f;    // jeda kebal sesaat setelah kena tabrak

bool gameoverState = false;
bool gamestartState = false;

struct Obstacle {
  float x;
  float gapY;      // titik tengah celah
  float gapHeight; // tinggi celah
  bool passed = false;
};

std::vector<Obstacle> obstacles;

void gameinput();
void gamestart();
void Bird();
void score();
void environtment();
void spawnobstacle();
void coallision();
void gameover();

// -----------------------------------------------------------
// Input lompat: tiap kali tombol ditekan, beri kecepatan ke atas.
// Kecepatan itu lalu "dimakan" gravitasi tiap frame di Bird().
// -----------------------------------------------------------
void gameinput() {
  if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) {
    birdVelocity = upValue;
  }
}

// -----------------------------------------------------------
// Cek apakah game dimulai (tekan ENTER di layar start).
// -----------------------------------------------------------
void gamestart() {
  if (IsKeyPressed(KEY_ENTER)) {
    gamestartState = true;
  }
}

// -----------------------------------------------------------
// Update posisi burung berdasarkan gravitasi & kecepatan,
// lalu gambar burungnya.
// Ini seperti bola yang jatuh terus, tapi tiap tombol ditekan
// kecepatannya di-reset ke arah atas (lihat gameinput()).
// -----------------------------------------------------------
void Bird() {
  birdVelocity += gravityValue * GetFrameTime();
  birdY += birdVelocity * GetFrameTime();

  // jangan sampai keluar dari atas layar
  if (birdY - birdRadius < 0) {
    birdY = birdRadius;
    birdVelocity = 0;
  }

  Color birdColor = (invulnTimer > 0.0f) ? Fade(YELLOW, 0.5f) : YELLOW;
  DrawCircle((int)birdX, (int)birdY, birdRadius, birdColor);
}

// -----------------------------------------------------------
// Tambah skor setiap kali burung berhasil melewati sebuah
// obstacle, lalu gambar teks skor di layar.
// -----------------------------------------------------------
void score() {
  for (auto &obs : obstacles) {
    if (!obs.passed && (obs.x + obstacleWidth) < birdX) {
      obs.passed = true;
      scoreValue++;
    }
  }
  DrawText(TextFormat("Score: %d", scoreValue), 10, 10, 20, BLACK);
}

// -----------------------------------------------------------
// Gambar latar (langit + tanah). Nilai gravitasi sudah
// diperbaiki: dulu "6,67 * 10 **-10" (bukan sintaks C++ valid
// dan itu konstanta gravitasi Newton, bukan gravitasi game).
// Nilai gravitasi game diatur di deklarasi gravityValue di atas.
// -----------------------------------------------------------
void environtment() {
  ClearBackground(SKYBLUE);
  DrawRectangle(0, screenHeight - 40, screenWidth, 40, DARKGREEN); // tanah
}

// -----------------------------------------------------------
// Gerakkan semua obstacle ke kiri tiap frame, buang yang sudah
// lewat layar, dan generate obstacle baru secara acak (celahnya
// di posisi Y random) ketika obstacle terakhir sudah cukup jauh.
// -----------------------------------------------------------
void spawnobstacle() {
  for (auto &obs : obstacles) {
    obs.x -= speed * GetFrameTime();
  }

  if (!obstacles.empty() && obstacles.front().x + obstacleWidth < 0) {
    obstacles.erase(obstacles.begin());
  }

  if (obstacles.empty() || obstacles.back().x < screenWidth - 280) {
    Obstacle newObs;
    newObs.x = (float)screenWidth;
    newObs.gapHeight = 150.0f;
    newObs.gapY = (float)GetRandomValue(100, screenHeight - 140);
    obstacles.push_back(newObs);
  }

  for (auto &obs : obstacles) {
    DrawRectangle((int)obs.x, 0, (int)obstacleWidth,
                  (int)(obs.gapY - obs.gapHeight / 2), DARKGREEN);
    DrawRectangle(
        (int)obs.x, (int)(obs.gapY + obs.gapHeight / 2), (int)obstacleWidth,
        (int)(screenHeight - (obs.gapY + obs.gapHeight / 2)), DARKGREEN);
  }
}

// -----------------------------------------------------------
// Cek tabrakan burung dengan tanah atau pipa/obstacle.
// Ada invulnTimer supaya health tidak berkurang berkali-kali
// dalam satu tabrakan yang sama (karena dicek tiap frame).
// -----------------------------------------------------------
void coallision() {
  if (invulnTimer > 0.0f) {
    invulnTimer -= GetFrameTime();
    return;
  }

  Rectangle birdRect = {birdX - birdRadius, birdY - birdRadius, birdRadius * 2,
                        birdRadius * 2};
  bool hit = false;

  if (birdY + birdRadius >= screenHeight - 40) {
    hit = true;
    birdY = screenHeight - 40 - birdRadius;
    birdVelocity = 0;
  }

  for (auto &obs : obstacles) {
    Rectangle topRect = {obs.x, 0, obstacleWidth, obs.gapY - obs.gapHeight / 2};
    Rectangle botRect = {obs.x, obs.gapY + obs.gapHeight / 2, obstacleWidth,
                         screenHeight - (obs.gapY + obs.gapHeight / 2)};

    if (CheckCollisionRecs(birdRect, topRect) ||
        CheckCollisionRecs(birdRect, botRect)) {
      hit = true;
    }
  }

  if (hit) {
    health--;
    invulnTimer = 1.0f; // 1 detik kebal setelah kena
  }
}

// -----------------------------------------------------------
// Cek apakah health habis -> game over, tampilkan pesan,
// dan reset semua state kalau ENTER ditekan lagi.
// -----------------------------------------------------------
void gameover() {
  if (health <= 0) {
    gameoverState = true;
    DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 30, 30,
             RED);
    DrawText("Tekan ENTER untuk main lagi", screenWidth / 2 - 150,
             screenHeight / 2 + 10, 20, BLACK);

    if (IsKeyPressed(KEY_ENTER)) {
      health = 3;
      birdY = screenHeight / 2.0f;
      birdVelocity = 0.0f;
      scoreValue = 0;
      invulnTimer = 0.0f;
      obstacles.clear();
      gameoverState = false;
      gamestartState = false;
    }
  }
}

int main() {
  InitWindow(screenWidth, screenHeight, "Flappy Bird");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    if (!gamestartState) {
      environtment();
      DrawText("Tekan ENTER untuk mulai", screenWidth / 2 - 150,
               screenHeight / 2, 20, BLACK);
      gamestart();
    } else if (gameoverState) {
      environtment();
      gameover();
    } else {
      environtment();
      gameinput();
      Bird();
      spawnobstacle();
      score();
      coallision();
      gameover();
      DrawText(TextFormat("Health: %d", health), screenWidth - 120, 10, 20,
               MAROON);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
