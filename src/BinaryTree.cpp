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
		root = new BinaryNode();
		root->data = data;
		return SUCCESS;
	}

	while(iter != NULL){
		if(iter->data == data){
			printf("Error: insert existing val\n");
			return -1;
		}
		if(data < iter->data){
			if(iter->left == NULL){
				iter->left = new BinaryNode(data);
				return SUCCESS;
			}
			else{
				iter = iter->left;
			}
		}else{
			if(iter->right == NULL){
				iter->right = new BinaryNode(data);
				return SUCCESS;
			}
			else{
				iter = iter->right;
			}
		}
	}
	return -1;
}

RC BinaryTree::search(ValType data){
	BinaryNode* iter = root;

	// if it is empty tree
	while(iter != NULL){
		if(iter->data == data){
			return SUCCESS;
		}
		if(data < iter->data){
			iter = iter->left;
		}else{
			iter = iter->right;
		}
	}

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
