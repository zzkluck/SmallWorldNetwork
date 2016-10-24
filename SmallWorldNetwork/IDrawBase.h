#pragma once
#include"Definitions.h"
using namespace zzkluck::KBitmap;

class IDrawBase
{
private:
	unsigned BaseX;
	unsigned BaseY;

	virtual Coordinate GetCoordinate(unsigned x, unsigned y) {
		return Coordinate(x + BaseX, y + BaseY);
	}


public:
	IDrawBase();
	IDrawBase(unsigned baseX, unsigned baseY) :BaseX(baseX), BaseY(baseY) {};
	virtual ~IDrawBase();

	virtual void DrawPoint(Coordinate coordinate) = 0;
	virtual void DrawLine(Coordinate point1,Coordinate point2) = 0;
	virtual void DrawCircle(Coordinate center, double radius) = 0;
};

