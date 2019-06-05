#ifndef _BPLUS_TREE_H_
#define _BPLUS_TREE_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BplusNode.h"
#include "BasicTree.h"

class BplusTree: public BasicTree{
	public:
		BplusTree();
		BplusTree(int);
		~BplusTree();
	// hash function
	public:
		RC create(int);
		RC insert(ValType);
		RC search(ValType);
		RC printTreeMethod();
		bool isEmptyTree();
		void freeTree(BplusNode*);
	protected:
		BplusNode* root;
		unsigned int maxChildSize;
};
#endif
