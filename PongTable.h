/**************************************************************
* File   : PongTable.h
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose: header file for Pong game table
*************************************************************/
#include "PongObject.h"

#ifndef PONGTABLE_H
#define PONGTABLE_H

class PongTable {
public:
	
	PongTable();
	PongObject* getBall();
	PongObject* getTopWall();
	PongObject* getLeftWall();
	PongObject* getRightWall();
	PongObject* getBottomWall();
	PongObject* getComputerPaddle();
	PongObject* getPlayerPaddle();
	//Render Method
	void render(HDC console, float lag);
	//Collision
	bool collisions();

	//Move comupter paddle Method
	void moveComputerPaddle();


	

private:

	PongObject ball;
	PongObject topWall;
	PongObject leftWall;
	PongObject rightWall;
	PongObject bottomWall;
	PongObject computerPaddle;
	PongObject playerPaddle;
	
};
#endif //PONGTABLE_H
