#include "BinaryTree.h"

BinaryTree::BinaryTree(){
	root = NULL;
	treeSize=0;
	return;
}

BinaryTree::~BinaryTree(){
	freeTree(root);
	return;
}

RC BinaryTree::create(){
	root = NULL;
	treeSize=0;
	return SUCCESS;
}

RC BinaryTree::insert(ValType data){
	BinaryNode* iter = root;

	// if it is empty tree
	if(iter == NULL){
		iter = new BinaryNode();
		iter->data = data;
		return;
	}

	while(iter != NULL){
		if(iter->data == val){
			printf("Error: insert existing val\n");
			return -1;
		}
		if(data < iter->data){
			if(iter->left == NULL){
				iter->left = new BinaryNode(data);
				return SUCCESS;
			}
			else{
				return insert(iter->left, data);
			}
		}else{
			if(iter->right == NULL){
				iter->right = new BinaryNode(data);
				return SUCCESS;
			}
			else{
				return insert(iter->right, data);
			}
		}
	}
	return -1;
}

RC BinaryTree::search(KeyType key){
	return -1;
}

RC BinaryTree::printTreeMethod(){
	std::cout<<"Binary tree class is used!"<<std::endl;
	return SUCCESS;
}

bool BinaryTree::isEmptyTree(){
	return true;
}

void BinaryTree::freeTree(BinaryNode* root){
	if(root != NULL){
		freeTree(root->left);
		freeTree(root->right);
		delete root;
	}
	return;
}
