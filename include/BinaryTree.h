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
		RC insert(ValType);
		RC search(ValType);
		RC printTreeMethod();
		bool isEmptyTree();
		void freeTree(BinaryNode*);
	private:
		BinaryNode* root;
		unsigned int treeSize;
};
#endif
