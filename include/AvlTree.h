#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <iostream>
#include <cassert>
#include <vector>
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
	private:
		RC rotate_left(std::vector< BinaryNode* >&, BinaryNode*);
		RC rotate_right(std::vector< BinaryNode* >&, BinaryNode*);
		int getHeight(BinaryNode*);
};
#endif
