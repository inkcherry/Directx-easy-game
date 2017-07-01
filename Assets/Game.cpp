
#include "Game.h"
#include <math.h>
#include<iostream>

Game::Game(HWND hWnd, const KeyboardServer& kServer)
	: gfx(hWnd),
	kbd(kServer),
	dx(100),
	dy(100),
	x(200),
	y(200),
	speed(1),
	cursorPos(4),
	player(0),
	nTurns(0)
{
	/*Circle(300, 300, 50);*/
	
	for (int index = 0; index < 9; index++)
 {
		SetSquareState(index, EMPTY);
 }
}


void Game::Circle(int basex,int basey,int rad,int player)
 {  


	float radSqr = rad*rad;
	if (player == 1)       
	{
		for (float t = 0; t < 6.28; t = t + 0.01)
		{

			int x0 = rad*sin(t);
			int y0 = rad*cos(t);
			gfx.PutPixel(basex + x0, basey + y0, 255, 255, 0);
		}
	}
	else if (player == 0)
	{
		for (float t = 0; t < 6.28; t = t + 0.01)
		{

			int x0 = rad*sin(t);
			int y0 = rad*cos(t);
			gfx.PutPixel(basex + x0, basey + y0, 255, 0, 178);
		}
	}
}
void Game::UserInput()
{
	if (kbd.RightIsPressed())
	{
		cursorPos++;
		if (cursorPos > 8) cursorPos = 0;
		Sleep(100);
	}
	if (kbd.UpIsPressed())
	{
		cursorPos -= 3;
		if (cursorPos <0) cursorPos += 9;
		Sleep(100);
	}
	if (kbd.DownIsPressed())
	{
		cursorPos += 3;
		if (cursorPos > 8) cursorPos -= 9;
		Sleep(100);
	}
	if (kbd.LeftIsPressed())
	{
		cursorPos--;
		if (cursorPos < 0) cursorPos = 8;
		Sleep(100);
	}
	if (kbd.EnterIsPressed())
	{
		if (GetSquareState(cursorPos) != O&&GetSquareState(cursorPos) != X)  //如果没有被初始化
		{
			SetSquareState(cursorPos, player ? O : X);
			player = !player;
			nTurns++;
			Sleep(100);
		}
	}
}

void Game::Go()
{

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
	

}
void Game::DravGird(int baseX, int baseY, int size)
{

	for (int i = baseX; i<baseX+300; i = i++)                //i是横坐标     这是画竖线         
		for (int j = baseY; j <= baseY+300; j = j + 100)    //j是纵坐标
		{
			gfx.PutPixel(i, j, 255, 255, 255);
		}                                          
	for (int i = baseY; i < baseY+300; i++)            //i是纵坐标
	{
		for (int j = baseX; j <= baseX+300; j = j + 100)
		{
			gfx.PutPixel(j, i, 255, 255, 255);
		}
	}

}
Game::XOState Game::CheckForVictory()
{
	if (s0 == s1&&s0 == s2&&s0 != EMPTY)  
	{
		return s0;
	}
	if (s3 == s4&&s3 == s5&&s3 != EMPTY)
	{
		return s3;
	 }
	if (s6 == s7&&s6 == s8&&s6 != EMPTY)
	{
		return s6;
	}
	
	if (s0 == s3&&s3 == s6&&s0 != EMPTY)
	{
		return s0;
	}
	if (s1 == s4&&s4 == s7&&s1 != EMPTY)
	{
		return s1;
	}
	if (s2 == s5&&s5 == s8&&s2 != EMPTY)
	{
		return s2;
	}
	if (s0 == s4&&s4 == s8&&s0 != EMPTY)
	{
		return s0;
	}
	if (s2 == s4&&s4 == s6&&s2 != EMPTY)
	{
		return s2;
	}
	return EMPTY;
}
void Game::DravCursor(int index)   //画光标
{
	int Basex;     //格子中心横坐标
	int Basey;     //格子中心纵坐标
	Basex = 250+(index) % 3 *100+50;
	Basey = 200+(index) / 3 * 100 ;
	for (int i = Basex - 45; i < Basex-5; i++)
	{
		gfx.PutPixel(i, Basey + 45, 13, 255, 255);   //右上横线
		gfx.PutPixel(i + 50, Basey - 45, 13, 255, 255);  //右下横
	}
	for (int i = Basey - 45; i < Basey-5;i++)
	{
		gfx.PutPixel(Basex - 45, i+50, 13, 225, 255);   //右下数线
		gfx.PutPixel(Basex + 45, i, 13, 255, 255);    //右上数线
 	}
	
}
void Game::ComposeFrame()
{    

	const int baseX=250;
	const int baseY=150;
	const int squareSize = 100;
	//Circle(100, 100, 30);
	Game::XOState victoryState = CheckForVictory();
	if (victoryState == EMPTY&&nTurns != 9)
	{
		DravCursor(cursorPos);    //画光标
		UserInput();
	}
	else
	{
		if (nTurns == 9)
			victoryState = EMPTY;
		DrawEndScreen(358, 495, victoryState);

	}
	DravGird(baseX, baseY, squareSize);    
	

	for (int index = 0; index < 9; index++)    //画圈
	{
		
		if (GetSquareState(index) == O)
		{
			Circle(baseX + (index % 3) *100+50, baseY +((index/3)) * 100+50,30,1);
		}
		if (GetSquareState(index) == X)
		{
			Circle(baseX + (index % 3) * 100 + 50, baseY + ((index / 3)) * 100 + 50, 30, 0);
		}
		
	}

}
void Game::SetSquareState(int index, XOState state)
{
	switch (index)
	{
	case 0:
			s0 = state;
			break;
	case 1:
		s1 = state;
		break;
	case 2:
		s2 = state;
		break;
	case 3:
		s3 = state;
		break;
	case 4:
		s4 = state;
		break;
	case 5:
		s5 = state;
		break;
	case 6:
		s6 = state;
		break;
	case 7:
		s7 = state;
		break;
	case 8:
		s8 = state;
		break;
	default:
		break;
	}
}

