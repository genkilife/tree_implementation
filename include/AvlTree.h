#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BinaryTree.h"

class AvlTree: public BinaryTree{
	public:
		AvlTree();
		AvlTree(ValType);
		~AvlTree();
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
