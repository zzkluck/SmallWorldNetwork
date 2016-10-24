#include "DrawNetwork.h"
void DrawNetwork::setNodesAsCircle() {
	double angle = 0;
	for (auto beg = Nodes.begin(); beg != Nodes.end(); beg++) {
		beg->DrawX = (int)(_Width / 2 + 3 * _Width / 8 * sin(angle));
		beg->DrawY = (int)(_Height / 2 + 3 * _Height / 8 * cos(angle));
		angle += 2 * PI / Nodes.size();
	}
}
void DrawNetwork::drawAllNodes() {
	for (auto beg = Nodes.begin(); beg != Nodes.end(); beg++) {
		DrawPoint(beg->DrawX, beg->DrawY, BrushType::Rectangle);
	}
}
void DrawNetwork::drawAllLinks() {
	for (auto beg = Links.begin(); beg != Links.end(); beg++) {
		DrawLine
		(Coordinate(Nodes[beg->GetStartNodeID() - 1].DrawX, Nodes[beg->GetStartNodeID() - 1].DrawY),
			Coordinate(Nodes[beg->GetEndNodeID() - 1].DrawX, Nodes[beg->GetEndNodeID() - 1].DrawY));
	}
}
void DrawNetwork::setBrushColor(RGBColor color) {
	BrushColor = color;
}
void DrawNetwork::WriteToFile(string path) {
	Write(path);
}