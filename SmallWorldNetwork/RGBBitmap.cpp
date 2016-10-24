#include "RGBBitmap.h"
#define DRAW_POINT(X,Y) colors[X+Y*_Height]=BrushColor
using namespace zzkluck::KBitmap;
RGBBitmap::RGBBitmap()
{

}

RGBBitmap::RGBBitmap
(unsigned width, unsigned height, unsigned baseX, unsigned baseY, RGBColor background) :
	BaseBitmap(width, height), IDrawBase(baseX, baseY)
{
	this->infoheader.biBitCount = 24;
	this->colors.resize(infoheader.biHeight*infoheader.biWidth, background);
}

RGBBitmap::RGBBitmap(unsigned width, unsigned height, RGBColor background) :
	RGBBitmap(width, height, 0, 0, background)
{
}

RGBBitmap::~RGBBitmap()
{
}

void RGBBitmap::DrawPoint(Coordinate coordinate)
{
	DrawPoint(coordinate.x, coordinate.y, BrushType::Point);
}
void RGBBitmap::DrawPoint(unsigned x, unsigned y, BrushType brushType)
{
	assert(x < _Width&&y < _Height);

	switch (brushType)
	{
	case Point:
		colors[x + y*_Height] = BrushColor;
		break;
	case HorizontalLine:
		break;
	case VerticalLine:
		break;
	case Rectangle:
		colors[x + y*_Height] = BrushColor;
		colors[x + y*_Height + 1] = BrushColor;
		colors[x + y*_Height - 1] = BrushColor;
		colors[x + y*_Height + _Height] = BrushColor;
		colors[x + y*_Height - _Height] = BrushColor;
		break;
	default:
		break;
	}
}
void RGBBitmap::DrawLine(Coordinate point1, Coordinate point2)
{
	int dy = point2.y - point1.y;
	int dx = point2.x - point1.x;
	int x = point1.x;
	int y = point1.y;
	int sx, sy;

	if (dx > 0)
		sx = 1;
	else if (dx < 0) {
		sx = -1;
		dx = -dx;
	}
	else
		dx = 0;
	if (dy > 0)
		sy = 1;
	else if (dy < 0) {
		sy = -1;
		dy = -dy;
	}
	else
		dy = 0;

	int ax = 2 * dx, ay = 2 * dy;
	if (dy <= dx) {
		for (int decy = ay - dx;; x += sx, decy += ay) {
			DrawPoint(x, y, BrushType::Rectangle);
			if (x == point2.x)
				break;
			if (decy >= 0) {
				decy -= ax;
				y += sy;
			}
		}
	}
	else {
		for (int decx = ax - dy;; y += sy, decx += ax) {
			DrawPoint(x, y, BrushType::Rectangle);
			if (y == point2.y)
				break;
			if (decx >= 0) {
				decx -= ay;
				x += sx;
			}
		}
	}

}




void RGBBitmap::DrawCircle(Coordinate center, double radius)
{
}


void RGBBitmap::Write(ostream & os) const
{
	WriteHeader(os);
	WriteColors(os);
}

void RGBBitmap::Write(string path) const
{
	ofstream os(path);
	assert(os);
	this->Write(os);
	os.close();
}

void RGBBitmap::Read(istream & is)
{
	this->ReadHeader(is);
	this->ReadColors(is);
}

void RGBBitmap::Read(string path)
{
	ifstream is(path);
	assert(is);
	this->Read(is);
	is.close();
}

void RGBBitmap::ChangeBrushColor(RGBColor color)
{
	this->BrushColor = color;
}

void RGBBitmap::ChangeBrushColor(unsigned char r, unsigned char g, unsigned b)
{
	this->BrushColor = RGBColor(r, g, b);
}

void RGBBitmap::WriteColors(ostream & os)const
{
	assert(colors.size() >= infoheader.biWidth*infoheader.biHeight);

	for (auto beg = colors.begin(); beg < colors.end();) {
		for (auto i = 0; i != infoheader.biWidth; i++) {
			os.write((char*)&*beg, sizeof(RGBColor));
			beg++;
		}
		for (auto i = 0; i != LineOffsetByteCnt; i++) {
			os.write((char*)'0', 1);
			beg++;
		}
	}
}

void RGBBitmap::ReadColors(istream & is)
{
	colors.resize(infoheader.biHeight*infoheader.biWidth);
	for (auto beg = colors.begin(); beg < colors.end();) {
		for (auto i = 0; i != infoheader.biWidth; i++) {
			is.read((char*)&*beg, sizeof(RGBColor));
			beg++;
		}
		is.ignore(LineOffsetByteCnt);
	}
}

