/**************************************************************
* File   : DataStructure.cpp
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose: header file for Pong game Object such as the ball, 
* paddle and wall.
*************************************************************/
#include "pong.h"


#ifndef PONGOBJECT_H
#define PONGOBJECT_H

class PongObject {
	

public:

	PongObject();

	PongObject(int heightIn, int widthIn, Position currentIn, Position previousIn, Position velocityIn,   bool ballFlagIn);
	

	Position getCurrent();
	Position getPrevious();
	Position getVelocity();

	Position getCurrent(float lag);

	int getHeight();
	int getWidth();
	// the is dirty method
	bool isDirty();
	bool isBall();

	//SETTER
	void setCurrent(Position value);
	void setPrevious(Position value);
	void setVelocity(Position value);

	void setHeight(int value);
	void setWidth(int value);

	void setBallFlag(bool ballFlagin);

	void setIsDirty(bool dirtyIn);

	//has moved method
	bool hasMoved(float lag);
	

	// Erase and Draw Method
	void erase(HDC console);
	void draw(HDC console, float lag);

	//Render Method
	void render(HDC console, float lag);

	//Intersect Method 
	bool intersects(PongObject* other);

	

private:
	Position current;
	Position previous;
	Position velocity;

	int height;
	int width;

	bool ballFlag;

	bool dirty;

}; // end class PongObject


#endif //PONGOBJECT_H
