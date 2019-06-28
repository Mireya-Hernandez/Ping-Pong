/**************************************************************
* File   : PongObject.cpp
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose:Implementation file of a pong game object such as 
* ball, paddle and wall
*************************************************************/
#include "pongObject.h"


PongObject::PongObject() {
	current = { 0.0f, 0.0f };
	previous = { 0.0f, 0.0f };
	velocity = { 0.0f, 0.0f };

	height =  0.0;
	width = 0.0;

	dirty = true;

	}
//constructor
PongObject::PongObject(int heightIn, int widthIn, Position currentIn, Position previousIn, Position velocityIn, bool ballFlagIn) {
	current = currentIn;
	previous = previousIn;
	velocity = velocityIn;

	height = heightIn;
	width = widthIn;
	ballFlag = ballFlagIn;
	
	}

//Accessor Method
Position PongObject::getCurrent() {return current; }
Position PongObject::getPrevious() {return previous; }
Position PongObject::getVelocity() {return velocity; }

int PongObject::getHeight() { return height; }
int PongObject::getWidth() { return width; }

//has moved 

bool PongObject::hasMoved(float lag)
{
	Position adjustedCurr = getCurrent(lag);

	return	(int(adjustedCurr.xValue) != int(previous.xValue)) || (int(adjustedCurr.yValue) != int(previous.yValue));
}

//the ball indicator
bool PongObject::isBall()
{
	return ballFlag;
}



Position PongObject::getCurrent(float lag)

{
	Position  thisValue;

	 thisValue.xValue = current.xValue + (lag*velocity.xValue);
	thisValue.yValue = current.yValue + (lag*velocity.yValue);


	return   thisValue;   
}

//Erase and Draw
void PongObject::erase(HDC console)
{
	int xpos = previous.xValue;
	int ypos = previous.yValue;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			SetPixel(console, xpos + j, ypos + i, BLACK);
		}
	}
	return;
}

void PongObject::draw(HDC console, float lag)
{
	Position adjustedCurr = getCurrent(lag);
	int xpos = adjustedCurr.xValue;
	int ypos = adjustedCurr.yValue;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			COLORREF paint = PAINT;
			if (isBall()) {
				paint = BALL_PATTERN[i][j];
			}
			SetPixel(console, xpos + j, ypos + i, paint);
		}

	}
	setPrevious(adjustedCurr);

	return;
}

void PongObject::render(HDC console, float lag) {
	if (hasMoved(lag) || isDirty()) {

		erase(console);
		draw(console, lag);
		setIsDirty(false);

	}
	return;
}
bool PongObject::intersects(PongObject* other) {

	// This Object
	float thisTop = current.yValue;
	float thisLeft = current.xValue;
	float thisBottom = current.yValue + height;
	float thisRight = current.xValue + width;

	//Other Objects
	float otherTop = other->getCurrent().yValue;
	float otherBottom = other->getCurrent().yValue + other->getHeight();
	float otherLeft = other->getCurrent().xValue;
	float otherRight = other->getCurrent().xValue + other->getWidth();

	return !(otherLeft > thisRight|| otherRight < thisLeft || otherTop > thisBottom || otherBottom < thisTop);
}

bool PongObject::isDirty()
{
	return dirty;
}

//Setter Method
void PongObject::setCurrent(Position value) {
	current = value;
}
void PongObject::setPrevious(Position value) {
	previous = value;
}
void PongObject::setVelocity(Position value) {
	velocity = value;
}
void PongObject::setHeight(int heightIn) {
	height = heightIn;
}

void PongObject::setWidth(int widthIn) {
	width = widthIn;
}

void PongObject::setBallFlag(bool ballFlagIn) {
	ballFlag = ballFlagIn;
}

void PongObject::setIsDirty(bool IsDirtyIn) {
	dirty = IsDirtyIn;
}

