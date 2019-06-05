#include "BplusNode.h"
#include <cassert>

BplusNode::BplusNode()
		:maxDataSize(0)
{
	datas.clear();
	childPtrs.clear();
}

BplusNode::BplusNode(int maxSize)
		:maxDataSize(maxSize)
{
	datas.clear();
	childPtrs.clear();
}

RC BplusNode::findData(ValType data, BplusNode* & childPtr){
	childPtr = NULL;
	unsigned int i;
	for(i=0; i < datas.size(); i++){
		if(datas[i] == data){
			return SUCCESS;
		} else if(datas[i] > data){
			break;
		}
	}

	childPtr = childPtrs[i];
	if(childPtr == NULL){
		assert(childPtr!=NULL);
		return -1;
	}

	return -1;
}

int BplusNode::getDatasSize(){
	return datas.size();
}

int BplusNode::getChildPtrsSize(){
	return childPtrs.size();
}

BplusNode::~BplusNode(){
	datas.clear();
	childPtrs.clear();
}
