
#pragma once

#include <d3d9.h>

class D3DGraphics
{
public:
	D3DGraphics( HWND hWnd );
	~D3DGraphics();
	void PutPixel( int x,int y,int r,int g,int b );
	void BeginFrame();
	void EndFrame();
	void DravCircle(int cx, int cy, int rad, int r, int g, int b);
private:
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
};