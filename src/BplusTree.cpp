#include "BplusTree.h"

BplusTree::BplusTree(){
	maxChildSize = 0;
	root = NULL;
	return;
}

BplusTree::BplusTree(int childSize)
		:maxChildSize(childSize)
{
	root = NULL;
	return;
}

BplusTree::~BplusTree(){
	return;
}

RC BplusTree::create(int childSize){
	maxChildSize = childSize;
	root = new BplusNode(maxChildSize);
	return SUCCESS;
}

RC BplusTree::insert(ValType data){
	BplusNode* iter = root;

	return -1;
}

RC BplusTree::search(ValType data){
	BplusNode* iter = root;

	return -1;
}

RC BplusTree::printTreeMethod(){
	std::cout<<"Bplus tree class is used!"<<std::endl;
	return SUCCESS;
}

bool BplusTree::isEmptyTree(){
	return root == NULL || root->getDatasSize() == 0;
}

void BplusTree::freeTree(BplusNode* root){
	// TODO: postpone if really need this
	return;
}
