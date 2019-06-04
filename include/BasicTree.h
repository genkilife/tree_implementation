#ifndef _BASIC_NODE_H_
#define _BASIC_NODE_H_

#include <iostream>
#include "test_util.h"
#include "Node.h"

class BasicTree{
	public:
		BasicTree();
		~BasicTree();
	// hash function
	public:
		virtual RC create();
		virtual RC insert(KeyType, ValType);
		virtual RC search(KeyType);
		virtual RC printTreeMethod();
		virtual bool isEmptyTree();
};
#endif
