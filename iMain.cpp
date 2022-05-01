#include<iostream>
#include <string>
#include <fstream>
using namespace std;
#include"iGraphics.h"
#define totalBricks 50
#define screenWidth 1200
#define screenHight 650
#define yAxisMargin 50

struct buttonCordinate
{
	int x, y;
}bCordinate[4];

char button[4][25] = { "images\\start.bmp", "images\\highscore.bmp", "images\\instruction.bmp", "images\\credits.bmp" };
char homemenu[20] = "images\\dx_ball.bmp";
char score[25] = "images\\score.bmp";
char backGroundImage[30] = "images\\sky.bmp";
char winImage[20] = "images\\won.bmp";
char overImage[20] = "images\\over.bmp";
char finalScoreImage[25] = "images\\final_score.bmp";
char finalHighScoreImage[30] = "images\\final_high_score.bmp";
char mainMenuImage[30] = "images\\main_menu.bmp";
//char resumeImage[30] = "images\\resume.bmp";
char pauseImage[30] = "images\\pause.bmp";
char instructionsImage[30] = "images\\instructions.bmp";
char creditImage[30] = "images\\credit_page.bmp";

int gameState = -1;
int countBricks = totalBricks;
int currentScore = 0;
int highestScore;
bool musicOn = true;

struct brickSturcture
{
	int x, y;
	int dx = 100;
	int dy = 20;
	bool show = true;
	int red;
	int green;
	int blue;
};

brickSturcture bricks[totalBricks];
brickSturcture bricks2[totalBricks];
brickSturcture bricks3[totalBricks];
int red = 255;
int green = 255;
int blue = 255;


int xBall = (int)screenWidth / 2;
int yBall = yAxisMargin;
int radiusBall = 10;
int dx = 7;
int dy = 5;

int xBoard = xBall - 50;
int yBoard = yBall - 20;
int dxBoard = 100;
int dyBoard = 10;

bool isStarted = false;
bool isPaused = false;

void ballChange();
void restartBall();
void defineBricks1();
void defineBricks2();
void defineBricks3();
void mainMenuPressed();


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


void iDraw()
{
	iClear();
	if (gameState == -1){
		iShowBMP(0, 0, homemenu);
		for (int i = 0; i < 4; i++)
		{
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 0);
		}
	}
	else if (gameState == 1){
		iShowBMP(400, 450, finalHighScoreImage);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", highestScore);
		iSetColor(255, 255, 255);
		iText(550, 400, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iShowBMP(450, 200, mainMenuImage);
	}
	else if (gameState == 2){
		iShowBMP(0, 0, instructionsImage);
		iShowBMP(500, 100, mainMenuImage);
	}
	else if (gameState == 3){
		iShowBMP(0, 0, creditImage);
		iShowBMP(500, 100, mainMenuImage);
	}
	else if (gameState == 0){
		iShowBMP(0, 0, backGroundImage);
		iShowBMP2(5, 615, score, 255);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", currentScore);
		iSetColor(0, 0, 0);
		iText(60, 622, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(red, green, blue);
		iFilledCircle(xBall, yBall, radiusBall, 1000);
		iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks[i].show)
			{
				iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
				iFilledRectangle(bricks[i].x, bricks[i].y, bricks[i].dx, bricks[i].dy);
			}
		}

		if (isPaused){
			iShowBMP(450, 200, pauseImage);
		}
	}

	else if (gameState == 11){
		iShowBMP(0, 0, backGroundImage);
		iShowBMP2(5, 615, score, 255);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", currentScore);
		iSetColor(0, 0, 0);
		iText(60, 622, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(red, green, blue);
		iFilledCircle(xBall, yBall, radiusBall, 1000);
		iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks2[i].show)
			{
				iSetColor(bricks2[i].red, bricks2[i].green, bricks2[i].blue);
				iFilledRectangle(bricks2[i].x, bricks2[i].y, bricks2[i].dx, bricks2[i].dy);
			}
		}

		if (isPaused){
			iShowBMP(450, 200, pauseImage);
		}
	}

	else if (gameState == 12){
		iShowBMP(0, 0, backGroundImage);
		iShowBMP2(5, 615, score, 255);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", currentScore);
		iSetColor(0, 0, 0);
		iText(60, 622, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(red, green, blue);
		iFilledCircle(xBall, yBall, radiusBall, 1000);
		iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks3[i].show)
			{
				iSetColor(bricks3[i].red, bricks3[i].green, bricks3[i].blue);
				iFilledRectangle(bricks3[i].x, bricks3[i].y, bricks3[i].dx, bricks3[i].dy);
			}
		}

		if (isPaused){
			iShowBMP(450, 200, pauseImage);
		}
	}
	else if (gameState == 13){
		if (currentScore > highestScore) {
			highestScore = currentScore;
			ofstream os("highscore.txt");
			os << highestScore << endl;
			os.close();
		}

		iShowBMP(300, 250, winImage);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", currentScore);
		iSetColor(255, 255, 255);
		iText(300, 200, "Your Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(430, 200, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iText(300, 150, "Highest Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(score_in_str, "%d", highestScore);
		iText(460, 150, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		iShowBMP(500, 50, mainMenuImage);
	}

	else if (gameState == -5){
		iShowBMP(450, 450, overImage);
		iShowBMP(450, 250, finalScoreImage);

		char score_in_str[10];
		sprintf_s(score_in_str, "%d", currentScore);
		iSetColor(0, 0, 255);
		iText(760, 265, score_in_str, GLUT_BITMAP_TIMES_ROMAN_24);

		if (currentScore > highestScore) {
			highestScore = currentScore;
			ofstream os("highscore.txt");
			os << highestScore << endl;
			os.close();
		}

		iShowBMP(500, 100, mainMenuImage);
	}
	else
	{

	}
}


/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}


