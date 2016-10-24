#include"SmallWorldNetwork.h"

#pragma region Node
bool Node::operator<(const Node& node) {
	return this->_identifie < node.GetID();
}
bool Node::operator>(const Node& node) {
	return this->_identifie > node.GetID();
}
bool Node::operator==(const Node& node) {
	return this->_identifie == node.GetID();
}
bool Node::operator!=(const Node& node) {
	return this->_identifie != node.GetID();
}
bool Node::isNeighbour(Node& node) {
	//TODO:如果对neighbours维持排序的话,这个查找算法可以优化为二分搜索
	return this->isNeighbour(node.GetID());
}
bool Node::isNeighbour(int ID)
{
	if (find(neighbours.begin(), neighbours.end(), ID) == neighbours.end())
		return false;
	return true;
	return false;
}
void Node::AddNeighbour(Node& node) {
	if (this->isNeighbour(node) == false)
		neighbours.insert(node.GetID());
}
void Node::RemoveNeighbour(Node& node) {
	auto target = find(neighbours.begin(), neighbours.end(), node.GetID());
	if (target != neighbours.end()) {
		neighbours.erase(target);
	}
}
void Node::AddNeighbourEach(Node& node1, Node& node2) {
	node1.AddNeighbour(node2);
	node2.AddNeighbour(node1);
}
void Node::RemoveNeighbourEach(Node& node1, Node& node2) {
	node1.RemoveNeighbour(node2);
	node2.RemoveNeighbour(node1);
}
#pragma endregion

#pragma region Link
Link::Link(int start, int end, bool isDirected, bool allowHoop)
	:startNodeID(start), endNodeID(end), _isDirected(isDirected), _allowHoop(allowHoop)
{
	//如果link是无向的,始终保持id较小的节点为start节点
	MakeSmallerIDStart();
}

Link& Link::operator=(const Link& link) {
	this->startNodeID = link.startNodeID;
	this->endNodeID = link.endNodeID;
	this->_isDirected = link._isDirected;
	this->_allowHoop = link._allowHoop;
	return *this;
}

bool Link::operator==(const Link& link) {
	if (this->startNodeID == link.startNodeID&&
		this->endNodeID == link.endNodeID)
		return true;
	else
		return false;
}

bool Link::operator<(const Link& link) {
	if (this->startNodeID != link.startNodeID)
		return this->startNodeID < link.startNodeID;
	else
		return this->endNodeID < link.endNodeID;
}
int Link::GetStartNodeID()const { return startNodeID; }
int Link::GetEndNodeID()const { return endNodeID; }

#pragma endregion

#pragma region VirtualNetWork
void VirtualNetWork::AddNodesDefault(int n)
{
	//添加标识符从1到n的N个节点
	for (int i = 1; i <= n; i++)
		Nodes.push_back(Node(i));
}
void VirtualNetWork::BuildLinksDefault(int k)
{
	assert(Nodes.size() != 0);
	for (int StartNodeIndex = 0; StartNodeIndex != Nodes.size(); StartNodeIndex++) {
		for (int i = 1; i <= k; i++) {
			Buid_TwoWay_Link(Nodes[StartNodeIndex],
				Nodes[GetNextNodeIndex(StartNodeIndex, i)]);
			Buid_TwoWay_Link(Nodes[StartNodeIndex],
				Nodes[GetNextNodeIndex(StartNodeIndex, -i)]);
		}
	}
}
inline void VirtualNetWork::Buid_TwoWay_Link(Node& node1, Node& node2) {
	assert(node1 != node2);
	if (find(Links.begin(), Links.end(), Link(node1, node2)) == Links.end()) {
		Links.push_back(Link(node1, node2));
		Node::AddNeighbourEach(node1, node2);
	}
}
void VirtualNetWork::Relink(double RelinkProbability, double RelinkWhichNodeProbability)
{
	list<Link> newLinks;
	srand((unsigned)time(NULL));
	for (auto beg = Links.begin(); beg != Links.end(); beg++) {
		if (Rand0_1() < RelinkProbability) {
			Node::RemoveNeighbourEach(Nodes[getIndex(beg->GetStartNodeID())],
				Nodes[getIndex(beg->GetEndNodeID())]);

			int oldLinkNodeIndex;
			if (Rand0_1() < RelinkWhichNodeProbability)
				oldLinkNodeIndex = getIndex(beg->GetEndNodeID());
			else
				oldLinkNodeIndex = getIndex(beg->GetStartNodeID());

			int newLinkNodeIndex = Rand0_X(Nodes.size());
			while (Nodes[oldLinkNodeIndex].isNeighbour(newLinkNodeIndex)
				|| oldLinkNodeIndex == newLinkNodeIndex) {
				newLinkNodeIndex += 1;
				if (newLinkNodeIndex == Nodes.size())
					newLinkNodeIndex -= Nodes.size();
			}

			newLinks.push_back(Link(newLinkNodeIndex + 1, oldLinkNodeIndex + 1));

		}
		else
		{
			newLinks.push_back(*beg);
		}
	}
	Links.clear();
	Links = newLinks;
}
double VirtualNetWork::getClusteringCoefficient(int nodeID) {
	int e = 0;
	set<int>& temp = Nodes[getIndex(nodeID)].neighbours;
	for (auto neighbor : temp) {
		for (auto nowNeighbors : Nodes[getIndex(neighbor)].neighbours) {
			if (temp.find(nowNeighbors) != temp.end()) {
				e += 1;
			}
	}
	return e / temp.size() / (temp.size() - 1);
}
#pragma endregion