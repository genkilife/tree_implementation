#include "AvlTree.h"

AvlTree::AvlTree()
		:BinaryTree()
{
}

AvlTree::~AvlTree()
{
	this->~BinaryTree();
}

RC AvlTree::insert(ValType data){
	BinaryNode* iter = root;
	std::vector< BinaryNode* > visitedNodes;

	// if it is empty tree
	if(iter == NULL){
		root = new BinaryNode();
		root->data = data;
		return SUCCESS;
	}

	while(iter != NULL){
		visitedNodes.push_back(iter);

		if(iter->data == data){
			printf("Error: insert existing val\n");
			return -1;
		}
		if(data < iter->data){
			if(iter->left == NULL){
				iter->left = new BinaryNode(data);
				break;
			}
			else{
				iter = iter->left;
			}
		}else{
			if(iter->right == NULL){
				iter->right = new BinaryNode(data);
				break;
			}
			else{
				iter = iter->right;
			}
		}
	}

	// Balance
	while(visitedNodes.size()!=0){
		BinaryNode* cur = visitedNodes.back();	
		visitedNodes.pop_back();

		int left_height = (cur->left == NULL) ? 0 : cur->left->height;
		int right_height = (cur->right == NULL) ? 0 : cur->right->height;

		if((left_height-right_height)>=2){
			if(rotate_right(visitedNodes, cur) != SUCCESS){
				return -1;
			}
		}
		else if((right_height-left_height)>=2){
			if(rotate_left(visitedNodes, cur) != SUCCESS){
				return -1;
			}
		}
	}

	return SUCCESS;
}

RC AvlTree::printTreeMethod(){
	std::cout<<"Avl tree class is used!"<<std::endl;
	return SUCCESS;
}

RC AvlTree::rotate_left(std::vector< BinaryNode* >& visitedNodes, BinaryNode* cur){
	// Select subtree
	BinaryNode* A, *B;
	A = cur;
	B = cur->right;

	A->right = B->left;
	A->height = getHeight(A);
	// update height on A

	B->left = A;
	B->height = getHeight(B);

	if(visitedNodes.size()!=0){
		BinaryNode* par = visitedNodes.back();
		if(par->left == A){
			par->left = B;
		}else if (par->right == A){
			par->right = B;
		} else{
			return -1;
		}
	}
	else{
		root = B;
	}
	return SUCCESS;
}

RC AvlTree::rotate_right(std::vector< BinaryNode* >& visitedNodes, BinaryNode* cur){
	// Select subtree
	BinaryNode *B, *C;
	B = cur->left;
	C = cur;

	C->left = B->right;
	C->height = getHeight(C);
	// update height on A

	B->right = C;
	B->height = getHeight(B);

	if(visitedNodes.size()!=0){
		BinaryNode* par = visitedNodes.back();
		if(par->left == C){
			par->left = B;
		}else if (par->right == C){
			par->right = B;
		} else{
			return -1;
		}
	}
	else{
		root = B;
	}
	return SUCCESS;
}

int AvlTree::getHeight(BinaryNode* cur){
	int left_height = (cur->left == NULL) ? 0 : cur->left->height+1;
	int right_height = (cur->right == NULL) ? 0 : cur->right->height+1;
	if(left_height > right_height){
		return left_height;
	} else{
		return right_height;
	}
}
