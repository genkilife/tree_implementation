#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include "test_util.h"

class BinaryNode(){
	public:
		BinaryNode();
		BinaryNode(ValType);
		~BinaryNode();
	private:
		BinaryNode *left, *right;
		ValType data;
};

#endif
