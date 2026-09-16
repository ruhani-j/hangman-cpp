# Hangman C++

A dependency-free terminal Hangman game written in C++17.

## Features

- Randomly selects a word from a built-in word list
- Displays the hangman drawing as misses accumulate
- Accepts one-letter guesses and rejects invalid input
- Detects repeated guesses
- Reports the final word after a win or loss

## Build With CMake

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\hangman.exe
```

On single-configuration generators, the executable may be at `build/hangman.exe`.

## Build Directly With g++

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic src/main.cpp -o hangman.exe
./hangman.exe
```
