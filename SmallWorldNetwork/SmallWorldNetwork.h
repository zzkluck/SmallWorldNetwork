#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>
#include<ctime>
#include<list>
#include<cmath>
#include<set>
#include<map>
#include"RGBBitmap.h"
using namespace std;

class Node
{
public:
	Node() :Node(0) {}
	Node(int identifie) :_identifie(identifie) {}
	Node(int identifie, int x, int y) :_identifie(identifie) {}

	unsigned GetID()const { return _identifie; }
	void SetID(unsigned identifie) { _identifie = identifie; }

	bool operator<(const Node& node);
	bool operator>(const Node& node);
	bool operator==(const Node& node);
	bool operator!=(const Node& node);

	bool isNeighbour(Node& node);
	bool isNeighbour(int ID);
	void AddNeighbour(Node& node);
	void RemoveNeighbour(Node& node);
	static void AddNeighbourEach(Node& node1, Node& node2);
	static void RemoveNeighbourEach(Node& node1, Node& node2);
	int NeighboursSize() { return neighbours.size(); }

	int DrawX, DrawY;
	set<int> neighbours;
protected:
	unsigned _identifie;
};

class DrawNode :public Node {
	//该类还未完成,功能暂由基类实现
public:
	DrawNode(int identifie, int x, int y) :Node(identifie), DrawX(x), DrawY(y) {}
	int DrawX, DrawY;
};

class Link
{
	//思来想去之后,决定使用标识符作为link的元素
public:
	Link(int start, int end, bool isDirected, bool allowHoop);
	Link(int start, int end)
		:Link(start, end, false, false) {}
	Link(Node& node1, Node& node2) :
		Link(node1.GetID(), node2.GetID()) {};

	bool operator==(const Link& link);
	bool operator<(const Link& link);
	Link& operator=(const Link& link);

	int GetStartNodeID()const;
	int GetEndNodeID()const;
private:
	inline void MakeSmallerIDStart() {
		if (_isDirected == false)
			if (startNodeID > endNodeID) {
				swap(startNodeID, endNodeID);
			}
	}

	bool _isDirected;
	bool _allowHoop;
	int startNodeID;
	int endNodeID;
};

class VirtualNetWork
{
	//已知问题:"允许有向链接和双向链接同时存在在同一个Link中,这显然是愚蠢的"
public:
	vector<Node> Nodes;
	//map<string, Node> Nodes;
	list<Link> Links;

	VirtualNetWork() = default;

	void AddNodesDefault(int n);
	void BuildLinksDefault(int k);
	void Relink(double relinkProbability, double relinkStartOrEnd);

	double getClusteringCoefficient(int nodeID);
	int getShortestWayLength(int nodeID1, int nodeID2);

	inline void Buid_TwoWay_Link(Node& node1, Node& node2);
	inline int VirtualNetWork::GetNextNodeIndex(unsigned startNodeIndex, int offs) {
		assert(startNodeIndex < Nodes.size());
		return  (startNodeIndex + offs + Nodes.size()) % Nodes.size();
	}
	inline int getIndex(int ID) {
		return ID - 1;
	}
	inline int getID(int Index) {
		return Index + 1;
	}

private:
	inline static double Rand0_1() {
		return (double)rand() / RAND_MAX;
	}
	inline static int Rand0_X(int x) {
		assert(x > 0);
		return rand() % x;
	}
	int length = 1;
};






