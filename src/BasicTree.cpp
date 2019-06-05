#include "BasicTree.h"

BasicTree::BasicTree(){
}

BasicTree::~BasicTree(){
}

RC BasicTree::create(){
	return SUCCESS;
}

RC BasicTree::insert(ValType val){
	return SUCCESS;
}

RC BasicTree::search(KeyType key){
	return SUCCESS;
}

RC BasicTree::printTreeMethod(){
	std::cout<<"Basic tree class is used!"<<std::endl;
	return SUCCESS;
}

bool BasicTree::isEmptyTree(){
	return true;
}
