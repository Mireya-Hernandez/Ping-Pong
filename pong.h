/**************************************************************
* File   : DataStructure.cpp
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose: header file for the main application for the pong 
* game
*************************************************************/
#include <Windows.h>  // console graphics on windows
#ifndef PONG_H
#define PONG_H

//screen dimesion constants
const int SCREEN_OFFSET = 2; //Distance walls are from sceen edge

//wall dimension constants
const int WALL_THICKNESS = 1; // How thick is a wall in pixels

//Screen Demensions
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 128;


//Ball Demensions
const int BALL_WIDTH = 6;
const int BALL_HEIGHT = 6;

// define color constants
const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF PAINT = WHITE;

//paddle dimension constants
const int PADDLE_HEIGHT = 28;
const int PADDLE_WIDTH = 2;
const int PADDLE_OFFSET = 4; //distance from wall

// ball dimension constants
const int BALL_START_X = SCREEN_WIDTH / 12;
const int BALL_START_Y = SCREEN_HEIGHT / 8;
const int BALL_START_VEL_X = 2;
const int BALL_START_VEL_Y = 2;

//Update Frame Rate in Milliseconds
const float Frame_Rate = 1000 / 60; // = 16.66666666



//the ball as an array
const COLORREF BALL_PATTERN[BALL_HEIGHT][BALL_WIDTH] = {
	{BLACK, BLACK, PAINT, PAINT, BLACK, BLACK},
	{BLACK, PAINT, PAINT, PAINT, PAINT, BLACK},
	{PAINT, PAINT, PAINT, PAINT, PAINT, PAINT},
	{PAINT, PAINT, PAINT, PAINT, PAINT, PAINT},
	{BLACK, PAINT, PAINT, PAINT, PAINT, BLACK},
	{BLACK, BLACK, PAINT, PAINT, BLACK, BLACK} };

// key input & directions
enum InputDirections {
	STOP,
	NONE,
	HIGH,
	LOW,
	LEFT,
	RIGHT
};


//Position coordination structure
struct Position {
	float xValue;
	float yValue;
};

struct GameObjects {
	float xpos;
	float ypos;
	float xposl;
	float yposl;
	float xvel;
	float yvel;
};



#endif