//*******************************************************************ipassiveMouse***********************************************************************//


void iPassiveMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//cout << mx << " " << my << endl;
		for (int i = 0; i < 4; i++){
			if (mx >= bCordinate[i].x && mx <= bCordinate[i].x + 250 && my >= bCordinate[i].y && my <= bCordinate[i].y + 86)
			{
				gameState = i;
			}
		}

		if (isPaused){
			if (mx >= 490 && mx <= 725 && my >= 320 && my <= 385){
				iResumeTimer(0);
				isPaused = false;
			}
			if (mx >= 490 && mx <= 725 && my >= 220 && my <= 285){
				mainMenuPressed();
			}
		}

		if (gameState == 1){
			if (mx >= 455 && mx <= 690 && my >= 210 && my <= 275){
				mainMenuPressed();
			}
		}

		if (gameState == -5 || gameState == 2 || gameState == 3){
			if (mx >= 505 && mx <= 740 && my >= 110 && my <= 175){
				mainMenuPressed();
			}
		}

		if (gameState == 13){
			if (mx >= 505 && mx <= 740 && my >= 60 && my <= 125){
				mainMenuPressed();
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}


/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 'w')
	{

	}
	else if (key == 's')
	{

	}
	else if (key == 'a')
	{

	}
	else if (key == 'd')
	{

	}
	else if (key == ' ')
	{
		if (!isStarted)
		{
			isStarted = true;
		}
	}
	else if (key == 'p')
	{
		iPauseTimer(0);
		isPaused = true;
	}
	else if (key == 'r')
	{
		iResumeTimer(0);
		isPaused = false;
	}


}


/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/


void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_UP)
	{

	}
	else if (key == GLUT_KEY_DOWN)
	{

	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (xBoard > 0)
		{
			xBoard -= 18;
			if (!isStarted)
			{
				xBall -= 18;
			}
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (xBoard < screenWidth - dxBoard)
		{
			xBoard += 18;
			if (!isStarted)
			{
				xBall += 18;
			}
		}
	}

	else if (key == GLUT_KEY_HOME)
	{

	}
	else if (key == GLUT_KEY_INSERT)
	{

	}

}
void ballChange()
{
	/*red = rand() % 255;
	green = rand() % 255;
	blue = rand() % 255;*/
	red = 0;
	green = 0;
	blue = 0;
	if (isStarted)
	{
		xBall += dx;
		yBall += dy;

		if (xBall >= screenWidth || xBall <= 0)
			dx *= (-1);
		if (yBall >= screenHight || yBall <= 0)
			dy *= (-1);

		for (int i = 0; i < totalBricks; i++)
		{
			if (gameState == 0){
				if (bricks[i].show)
				{
					if (xBall >= bricks[i].x && xBall <= bricks[i].x + bricks[i].dx)
					{
						if (yBall >= bricks[i].y && yBall <= bricks[i].y + bricks[i].dy)
						{
							dy *= (-1);
							bricks[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 11;
								countBricks = totalBricks;
								restartBall();
							}
						}
					}
					else if (yBall >= bricks[i].y && yBall <= bricks[i].y + bricks[i].dy)
					{
						if (xBall >= bricks[i].x && xBall <= bricks[i].x + bricks[i].dx)
						{
							dx *= (-1);
							bricks[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 11;
								countBricks = totalBricks;
								restartBall();
							}
						}
					}
				}
			}
			else if (gameState == 11){
				if (bricks2[i].show)
				{
					if (xBall >= bricks2[i].x && xBall <= bricks2[i].x + bricks2[i].dx)
					{
						if (yBall >= bricks2[i].y && yBall <= bricks2[i].y + bricks2[i].dy)
						{
							dy *= (-1);
							bricks2[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 12;
								countBricks = totalBricks;
								restartBall();
							}
						}
					}
					else if (yBall >= bricks2[i].y && yBall <= bricks2[i].y + bricks2[i].dy)
					{
						if (xBall >= bricks2[i].x && xBall <= bricks2[i].x + bricks2[i].dx)
						{
							dx *= (-1);
							bricks2[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 12;
								countBricks = totalBricks;
								restartBall();
							}
						}
					}
				}
			}
			else if (gameState == 12){
				if (bricks3[i].show)
				{
					if (xBall >= bricks3[i].x && xBall <= bricks3[i].x + bricks3[i].dx)
					{
						if (yBall >= bricks3[i].y && yBall <= bricks3[i].y + bricks3[i].dy)
						{
							dy *= (-1);
							bricks3[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 13;
								countBricks = totalBricks;
							}
						}
					}
					else if (yBall >= bricks3[i].y && yBall <= bricks3[i].y + bricks3[i].dy)
					{
						if (xBall >= bricks3[i].x && xBall <= bricks3[i].x + bricks3[i].dx)
						{
							dx *= (-1);
							bricks3[i].show = false;
							countBricks--;
							currentScore += 10;

							if (!countBricks){
								gameState = 13;
								countBricks = totalBricks;
							}
						}
					}
				}
			}
		}
		if (xBall >= xBoard && xBall <= xBoard + dxBoard && yBall >= yBoard && yBall <= yBoard + dyBoard)
		{
			dy *= (-1);
		}
		else
		{
			if (yBall < yBoard && gameState != 13)
			{
				gameState = -5;
			}
		}
	}
}

