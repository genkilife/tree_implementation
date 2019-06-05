#include "AvlTree.h"

AvlTree::AvlTree()
		:BinaryTree()
{
}

AvlTree::AvlTree(ValType data)
		:BinaryTree(data)
{
}

AvlTree::~AvlTree()
		:BinaryTree()
{
}

RC AvlTree::insert(ValType data){
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

RC AvlTree::printTreeMethod(){
	std::cout<<"Avl tree class is used!"<<std::endl;
	return SUCCESS;
}

