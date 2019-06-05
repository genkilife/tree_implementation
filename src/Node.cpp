#include "Node.h"

BinaryNode::BinaryNode(){
	left = right = NULL;
}

BinaryNode::BinaryNode(ValType idata){
	data = idata;
}

BinaryNode::~BinaryNode(){
	if(left != NULL)
		delete left;
	if(right!= NULL)
		delete right;
}
