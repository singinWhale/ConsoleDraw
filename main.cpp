#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")
namespace paint{
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
	void drawTile(HDC hDC, float fX, float fY, float fWidth, float fHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel){
		HDC hdcMem = CreateCompatibleDC(hDC);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);
		GetObject(hbm, sizeof(bm), &bm);
		TransparentBlt(hDC, (int)fX, (int)fY, (int)fWidth, (int)fHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, clrAlphaChannel);
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
	void drawTileEx(HDC hDC, float fX, float fY, float fWidth, float fHeight, float fInbitmapX, float fInBitmapY, float fInBitmapWidth, float fInBitmapHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel){
		HDC hdcMem = CreateCompatibleDC(hDC);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);
		GetObject(hbm, sizeof(bm), &bm);
		TransparentBlt(hDC, (int)fX, (int)fY, (int)fWidth, (int)fHeight, hdcMem, fInbitmapX, fInBitmapY, fInBitmapWidth, fInBitmapHeight, clrAlphaChannel);
		//BitBlt(hDC, _x, _y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
	}
	/* DOESN'T WORK YET !!!!
	hDC: Drawing DC,
	HWND: Your Window-Handle. (in console: GetConsoleWindow())
	YourPaintMethod: your personal paint-method:
	f. ex.:
	#include <Windows.h>
	void paint(){
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	//Do sth here like DrawFancyShit(hDC, x, y);
	ReleaseDC(hWnd, hDC);
	}
	-> use DoubleBuffer(GetConsoleWindow(), paint); instead of your pure paint();
	=> paint() fills a paint buffer and split surface.
	*/
	void doubleBuffer(HWND hWnd, void(*YourPaintMethod)()){
		HDC hDC = GetDC(hWnd);
		RECT recWindow;
		GetWindowRect(hWnd, &recWindow);
		HBITMAP hBitmapBuffer = CreateCompatibleBitmap(hDC, recWindow.right, recWindow.bottom);
		HDC hDCMem = CreateCompatibleDC(hDC);
		SelectObject(hDCMem, hBitmapBuffer);//Init Buffer als Bitmap
		//Hier beginnst du das malen! Du musst aber in das BufferDC schreiben!! -> hDCMem
		{
			//PAINT
			YourPaintMethod();
			//WICHTIG!! Falls du einen Kreis malst und verschiedene Brushes initialisierst, musst du die am ende wieder lˆschen!!
			//Sonst hast du das Problem dass wenn du was malst die GDI-Objekte-Heaps voll sind und du somit nur noch weiﬂe RECTS bzw Ellipsen, etc malen kannst...
		}
		//Ende vom malen!
		BitBlt(hDC, 0, 0, recWindow.right, recWindow.bottom, hDCMem, 0, 0, SRCCOPY);//Ganzer Buffer hDCMem ausgeben
		DeleteDC(hDCMem);
		DeleteObject(hBitmapBuffer);
	}

	/*
	MessageBox:
	TYPE: MB_...
	Declared in "Windows.h"
	MB_DEFBUTTON1 LAYOUT !!!
	*/
	int msgBox(char * CAPTION, char * TEXT, int TYPE){
		return MessageBoxA(NULL, TEXT, CAPTION, TYPE | MB_DEFBUTTON1);
	}


}

////////////////////////////////////////////////////////////////////////CONSOLEEXTRA
namespace console{
	namespace chars{
		namespace uml{
			const char cauml = 'Ñ';
			const char cAuml = 'é';
			const char cuuml = 'Å';
			const char cUuml = 'ö';
			const char couml = 'î';
			const char cOuml = 'ô';
			const char csharps = '·';
		}
		namespace border_single{
			const char cLeftUpperCorner = '⁄';
			const char cLeftMiddleCorner = '√';
			const char cLeftLowerCorner = 'Ÿ';

			const char cVerticalLine = '≥';
			const char cHorizontalLine = 'ƒ';

			const char cRightUpperCorner = '⁄';
			const char cRightMiddleCorner = '¥';
			const char cRightLowerCorner = 'Ÿ';

			const char cUpperMiddleCorner = '¬';
			const char cLowerMiddleCorner = '¡';

			const char cCenterCross = '≈';
		}

		namespace border_double{
			const char cLeftUpperCorner = '…';
			const char cLeftMiddleCorner = 'Ã';
			const char cLeftLowerCorner = '»';

			const char cVerticalLine = '∫';
			const char cHorizontalLine = 'Õ';

			const char cRightUpperCorner = 'ª';
			const char cRightMiddleCorner = 'π';
			const char cRightLowerCorner = 'º';

			const char cUpperMiddleCorner = 'À';
			const char cLowerMiddleCorner = ' ';

			const char cCenterCross = 'Œ';
		}

		namespace block{
			const char cBlockDensity0 = ' ';
			const char cBlockDensity1 = '∞';
			const char cBlockDensity2 = '±';
			const char cBlockDensity3 = '≤';
			const char cBlockDensity4 = '€';

			const char cUpperHalfBlock = '‹';
			const char cLowerHalfBlock = 'ﬂ';
		}
	}

	/*
	COLORRANGE: HEX: 0x00 to 0xFF
	First digit: Backgroundcolor
	Last digit: Foregroundcolor
	f.ex: 0x0A == black-green (typical matrix style)
	*/
	void color(int iColor){
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hCon, iColor);
	}
	/*
	Hide Caret (visible(true)/invisible(false))
	*/
	void caretVisibility(bool bVisible){
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
	void gotoxy(int x, int y){
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD co = { x, y };
		SetConsoleCursorPosition(hCon, co);
	}
	/*
	Set Title of Console.
	*/
	void title(char * TITLE){
		SetConsoleTitleA(TITLE);
	}
}



//////////////////////////////////////////////////////////////////////////////////TESTAREA

int main(){
	
	return 0;
}