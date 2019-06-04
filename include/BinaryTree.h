#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BasicTree.h"

class BinaryTree: public BasicTree{
	public:
		BinaryTree();
		~BinaryTree();
	// hash function
	public:
		RC create();
		RC insert(KeyType, ValType);
		RC search(KeyType);
		RC printTreeMethod();
		bool isEmptyTree();
	private:
		BinaryNode* root;
		unsigned int treeSize;
};
#endif
