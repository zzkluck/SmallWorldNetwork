#pragma once
namespace zzkluck {
	namespace KBitmap{

		enum BrushType {
			Point, HorizontalLine, VerticalLine, Rectangle
		};


		struct RGBColor {
			RGBColor() {};
			RGBColor(unsigned char r, unsigned char g, unsigned b) :b(b), g(g), r(r) {}
			unsigned char b;
			unsigned char g;
			unsigned char r;
		};

		typedef unsigned long DWORD;
		typedef unsigned short WORD;
		typedef unsigned char BYTE;
		typedef long LONG;
		typedef struct {
			DWORD bfSize;
			WORD bfReserved0;
			WORD bfReserved1;
			DWORD bfOffbits;
		}BITMAPFILEHEADER;
		typedef struct {
			DWORD biSize;
			LONG biWidth;
			LONG biHeight;
			WORD biPlane;
			WORD biBitCount;
			DWORD biCompression;
			DWORD biSizeImage;
			LONG biXPelsPerMeter;
			LONG biYPelsPerMeter;
			DWORD biClrUsed;
			DWORD biclrImportant;
		}BITMAPINFOHEADER;
		typedef struct {
			BYTE rgbBlue;
			BYTE rgbGreen;
			BYTE rgbRed;
			BYTE rgbReserved;
		}RGBQUAD;

		typedef enum
		{
			DEFAULT
		}BitmapUseMode;

		struct Coordinate
		{
			Coordinate(unsigned x, unsigned y) :x(x), y(y) {}
			unsigned x;
			unsigned y;
		};
	}
}