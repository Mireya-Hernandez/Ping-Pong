/**************************************************************
* File   : PongTable.cpp
* Author : Mireya Hernandez
* Class  : COP 2001 201901 10410
* Purpose: header file for Pong game table
*************************************************************/
#include"PongTable.h"


PongTable::PongTable() {
	// ball coordinates and velocity
	Position ballCurrent = { BALL_START_X, BALL_START_Y };
	Position ballPrevious = { 0,0 };
	Position ballVelocity = { BALL_START_VEL_X, BALL_START_VEL_Y };
	ball = PongObject( BALL_HEIGHT, BALL_WIDTH, ballCurrent, ballPrevious, ballVelocity,  true);

	//top wall
	int topHeight = WALL_THICKNESS;
	int topWidth = SCREEN_WIDTH - (2 * SCREEN_OFFSET);
	Position topCurrent = { SCREEN_OFFSET, SCREEN_OFFSET };
	Position topPrevious = { 0, 0 };
	Position topVelocity = { 0, 0 };
	topWall = PongObject(topHeight, topWidth,topCurrent, topPrevious, topVelocity,   false);

	//Left wall
	int leftHeight = SCREEN_HEIGHT - (2 * SCREEN_OFFSET);
	int leftWidth = WALL_THICKNESS;
	Position leftCurrent = { SCREEN_OFFSET, SCREEN_OFFSET };
	Position leftPrevious = { 0,0 };
	Position leftVelocity = { 0,0 };
	leftWall = PongObject(leftHeight, leftWidth, leftCurrent, leftPrevious, leftVelocity, false);

	//Right Wall
	int rightHeight = SCREEN_HEIGHT - (2 * SCREEN_OFFSET);
	int rightWidth = WALL_THICKNESS;
	Position rightCurrent = { SCREEN_WIDTH - SCREEN_OFFSET - WALL_THICKNESS, SCREEN_OFFSET };
	Position rightPrevious = { 0,0 };
	Position rightVelocity = { 0,0 };
	rightWall = PongObject(rightHeight, rightWidth, rightCurrent, rightPrevious, rightVelocity,   false);

	//Bottom Wall
	int bottomHeight = WALL_THICKNESS;
	int bottomWidth = SCREEN_WIDTH - (2 * SCREEN_OFFSET);
	Position bottomCurrent = { SCREEN_OFFSET, SCREEN_HEIGHT - SCREEN_OFFSET - WALL_THICKNESS};
	Position bottomPrevious = { 0,0 };
	Position bottomVelocity = { 0,0 };
	bottomWall = PongObject(bottomHeight,  bottomWidth, bottomCurrent, bottomPrevious, bottomVelocity,  false);

	//Initialize computer paddle
	 
	Position aiPaddlePos;
	aiPaddlePos.xValue = rightWall.getCurrent().xValue - PADDLE_OFFSET - PADDLE_WIDTH;
	aiPaddlePos.yValue = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	computerPaddle = PongObject( PADDLE_HEIGHT, PADDLE_WIDTH, aiPaddlePos, {0,0 }, { 0,0 }, false);

	//instantiation of player paddle
	Position playerPaddlePos;
	playerPaddlePos.xValue = leftWall.getCurrent().xValue + PADDLE_OFFSET;
    playerPaddlePos.yValue = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	playerPaddle = PongObject(PADDLE_HEIGHT, PADDLE_WIDTH, aiPaddlePos, { 0,0 }, { 0,0 }, false);
}

PongObject* PongTable::getBall() {
	return &ball;
}

PongObject* PongTable::getTopWall() {
	return &topWall;
}

PongObject* PongTable::getLeftWall() {
	return &leftWall;
}

PongObject* PongTable::getRightWall() {
	return &rightWall;
}

PongObject* PongTable::getBottomWall() {
	return &bottomWall;
}

PongObject * PongTable::getComputerPaddle()
{
	return &computerPaddle;
}

PongObject * PongTable::getPlayerPaddle()
{

	return &playerPaddle;
}




void PongTable::render(HDC console, float lag) {

	 
	// draw the ball
	ball.render(console, lag);
	//PlayerPaddle
     playerPaddle.render(console, lag);

	// call to paddle
	computerPaddle.render(console, lag);

	// draw the wall
	leftWall.render(console, 0);

	rightWall.render(console, 0);

	topWall.render(console, 0);

	bottomWall.render(console, 0);
	return;
}

