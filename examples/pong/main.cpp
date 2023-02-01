#include "Pokitto.h"

Pokitto::Core game;
Pokitto::Display display;
Pokitto::Buttons buttons;
/*
	https://talk.pokitto.com/t/tutorial-community-3-level-1-3-first-game/143
	In this tutorial we are using fast screen mode.
	It means screen resolution is 110x88
	playerA's buttons are UP and DOWN
	playerB's buttons are A and B
*/

char ballX = 55;
float ballY = 44;
float ballS = 0;
bool ballV = 1, ballH = 0;
char paddleA = 40;
char paddleB = 40;
int scoreA = 0;
int scoreB = 0;
char screenW = 110;
char screenH = 88;

void resetVal(bool isBallLeft);

void init()
{
	display.width = screenW;
	display.height = screenH;
	game.setFrameRate(60);
	display.setCursor(40, 0);
}

void update()
{

	//-----------buttons-------------
	if (buttons.repeat(BTN_UP, 0) && paddleA > 0)
	{			   // if button up is pressed AND paddle is not touching to the edge
		paddleA--; // then move playerA's paddle to up
	}
	if (buttons.repeat(BTN_DOWN, 0) && paddleA < (screenH - 15))
	{			   // if button down is pressed AND paddle is not touching to the edge
		paddleA++; // then move playerA's paddle to down
	}
	if (buttons.repeat(BTN_A, 0) && paddleB > 0)
	{ // same as playerA
		paddleB--;
	}
	if (buttons.repeat(BTN_B, 0) && paddleB < (screenH - 15))
	{ // our paddle's height is 15
		paddleB++;
	}
	//----------logic----------
	if (ballV)
		ballY = ballY - ballS; // if bool value ballV is 1 then move ball to up
	else
		ballY = ballY + ballS; // if bool value ballV is 0 then move ball to down
	if (ballH)
		ballX++; // if bool value ballX is 1 then move ball to right
	else
		ballX--; // you know what is going on here
	// first we check is ball touching the upward and downward edge
	if ((ballY < 5) || ((ballY + 5) > screenH))
	{					// we use ballY + 5 because our balls radius is 5
		ballV = !ballV; // if ball touching edge then change the direction
	}
	// after we check is any player make score
	if (ballX == 4)
	{			  // if playerA not hit the ball
		scoreB++; // increase playerB's score
		resetVal(0);
	}
	if ((ballX + 5) == (screenW - 4))
	{			  // if playerB not hit the ball
		scoreA++; // same as above
		resetVal(1);
	}
	// paddle-ball collision
	if ((ballX == 10) && (ballY > paddleA) && (ballY < paddleA + 15))
	{
		ballH = !ballH;
		ballS = (((paddleA - ballY) / 7.5) + 1) * 2;
	}
	if ((ballX == (screenW - 10)) && (ballY > paddleB) && (ballY < paddleB + 15))
	{
		ballH = !ballH;
		ballS = (((paddleB - ballY) / 7.5) + 1) * 2;
	}
	//--------draw----------
	// write score
	display.color = 1;
	display.setCursor(45, 10);
	display.print(scoreA);
	display.print("-");
	display.print(scoreB);
	// draw playerA's paddle
	display.color = 2;
	display.fillRectangle(0, paddleA, 5, 15);
	// draw ball
	display.color = 3;
	display.fillCircle(ballX, char(ballY), 5);
	// draw playerB's paddle
	display.color = 4;
	display.fillRectangle(105, paddleB, 5, 15);
}

void resetVal(bool isBallLeft)
{
	ballX = 55;
	ballY = 44;
	paddleA = 40;
	paddleB = 40;
	ballS = 0;
	ballV = 1;
	ballH = isBallLeft;
}
