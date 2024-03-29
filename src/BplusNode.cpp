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
	if(datas.size()==0){
		return -1;
	}
	for(i=0; i < datas.size(); i++){
		if(datas[i] == data){
			return SUCCESS;
		} else if(datas[i] > data){
			break;
		}
	}

	childPtr = childPtrs[i];
	return -1;
}

unsigned int BplusNode::insertData(ValType data){
	if(datas.size() == maxDataSize){
		return datas.size();
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
	childPtrs.insert(childPtrs.begin()+i+1, NULL);

	return i;
}


unsigned int BplusNode::getDatasSize(){
	return datas.size();
}

int BplusNode::getChildPtrsSize(){
	return childPtrs.size();
}

ValType BplusNode::getData(unsigned int index){
	return datas[index];
}

BplusNode* BplusNode::getChild(unsigned int index){
	return childPtrs[index];
}

RC BplusNode::setChildPtr(unsigned int index, BplusNode* nodePtr){
	childPtrs[index] = nodePtr;
	return SUCCESS;
}

BplusNode* BplusNode::getChildPtr(unsigned int index){
	return childPtrs[index];
}

RC BplusNode::newChildPtr(unsigned int index){
	childPtrs[index] = new BplusNode(maxDataSize);
	return SUCCESS;
}

RC BplusNode::resizeNode(unsigned int size){
	datas.resize(size);
	childPtrs.resize(size+1);
	return SUCCESS;
}

BplusNode::~BplusNode(){
	datas.clear();
	childPtrs.clear();
}