bool PongTable::collisions()
{
	Position ballCurrent = ball.getCurrent();
	Position ballVelocity = ball.getVelocity();
	bool endGame = false;

	if (ball.intersects(&computerPaddle)) {

		ballCurrent.xValue = computerPaddle.getCurrent().xValue - ball.getWidth() - 1;
		ballVelocity.xValue *= -1;
		computerPaddle.setIsDirty(true);
	}

	else if (ball.intersects(&playerPaddle)) {

		ballCurrent.xValue = playerPaddle.getCurrent().xValue + playerPaddle.getWidth() + 1;
		ballVelocity.xValue *= -1;
		playerPaddle.setIsDirty(true);
	}

	//ball with left wall
	else if (ball.intersects(&leftWall)) {
		ballCurrent.xValue = leftWall.getCurrent().xValue + leftWall.getWidth() + 1;
		ballVelocity.xValue *= -1;
		leftWall.setIsDirty(true);
		
		
	}

	//ball with right wall
	else if (ball.intersects(&rightWall)) {
		ballCurrent.xValue = rightWall.getCurrent().xValue - ball.getWidth() - 1;
		ballVelocity.xValue *= -1;
		rightWall.setIsDirty(true);
		
	
	}

	//ball with top wall
	if (ball.intersects(&topWall)) {
		ballCurrent.yValue = topWall.getCurrent().yValue + ball.getHeight() + 1;
		ballVelocity.yValue *= -1;
		topWall.setIsDirty(true);
	}
	//ball with bottom wall
	else {
		ballCurrent.yValue = bottomWall.getCurrent().yValue - ball.getHeight() - 1;
		ballVelocity.yValue *= -1;
		bottomWall.setIsDirty(true);
	}
	ball.setCurrent(ballCurrent);
	ball.setVelocity(ballVelocity);

	Position aiPaddleCurrent = computerPaddle.getCurrent();
	Position computerPaddleVelocity = computerPaddle.getVelocity();

	if (computerPaddle.intersects(&topWall)) {
		aiPaddleCurrent.yValue = topWall.getCurrent().yValue + topWall.getHeight() + 1;
		computerPaddleVelocity.yValue = 0.0;
		topWall.setIsDirty(true);
	}
	else if (computerPaddle.intersects(&bottomWall)) {
		aiPaddleCurrent.yValue = bottomWall.getCurrent().yValue - PADDLE_HEIGHT - 1;
		computerPaddleVelocity.yValue = 0.0;
		bottomWall.setIsDirty(true);
	}

	computerPaddle.setCurrent(aiPaddleCurrent);
	computerPaddle.setVelocity(computerPaddleVelocity);

	//playerPaddle
	Position playerPaddleCurrent = playerPaddle.getCurrent();
	Position playerPaddleVelocity = playerPaddle.getVelocity();

	if (playerPaddle.intersects(&topWall)) {
		playerPaddleCurrent.yValue = topWall.getCurrent().yValue + topWall.getHeight() + 1;
		playerPaddleVelocity.yValue = 0.0;
		topWall.setIsDirty(true);
	}
	else if (playerPaddle.intersects(&bottomWall)) {
		playerPaddleCurrent.yValue = bottomWall.getCurrent().yValue - PADDLE_HEIGHT - 1;
		playerPaddleVelocity.yValue = 0.0;
		bottomWall.setIsDirty(true);
	}
	playerPaddle.setCurrent(playerPaddleCurrent);
	playerPaddle.setVelocity(playerPaddleVelocity);

	return endGame;
	

}

void PongTable::moveComputerPaddle()
{
	Position ballCurrent = ball.getCurrent();
	Position aiPaddleCurrent = computerPaddle.getCurrent();
	Position computerPaddleVelocity = computerPaddle.getVelocity();
	int paddleHeight = PADDLE_HEIGHT;

	float paddleTop = aiPaddleCurrent.yValue;
	float paddleBottom = paddleTop + paddleHeight;
	
	 paddleTop = paddleTop + (paddleHeight / 3);
	 paddleBottom = paddleBottom - (paddleHeight / 3);

	float ballTop = ballCurrent.yValue;
	float ballBottom = ballTop + BALL_HEIGHT;

	if (ballBottom < paddleTop)
	{
		computerPaddleVelocity.yValue -= 0.02;

	}
	else if (ballTop > paddleBottom)
	{
		computerPaddleVelocity.yValue += 0.02;
	}
	else
		computerPaddleVelocity.yValue = 0.0;
	
	computerPaddle.setVelocity(computerPaddleVelocity);
}


