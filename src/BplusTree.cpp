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
	BplusNode* n_iter;
	std::vector<BplusNode*> visitedNodes;
	RC status;

	while(iter != NULL){
		// reach leaf
		status = iter->findData(data, n_iter);
		if(status == SUCCESS){
			printf("We don't expect to insert duplicated datas!\n");
			return -1;
		}

		visitedNodes.push_back(iter);

		if(n_iter != NULL){
			iter = n_iter;
		}
	}

	// iter is at leaf page
	if(iter->insertData(data) != SUCCESS){
		return -1;
	}

	if(iter->getDatasSize() == maxChildSize){
		// split nodes and upwards

	}

	return SUCCESS;
}

RC BplusTree::search(ValType data){
	BplusNode* iter = root;
	BplusNode* n_iter;
	RC status;

	while(iter != NULL){
		status = iter->findData(data, n_iter);
		if(status == SUCCESS){
			return SUCCESS;
		}
		if(n_iter == NULL){
			return -1;
		}
		iter = n_iter;
	}
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
