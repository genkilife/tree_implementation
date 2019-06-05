#ifndef _BPLUSNODE_H_
#define _BPLUSNODE_H_

#include <iostream>
#include <vector>
#include "test_util.h"

class BplusNode{
	public:
		BplusNode();
		BplusNode(unsigned int maxDataSize);

		~BplusNode();

		std::vector< ValType > datas;
		std::vector< BplusNode* > childPtrs;

		RC findData(ValType, BplusNode* &);
		int getDatasSize();
		int getChildPtrsSize();

		ValType getData(unsigned int);

		RC insertData(ValType);

		unsigned int maxDataSize;
};

#endif
