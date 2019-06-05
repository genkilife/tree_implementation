#include "BplusNode.h"

BplusNode::BplusNode()
		:maxDataSize(0)
{
	datas.clear();
	childPtr.clear();
}

BplusNode::BplusNode(int maxSize)
		:maxDataSize(maxSize)
{
	datas.clear();
	childPtr.clear();
}

BplusNode::~BplusNode(){
	datas.clear();
	childPtr.clear();
}
