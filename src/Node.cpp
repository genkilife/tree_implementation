#include "Node.h"

BinaryNode::BinaryNode(){
	left = right = NULL;
	height=0;
}

BinaryNode::BinaryNode(ValType idata){
	left = right = NULL;
	data = idata;
	height=0;
}

BinaryNode::~BinaryNode(){
	if(left != NULL)
		delete left;
	if(right!= NULL)
		delete right;
}
