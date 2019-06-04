#include "BinaryTree.h"

BinaryTree::BinaryTree(){
}

BinaryTree::~BinaryTree(){
}

RC BinaryTree::create(){
	return SUCCESS;
}

RC BinaryTree::insert(KeyType key, ValType val){
	return SUCCESS;
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
