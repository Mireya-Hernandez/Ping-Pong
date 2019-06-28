/**************************************************************
* File   : DataStructure.cpp
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose: main application
*************************************************************/

#include <iostream>   // input/output stream
#include <time.h>      // for timing methods
#include "PongTable.h" // Pong Game Object

using namespace std;

//Function prototypes
HDC initConsole();

bool processInput(PongTable &table);

InputDirections playerInput();

bool update(PongTable &table);


int main()
{
	/* intialize console windpw and Get
	  a handle to its device context
	  for drawling */
	HDC hdc = initConsole();

	/******************************************************/
	/* declare and intialize time components for frame
	   rate calculation*/
	LARGE_INTEGER frequency;  // Factor of how fast CPU clock ticks
	LARGE_INTEGER lastTime;  //When last frame started
	LARGE_INTEGER currentTime; //when current frame started
	LARGE_INTEGER elapsedTime; // time between last and current
	float deltaTime = 0;   // left over frame time

	// get cpu clock frequency
	QueryPerformanceFrequency(&frequency);

	// set starting current time to now
	QueryPerformanceCounter(&currentTime);
	// set initial last time to starting time
	lastTime = currentTime;
	/******************************************************/

	PongTable table = PongTable();
	
	// draw ball
	table.render(hdc, 0);

	bool play = !(update(table));

	while (play)	// enter game to play
	{
		// get current frame times
		QueryPerformanceCounter(&currentTime);
		// get time elapsed between last frame and start of this one
		elapsedTime.QuadPart = currentTime.QuadPart - lastTime.QuadPart;
		// set last frame time to current
		lastTime = currentTime;
		// add to delta the current elapsed time converted to MS divided by the CPU Frequency
		deltaTime += (double)elapsedTime.QuadPart * 1000 / (double)frequency.QuadPart;
		

		//setting play variable to the result of equality
		play = processInput(table);

		while (deltaTime >= Frame_Rate) {
			//Call update function
			play = !update(table);
			deltaTime -= Frame_Rate;
		}


		//Call draw function 
		table.render(hdc, deltaTime / Frame_Rate);
	
	} // end while not exit loop

	cin.ignore();

	return 0;
}

/**********************************************************
 * Initializes the console window for drawing, and returns
 * a handle to a drawing context for the console.
 * @returns HDC	- handle to console's device context
 **********************************************************/
HDC initConsole()
{
	//Get a handle to console window
	HWND conWindow = GetConsoleWindow();

	//Get handle to console standard output stream
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get a handle to a device context for drawing on the console
	HDC conDc = GetDC(conWindow);

	// resize the console window
	RECT conDimensions;
	GetWindowRect(conWindow, &conDimensions);
	MoveWindow(conWindow, conDimensions.left, conDimensions.top, SCREEN_WIDTH + 42, SCREEN_HEIGHT + 38, true);

	// turn off the blinking cursor
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(conOut, &cursor);

	return conDc;
}

/**********************************************************
 * The ball input fuction will get the users input.
 * @param HDC pass_by- A pass by value
 * @param - GameOjects is the global structure for the
 * game objects represents position of ball and paddle.
 * @return bool -return true if x is not pressed or false
 * if x is pressed.
 **********************************************************/
bool processInput(PongTable &table) {
	bool continuePlaying = true;
	PongObject* playerPaddle = table.getPlayerPaddle();

	Position playPaddleVelocity = playerPaddle->getVelocity();

	// get user input
	InputDirections input = playerInput();

	// which direction to move ball
	switch (input)
	{
	case HIGH:
		playPaddleVelocity.yValue -= 0.50;
		break;

	case LOW:
		playPaddleVelocity.yValue += 0.50;
		break;

	case LEFT:
		playPaddleVelocity.xValue -= 0.25;
		break;

	case RIGHT:
		playPaddleVelocity.xValue += 0.25;
		break;
	case STOP:
		continuePlaying = false;
		break;

	}
	playerPaddle->setVelocity(playPaddleVelocity);

	table.moveComputerPaddle();

	return continuePlaying;
}

/**********************************************************
 * Reads the keybaord to see any keys that has been pressed
 * such as WASD or the arrow keys
 *@param const is the letter being pressed on the keyboard
 *@return InputDirection- none,high,low,left,right,stop
 **********************************************************/
InputDirections playerInput()
{
	InputDirections input = NONE;	// return direction to move

	//define key constants for WASD (hex literals)
	const WORD VK_W = 0x57;
	const WORD VK_A = 0x41;
	const WORD VK_S = 0x53;
	const WORD VK_D = 0x44;
	const WORD VK_X = 0x58;

	//Get handle to console standard input stream
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD eventBuff[128];				// event buffer
	unsigned long eventCount, eventsRead;

	// see if there are any events on the standard input stream
	GetNumberOfConsoleInputEvents(hin, &eventCount);

	if (eventCount > 0)
	{
		// read all events availabe into an array buffer
		ReadConsoleInput(
			hin,
			eventBuff,
			128,
			&eventsRead);

		/* see if any of the events read are keyboard events
		   and specifically one of the keys we care about */
		unsigned long i = 0;
		while (input == NONE && i < eventsRead)
		{
			if (eventBuff[i].EventType == KEY_EVENT)
			{
				switch (eventBuff[i].Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_W:		// player hit W key
				case VK_UP:		// or up arrow
					input = HIGH;	// move up
					break;

				case VK_S:		// player hit S key
				case VK_DOWN:	// or down arrow
					input = LOW;  // move down
					break;

				case VK_A:		// player hit A key
				case VK_LEFT:	// or left arrow
					input = LEFT;  // move left
					break;

				case VK_D:		// player hit D key
				case VK_RIGHT:	// or right arrow
					input = RIGHT;  // move right
					break;
				case VK_X:		// player hit X key
					input = STOP;	// exit game
					break;

				default:		// some other key was pressed
					input = NONE;
				} //end case statement

			} // end keyboard event type

			i++;
		} // end while events exist

	}

	// get rid of any other input in the stream
	FlushConsoleInputBuffer(hin);

	return input;
}

/**********************************************************
 * The update function will recive player input for the
 * current x/y corrdinate and x/y velpcity of the ball.
 * T
 * @param int pass_by-is the constant value of player input
 * as a pass by value
 * @param - The struct allow for representation of the
 * position of the objects (ball and paddle)
 **********************************************************/
bool update(PongTable &table)
{
	PongObject* ball = table.getBall();
	PongObject* computerPaddle = table.getComputerPaddle();
	PongObject* playerPaddle = table.getPlayerPaddle();


	// set new ball coordinates
	Position current = ball->getCurrent();
	Position velocity = ball->getVelocity();

	current.xValue += velocity.xValue;
	current.yValue += velocity.yValue;
	ball->setCurrent(current);
	//PADDLE
	Position aiPaddleCurrent = computerPaddle->getCurrent();
	Position computerPaddleVelocity = computerPaddle->getVelocity();

	aiPaddleCurrent.xValue += computerPaddleVelocity.xValue;
	computerPaddle->setCurrent(aiPaddleCurrent);

	//PlayerPaddle
	Position playerPaddleCurrent = playerPaddle->getCurrent();
	Position playerPaddleVelociety = playerPaddle->getVelocity();
	playerPaddleCurrent.yValue += playerPaddleVelociety.yValue;
	playerPaddle->setCurrent(playerPaddleCurrent);

	//end game
	bool endGame = false;

	// Function call collisionChecks() is the datatype and & suppose to be erased
	endGame = table.collisions();

	return endGame;
}

