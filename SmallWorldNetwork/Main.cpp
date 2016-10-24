#include"DrawNetwork.h"
#include"DEBUG.h"

#define NodeCount 1000
#define DefaultNeighborCount 8
#define RelinkProbability 0.5
#define RelinkStartOrEnd 0.5
#define DefaultCanvasSize 1000
#define LineColor RGBColor(0x66, 0xcc, 0xff)

#ifndef DEBUG
int main() {
	DrawNetwork myNetwork(DefaultCanvasSize, DefaultCanvasSize);

	myNetwork.AddNodesDefault(NodeCount);
	myNetwork.BuildLinksDefault(DefaultNeighborCount/2);

	myNetwork.setNodesAsCircle();
	
	myNetwork.drawAllNodes();
	myNetwork.setBrushColor(LineColor);
	myNetwork.drawAllLinks();

	//myNetwork.WriteToFile("D:\\Network.bmp");

	myNetwork.Relink(RelinkProbability,RelinkStartOrEnd);
	myNetwork.drawAllLinks();

	myNetwork.WriteToFile("D:\\NetworkAfterRelink.bmp");
}
#endif // !DEBUG