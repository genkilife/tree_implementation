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
	if(iter->insertData(data) >= maxChildSize){
		return -1;
	}


	// check merge
	iter = visitedNodes.back();
	visitedNodes.pop_back();

	// split nodes and move upwards
	while(iter->getDatasSize() == maxChildSize){
		// split node and promte
		// pick up the pivot data
		unsigned int pivotIndex = maxChildSize/2;
		ValType pivotData = iter->getData(pivotIndex);

		// this is root
		if(visitedNodes.size()==0){
			BplusNode* oldRoot = root;
			// put pick up data onto the node
			root = new BplusNode(maxChildSize);
			root->insertData(pivotData);
			root->setChildPtr(0, oldRoot);

			// create siblings and copy data into other sibling(right)
			root->newChildPtr(1);
			BplusNode* sibling = root->getChildPtr(1);
			for(unsigned int i=pivotIndex+1; i < maxChildSize; i++){
				sibling->insertData(oldRoot->getData(i));
			}
			for(unsigned int i=pivotIndex+1; i <= maxChildSize; i++){
				sibling->setChildPtr(i-pivotIndex-1, oldRoot->getChild(i));
			}

			// recude left node size
			oldRoot->resizeNode(pivotIndex);

		} else{
			// push key into upper layer
			BplusNode* parent = visitedNodes.back();

			unsigned int parIndex = parent->insertData(pivotData);
			if(parIndex >= maxChildSize){
				return -1;
			}

			parent->newChildPtr(parIndex+1);
			BplusNode* sibling = parent->getChildPtr(parIndex+1);

			for(unsigned int i=pivotIndex+1; i < maxChildSize; i++){
				sibling->insertData(iter->getData(i));
			}
			for(unsigned int i=pivotIndex+1; i <= maxChildSize; i++){
				sibling->setChildPtr(i-pivotIndex-1, iter->getChild(i));
			}

			// recude left node size
			iter->resizeNode(pivotIndex);
		}

		// TODO: check active later
		iter = visitedNodes.back();
		visitedNodes.pop_back();
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
