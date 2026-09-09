@echo off
echo Mengompilasi Flappy Bird...
g++ src/main.cpp -o flappybird.exe -lraylib -lopengl32 -lgdi32 -lwinmm
if %ERRORLEVEL% equ 0 (
    echo Kompilasi berhasil! Menjalankan game...
    start flappybird.exe
) else (
    echo Kompilasi gagal!
    pause
)

