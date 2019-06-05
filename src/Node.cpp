#include "Node.h"

void BinaryNode::BinaryNode(){
	left = right = NULL;
}

void BinaryNode::BinaryNode(ValType idata){
	data = idata;
}

void BinaryNode::~BinaryNode(){
	if(left != NULL)
		delete left;
	if(right!= NULL)
		delete right;
}