Game::XOState Game::GetSquareState(int index)
{
	switch (index)
	{
	case 0:
		return s0;
	case 1:
		return s1;
	case 2:
		return s2;
	case 3:
		return s3;
	case 4:
		return s4;
	case 5:
		return s5;
	case 6:
		return s6;
	case 7:
		return s7;
	case 8:
		return s8;
	
	default:
		break;
	}
}
void Game::DrawEndScreen(int x, int y, Game::XOState state)
{
	if (state == X)
	{
		DrawXWin(x+18,y+57);
	}
	else if (state == O)
	{
		DrawOWin(x + 18, y + 57);
	}
	else 
	{
		DrawTie(x + 18, y + 57);
	}
}
void Game:: DrawTie(int x,int y )        //平局
{
	gfx.PutPixel(12 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(13 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(16 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(14 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(15 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(23 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(24 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(29 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(30 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(31 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 8 + y, 0, 146, 14);
}
void Game::DrawOWin(int x,int y)              //黄色胜利
{
	gfx.PutPixel(1 + x, 0 + y, 255, 255, 0);
	gfx.PutPixel(2 + x, 0 + y, 255, 255, 0);
	gfx.PutPixel(3 + x, 0 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 0 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 1 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 1 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 1 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 1 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 2 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 2 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 2 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 2 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 3 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 3 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 3 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 3 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 4 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 4 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 4 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 4 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 5 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 5 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 5 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 5 + y, 255, 255, 0);
	gfx.PutPixel(16 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 6 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 6 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 6 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 6 + y, 255, 255, 0);
	gfx.PutPixel(17 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 7 + y, 255, 255, 0);
	gfx.PutPixel(1 + x, 7 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 7 + y, 255, 255, 0);
	gfx.PutPixel(5 + x, 7 + y, 255, 255, 0);
	gfx.PutPixel(17 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 8 + y, 255, 255, 0);
	gfx.PutPixel(2 + x, 8 + y, 255, 255, 0);
	gfx.PutPixel(3 + x, 8 + y, 255, 255, 0);
	gfx.PutPixel(4 + x, 8 + y, 255, 255, 0);
	gfx.PutPixel(17 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 8 + y, 0, 146, 14);
}
void Game:: DrawXWin(int x,int y)          //红胜利
{
	gfx.PutPixel(40 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(2 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 2 + y, 0, 146, 14); gfx.PutPixel(1 + x, 0 + y, 0, 0, 255);
	gfx.PutPixel(2 + x, 0 + y, 255, 0, 178);
	gfx.PutPixel(3 + x, 0 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 0 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 0 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 1 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 1 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 1 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 1 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 1 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 2 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 2 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 3 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 3 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 3 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 3 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(34 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 3 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 4 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 4 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 4 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 4 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(35 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 4 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 5 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 5 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 5 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 5 + y, 255, 0, 178);
	gfx.PutPixel(16 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(17 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(19 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(22 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(36 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 5 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 6 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 6 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 6 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 6 + y, 255, 0, 178);
	gfx.PutPixel(17 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 6 + y, 0, 146, 14);
	gfx.PutPixel(0 + x, 7 + y, 255, 0, 178);
	gfx.PutPixel(1 + x, 7 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 7 + y, 255, 0, 178);
	gfx.PutPixel(5 + x, 7 + y, 255, 0, 178);
	gfx.PutPixel(17 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(40 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(45 + x, 7 + y, 0, 146, 14);
	gfx.PutPixel(1 + x, 8 + y, 255, 0, 178);
	gfx.PutPixel(2 + x, 8 + y, 255, 0, 178);
	gfx.PutPixel(3 + x, 8 + y, 255, 0, 178);
	gfx.PutPixel(4 + x, 8 + y, 255, 0, 178);
	gfx.PutPixel(17 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(18 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(20 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(21 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(25 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(26 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(27 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(28 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(32 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(33 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(37 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(38 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(41 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(42 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(43 + x, 8 + y, 0, 146, 14);
	gfx.PutPixel(44 + x, 8 + y, 0, 146, 14);
}