#include<Windows.h>

class Painter
{

private:
	HANDLE hCon;
	HWND hWnd;

	HDC hDCDisplay;
	HDC hDCDraw;

public:
	//no public variables

private:
	Painter();

	//private copy constructors to prevent copies
	Painter(Painter const& copy);
	Painter& operator=(Painter const& copy);


public:

	/*
	Returns the Painter Instance. If none exists yet it is created;
	*/
	static Painter& getInstance()
	{
		static Painter instance;
		return instance;
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
	void drawBitmap(float fX, float fY, float fWidth, float fHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel);

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
	void drawBitmapEx(float fX, float fY, float fWidth, float fHeight, float fInbitmapX, float fInBitmapY, float fInBitmapWidth, float fInBitmapHeight, HBITMAP hbm, BITMAP bm, COLORREF clrAlphaChannel);

	/*
	MessageBox:
	TYPE: MB_...
	Declared in "Windows.h"
	MB_DEFBUTTON1 LAYOUT !!!
	*/
	int msgBox(char * CAPTION, char * TEXT, int TYPE);

	class console{
	private:
		friend class Painter;
		HANDLE* hCon;
	public:
		class chars{
		private:
			chars();
		public:
			class uml{
			private:
				uml();
			public:
				static const char cauml = '„';
				static const char cAuml = 'Ž';
				static const char cuuml = '';
				static const char cUuml = 'š';
				static const char couml = '”';
				static const char cOuml = '™';
				static const char csharps = 'á';
			};
			class border_single{
			private:
				border_single();
			public:
				static const char cLeftUpperCorner = 'Ú';
				static const char cLeftMiddleCorner = 'Ã';
				static const char cLeftLowerCorner = 'Ù';

				static const char cVerticalLine = '³';
				static const char cHorizontalLine = 'Ä';

				static const char cRightUpperCorner = 'Ú';
				static const char cRightMiddleCorner = '´';
				static const char cRightLowerCorner = 'Ù';

				static const char cUpperMiddleCorner = 'Â';
				static const char cLowerMiddleCorner = 'Á';

				static const char cCenterCross = 'Å';
			};

			class border_double{
			private:
				border_double();
			public:
				static const char cLeftUpperCorner = 'É';
				static const char cLeftMiddleCorner = 'Ì';
				static const char cLeftLowerCorner = 'È';

				static const char cVerticalLine = 'º';
				static const char cHorizontalLine = 'Í';

				static const char cRightUpperCorner = '»';
				static const char cRightMiddleCorner = '¹';
				static const char cRightLowerCorner = '¼';

				static const char cUpperMiddleCorner = 'Ë';
				static const char cLowerMiddleCorner = 'Ê';

				static const char cCenterCross = 'Î';
			};

			class block{
			private:
				block();
			public:
				static const char cBlockDensity0 = ' ';
				static const char cBlockDensity1 = '°';
				static const char cBlockDensity2 = '±';
				static const char cBlockDensity3 = '²';
				static const char cBlockDensity4 = 'Û';

				static const char cUpperHalfBlock = 'Ü';
				static const char cLowerHalfBlock = 'ß';

			};
		};
	private:
		console();
		console(HANDLE* p_hCon);
		console(console const& copy); //dont allow copies -> not implemented
	public:
		/*
		COLORRANGE: HEX: 0x00 to 0xFF
		First digit: Backgroundcolor
		Last digit: Foregroundcolor
		f.ex: 0x0A == black-green (typical matrix style)
		*/
		void color(int const iColor);
		/*
		Hide Caret (visible(true)/invisible(false))
		*/
		void caretVisibility(bool const bVisible);
		/*
		Move Cursor to (x|y)
		*/
		void gotoxy(int const x, int const y);
		/*
		Set Title of Console.
		*/
		void title(char const * TITLE);
	};
};