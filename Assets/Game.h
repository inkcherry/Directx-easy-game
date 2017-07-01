
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"

class Game
{
private:
	enum XOState    //创建一个新的枚举类型
	{
		EMPTY,
		X,
		O
	};
public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();
	void Circle(int basex, int basey, int rad,int player);
	void SetSquareState(int index, XOState state);
    XOState GetSquareState(int index);
	void DravGird(int baseX, int baseY, int size);
	XOState CheckForVictory();
	void DrawTie(int x, int);
	void DrawOWin(int x, int);
	void DrawXWin(int x, int);
	void DrawEndScreen(int x, int y, XOState state);
	void UserInput();
	void DravCursor(int index);
		
private:

	void ComposeFrame();
	

private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	int dx, dy,speed;
	int x, y, player, nTurns;
	XOState s0;
	XOState s1;
	XOState s2;
	XOState s3;
	XOState s4;
	XOState s5;
	XOState s6;
	XOState s7;
	XOState s8;
	XOState s9;
	int cursorPos;
	

};