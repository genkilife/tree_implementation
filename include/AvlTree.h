#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <iostream>
#include <cassert>
#include "test_util.h"
#include "BinaryTree.h"

class AvlTree: public BinaryTree{
	public:
		AvlTree();
		~AvlTree();
	// hash function
	public:
		RC insert(ValType);
		RC printTreeMethod();
};
#endif
