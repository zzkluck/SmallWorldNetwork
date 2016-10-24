#pragma once
#include "BaseBitmap.h"
#include "IDrawBase.h"
#include<vector>
#include<assert.h>
#include<fstream>
#include"Definitions.h"

using namespace std;
//using Coordinate = IDrawBase::Coordinate;
using namespace zzkluck::KBitmap;


class RGBBitmap :
	public BaseBitmap,public IDrawBase
{
public:
	RGBBitmap();
	RGBBitmap
	(unsigned width, unsigned height, unsigned BaseX, unsigned BaseY, RGBColor background = { 0,0,0 });
	RGBBitmap
	(unsigned width, unsigned height, RGBColor background = { 0,0,0 });
	~RGBBitmap();

	vector<RGBColor> colors;
	RGBColor BrushColor;
	
	void Write(ostream& os)const override;
	void Write(string path)const override;
	void Read(istream& is)override;
	void Read(string path)override;


	void DrawPoint(unsigned BaseX, unsigned BaseY, BrushType brushType);
	void DrawPoint(Coordinate coordinate) override;
	void DrawLine(Coordinate point1, Coordinate point2);
	void DrawCircle(Coordinate center, double radius);

	void ChangeBrushColor(RGBColor color);
	void ChangeBrushColor(unsigned char r, unsigned char g, unsigned b);

private:
	void WriteColors(ostream &os) const;
	void ReadColors(istream &is);
};