void restartBall()
{
	xBall = (int)screenWidth / 2;
	yBall = yAxisMargin;
	dx = 7;
	dy = 5;

	xBoard = xBall - 50;
	yBoard = yBall - 20;

	isStarted = false;
}

void mainMenuPressed()
{
	iResumeTimer(0);
	isPaused = false;
	restartBall();
	currentScore = 0;
	defineBricks1();
	defineBricks2();
	defineBricks3();
	countBricks = totalBricks;
	gameState = -1;
}

void defineBricks1()
{
	int sumx = 100;
	int sumy = 450;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks[i].red = rand() % 255;
		bricks[i].green = rand() % 255;
		bricks[i].blue = rand() % 255;
		bricks[i].x = sumx;
		bricks[i].y = sumy;
		bricks[i].show = true;
		sumx += 100;
		if (sumx>1000){
			sumx = 100;
			sumy += 20;
		}
	}
}

void defineBricks2()
{
	int sumx = 100;
	int sumy = 450;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks2[i].red = rand() % 255;
		bricks2[i].green = rand() % 255;
		bricks2[i].blue = rand() % 255;
		bricks2[i].x = sumx;
		bricks2[i].y = sumy;
		bricks2[i].show = true;
		sumx += 100;

		if (i == 9){
			sumx = 200;
			sumy += 20;
		}
		else if (i == 17){
			sumx = 400;
			sumy += 20;
		}
		else if (i == 21){
			sumx = 500;
			sumy += 20;
		}
		else if (i == 23){
			sumx = 500;
			sumy += 20;
		}
		else if (i == 25){
			sumx = 500;
			sumy += 20;
		}
		else if (i == 27){
			sumx = 400;
			sumy += 20;
		}
		else if (i == 31){
			sumx = 200;
			sumy += 20;
		}
		else if (i == 39){
			sumx = 100;
			sumy += 20;
		}
		else {

		}
	}
}

void defineBricks3()
{
	int sumx = 500;
	int sumy = 350;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks3[i].red = rand() % 255;
		bricks3[i].green = rand() % 255;
		bricks3[i].blue = rand() % 255;
		bricks3[i].x = sumx;
		bricks3[i].y = sumy;
		bricks3[i].show = true;
		sumx += 100;

		if (i == 1){
			sumx = 400;
			sumy += 20;
		}
		else if (i == 5){
			sumx = 200;
			sumy += 20;
		}
		else if (i == 13){
			sumx = 100;
			sumy += 20;
		}
		else if (i == 23){
			sumx = 500;
			sumy += 20;
		}
		else if (i == 25){
			sumx = 100;
			sumy += 20;
		}
		else if (i == 35){
			sumx = 200;
			sumy += 20;
		}
		else if (i == 43){
			sumx = 400;
			sumy += 20;
		}
		else if (i == 47){
			sumx = 500;
			sumy += 20;
		}
		else {

		}
	}
}

int main()
{
	int sum = 100;
	for (int i = 3; i >= 0; i--)
	{
		bCordinate[i].x = 50;
		bCordinate[i].y = sum;
		sum += 100;
	}

	defineBricks1();
	defineBricks2();
	defineBricks3();
	
	ifstream is("highscore.txt");
	is >> highestScore;
	is.close();

	if (musicOn){
		PlaySound("music\\Gamemusic.wav", NULL, SND_ASYNC | SND_LOOP);
	}

	iSetTimer(10, ballChange);
	iInitialize(screenWidth, screenHight, "DX-Ball");
	iStart();

	return 0;
}