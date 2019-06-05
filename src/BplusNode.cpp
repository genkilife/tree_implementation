#include "BplusNode.h"
#include <cassert>

BplusNode::BplusNode()
		:maxDataSize(0)
{
	datas.clear();
	childPtrs.clear();
}

BplusNode::BplusNode(unsigned int maxSize)
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

RC BplusNode::insertData(ValType data){
	if(datas.size() == maxDataSize){
		return -1;
	}

	if(datas.size() == 0){
		datas.push_back(data);
		childPtrs.push_back(NULL);
		childPtrs.push_back(NULL);
		return SUCCESS;
	}
	unsigned int i;
	for(i=0; i<datas.size(); i++){
		if(data < datas[i]){
			break;
		}
	}

	datas.insert(datas.begin()+i, data);
	childPtrs.push_back(NULL);

	return SUCCESS;
}


int BplusNode::getDatasSize(){
	return datas.size();
}

int BplusNode::getChildPtrsSize(){
	return childPtrs.size();
}

ValType BplusNode::getData(unsigned int index){
	return datas[index];
}

RC BplusNode::setChildPtr(unsigned int index, BplusNode* nodePtr){
	childPtr[index] = nodePtr;
	return SUCCESS;
}

BplusNode::~BplusNode(){
	datas.clear();
	childPtrs.clear();
}
