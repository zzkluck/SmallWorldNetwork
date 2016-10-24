#pragma once
#include"RGBBitmap.h"
#include"SmallWorldNetwork.h"

class DrawNetwork :public VirtualNetWork, RGBBitmap
{
public:
	const double PI = 3.1415936;
	DrawNetwork(int width, int height) :RGBBitmap(width, height) {}

	void setNodesAsCircle();
	void drawAllNodes();
	void drawAllLinks();
	void setBrushColor(RGBColor color);
	void WriteToFile(string path);
};
