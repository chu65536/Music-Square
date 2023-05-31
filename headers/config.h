#pragma once

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 1000

#define PLATFORM_HEIGHT 10
#define PLATFORM_WIDTH 25
#define C_SIZE 25
#define C_HSIZE C_SIZE / 2

// 1000 / (DX * VELOCITY * FPS) - should be int, otherwise will affect intendent speed
// In case this value == 0, everything is gonna be dead :)
// In case ms % this value != 0, 
#define DX 1
#define DY 1
#define VELOCITY 1
#define FPS 100