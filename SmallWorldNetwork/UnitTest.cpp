#include"SmallWorldNetwork.h"
#include"DEBUG.h"

static int MainReturn = 0;
static int TestCount = 0;
static int TestPass = 0;
#define EXPECT_EQ_BASE(equality,expect,actual,format)\
	do{\
		TestCount++;\
		if(equality)\
			TestPass++;\
		else{\
			fprintf(stderr,"%s:%d: espect: " format "  actual: " format "\n",__FILE__,__LINE__,expect,actual);\
			MainReturn=1;\
		}\
	} while (0);

#define EXPECT_EQ_INT(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual,"%d")
#define EXPECT_EQ_DOU(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual,"%lf")

#ifdef DEBUG
static void test_Node() {
	Node node1;
	Node node2(1);
	DrawNode node3(2, 10, 10);
	Node node4(3);
	DrawNode node5(2, 34325, 5342675);

	EXPECT_EQ_INT(0, node1.GetID());
	EXPECT_EQ_INT(1, node2.GetID());
	EXPECT_EQ_INT(10, node3.DrawX);
	EXPECT_EQ_INT(2, node5.GetID());

	EXPECT_EQ_INT(1, node1 < node2);
	//是的,我们会认为像n3和n5这样的两个节点相等,这不是Bug,这是一个feature.
	EXPECT_EQ_INT(1, (Node)node3 == (Node)node5);
	EXPECT_EQ_INT(1, node2 != node3);

	EXPECT_EQ_INT(0, node1.isNeighbour(node2));
	node1.AddNeighbour(node2);
	EXPECT_EQ_INT(1, node1.isNeighbour(node2));
	EXPECT_EQ_INT(0, node2.isNeighbour(node1));
	Node::AddNeighbourEach(node2, node3);
	EXPECT_EQ_INT(1, node2.isNeighbour(node3));
	EXPECT_EQ_INT(1, node3.isNeighbour(node2));

	node2.AddNeighbour(node4);
	EXPECT_EQ_INT(2, node2.NeighboursSize());
}
static void test_Link()
{
	Node n1;
	Node n2(1);
	DrawNode n3(2, 10, 10);
	DrawNode n4(3, 2414, 1535);

	Link link1(n2, n1);
	EXPECT_EQ_INT(0, link1.GetStartNodeID());
	EXPECT_EQ_INT(1, link1.GetEndNodeID());

	Link link2(n1, n2);
	EXPECT_EQ_INT(1, link1 == link2);

	Link link3 = link1;
	EXPECT_EQ_INT(1, link3 == link1);
	EXPECT_EQ_INT(1, link2 == link3);
}
static void test_VirtualNetwork() {
	VirtualNetWork myNetwork;

	myNetwork.AddNodesDefault(1000);
	EXPECT_EQ_INT(1000, myNetwork.Nodes.size());

	EXPECT_EQ_INT(999, myNetwork.GetNextNodeIndex(0, -1));
	EXPECT_EQ_INT(1, myNetwork.GetNextNodeIndex(0, 1));
	EXPECT_EQ_INT(0, myNetwork.GetNextNodeIndex(999, 1));
	EXPECT_EQ_INT(677, myNetwork.GetNextNodeIndex(145, 532));

	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[0], myNetwork.Nodes[myNetwork.GetNextNodeIndex(0, -1)]);
	EXPECT_EQ_INT(1, *myNetwork.Links.begin() == Link(1, 1000));
	EXPECT_EQ_INT(1, myNetwork.Nodes[0].isNeighbour(myNetwork.Nodes[999]));
	EXPECT_EQ_INT(1, myNetwork.Nodes[999].isNeighbour(myNetwork.Nodes[0]));

	myNetwork.BuildLinksDefault(4);
	EXPECT_EQ_INT(4000, myNetwork.Links.size());

	myNetwork.Relink(0.5, 0.5);
	EXPECT_EQ_INT(4000, myNetwork.Links.size());
}

static void test_NetworkCompute() {
	VirtualNetWork myNetwork;
	myNetwork.AddNodesDefault(4);
	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[0], myNetwork.Nodes[1]);
	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[0], myNetwork.Nodes[2]);
	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[0], myNetwork.Nodes[3]);

	EXPECT_EQ_DOU(0.0, myNetwork.getClusteringCoefficient(1));
	//EXPECT_EQ_INT(1, myNetwork.getShortestWayLength(1, 2));
	//EXPECT_EQ_INT(2, myNetwork.getShortestWayLength(3, 2));

	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[1], myNetwork.Nodes[2]);
	EXPECT_EQ_DOU((1 / 3), myNetwork.getClusteringCoefficient(1));
	//EXPECT_EQ_INT(1, myNetwork.getShortestWayLength(3, 2));

	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[1], myNetwork.Nodes[3]);
	EXPECT_EQ_DOU((2 / 3), myNetwork.getClusteringCoefficient(1));

	myNetwork.Buid_TwoWay_Link(myNetwork.Nodes[3], myNetwork.Nodes[2]);
	EXPECT_EQ_DOU(1.0, myNetwork.getClusteringCoefficient(1));

	
}
static void test_parse() {
	test_Node();
	test_Link();
	//test_VirtualNetwork();
	test_NetworkCompute();
}


int main() {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", TestPass, TestCount, TestPass * 100.0 / TestCount);
	getchar();
	return MainReturn;
}
#endif // DEBUG

