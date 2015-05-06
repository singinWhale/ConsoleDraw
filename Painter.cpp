#include "Painter.h"

Painter::Painter()
{
	hWnd = GetConsoleWindow();
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	hDCDisplay = GetDC(hWnd);
	hDCDraw = CreateCompatibleDC(hDCDisplay);
}

/*
Draws a single Bitmap into hDC, 1:1 stretch.
hDC: Drawing DC,
fX: x-Pos,
fY: y-Pos,
fWidth: x-Dimensions,
fWidth: y-Dimensions,
hbm: Handle of Bitmap,
bm: Loaded Bitmap,
clrAlphaChannel: Which color should be transparent;
*/
void Painter::drawBitmap(float fX, float fY, float fWidth, float fHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel){
	HDC hdcMem = CreateCompatibleDC(hDCDraw);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);
	GetObject(hbm, sizeof(bm), &bm);
	TransparentBlt(hDCDraw, (int)fX, (int)fY, (int)fWidth, (int)fHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, clrAlphaChannel);
	//BitBlt(hDC, _x, _y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}

/*
Draws a single Bitmap into hDC, includes scaling.
hDC: Drawing DC,
fX: x-Pos,
fY: y-Pos,
fWidth: x-Dimensions,
fWidth: y-Dimensions,
hbm: Handle of Bitmap,
bm: Loaded Bitmap,
fInBitmap... = part of Bitmap rectangle.
clrAlphaChannel: Which color should be transparent;
*/
void Painter::drawBitmapEx(float fX, float fY, float fWidth, float fHeight, float fInbitmapX, float fInBitmapY, float fInBitmapWidth, float fInBitmapHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel){
	HDC hdcMem = CreateCompatibleDC(hDCDraw);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);
	GetObject(hbm, sizeof(bm), &bm);
	TransparentBlt(hDCDraw, (int)fX, (int)fY, (int)fWidth, (int)fHeight, hdcMem, fInbitmapX, fInBitmapY, fInBitmapWidth, fInBitmapHeight, clrAlphaChannel);
	//BitBlt(hDC, _x, _y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}

/*
MessageBox:
TYPE: MB_...
Declared in "Windows.h"
MB_DEFBUTTON1 LAYOUT !!!
*/
int Painter::msgBox(char * CAPTION, char * TEXT, int TYPE){
	return MessageBoxA(NULL, TEXT, CAPTION, TYPE | MB_DEFBUTTON1);
}


/*
COLORRANGE: HEX: 0x00 to 0xFF
First digit: Backgroundcolor
Last digit: Foregroundcolor
f.ex: 0x0A == black-green (typical matrix style)
*/
void Painter::console::color(int const iColor){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, iColor);
}
/*
Hide Caret (visible(true)/invisible(false))
*/
void Painter::console::caretVisibility(bool const bVisible){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cocuInfo;
	cocuInfo.dwSize = 10;
	if (bVisible)
		cocuInfo.bVisible = 1;
	else
		cocuInfo.bVisible = 0;
	SetConsoleCursorInfo(hCon, &cocuInfo);
}
/*
Move Cursor to (x|y)
*/
void Painter::console::gotoxy(int const x, int const y){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD co = { x, y };
	SetConsoleCursorPosition(hCon, co);
}
/*
Set Title of Console.
*/
void Painter::console::title(char const * TITLE){
	SetConsoleTitleA(TITLE);
}