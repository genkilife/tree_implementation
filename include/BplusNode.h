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


		RC findData(ValType, BplusNode* &);
		unsigned int getDatasSize();
		int getChildPtrsSize();

		ValType getData(unsigned int);
		BplusNode* getChild(unsigned int);

		RC resizeNode(unsigned int);

		RC newChildPtr(unsigned int);
		RC setChildPtr(unsigned int, BplusNode*);
		BplusNode* getChildPtr(unsigned int);
		RC insertData(ValType);

	protected:
		std::vector< ValType > datas;
		std::vector< BplusNode* > childPtrs;
		unsigned int maxDataSize;
};

#endif
