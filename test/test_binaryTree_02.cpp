/*
This test case generate large keys and insert into hash structure.
Then, delete keys from the set.
*/
#include <vector>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
#include "test_util.h"
#include "BinaryTree.h"

using namespace std;

int main(){
	BinaryTree* btPtr = new BinaryTree();
	btPtr->printTreeMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int valSize = MAXNUMITEM;
	ValType* vals = new ValType[valSize];

	genDistinctKeys(vals, valSize);

	/*
		Initialize hash and insert keys
	*/
	btPtr->create();

	/*
		Begin meassuring performance
	*/
	auto start = chrono::high_resolution_clock::now();

	long long *msecInsert = new long long[(valSize/SAMPLE_PERIOD) + 1];
	long long *msecSearch = new long long[(valSize/SAMPLE_PERIOD) + 1];
	msecSearch[0] = 0;


	for(unsigned int idx=0; idx < valSize; idx++){
		if(btPtr->insert(vals[idx]) != SUCCESS){
			assert(false);
		}
		if((idx % SAMPLE_PERIOD) == 0){
			// Calcualte execution time of insert
			auto elapsed = chrono::high_resolution_clock::now() - start;
			msecInsert[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();
			if(idx > 0){
				// shuffle the keys to create random key fetcj
				vector<ValType> shuffledKeys_v(vals, vals+idx+1);
				random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

				ValType* shuffledKeys = new ValType[valSize];
				for(unsigned int iidx=0; iidx < idx+1; iidx++){
					shuffledKeys[iidx] = shuffledKeys_v[iidx];
				}

				start = chrono::high_resolution_clock::now();
				for(unsigned iidx=0 ; iidx < SAMPLE_PERIOD; iidx++){
					if(btPtr->search(shuffledKeys[iidx]) != SUCCESS){
						assert(false);
					}
				}
				elapsed = chrono::high_resolution_clock::now() - start;
				msecSearch[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();

				delete [] shuffledKeys;
				shuffledKeys_v.clear();

				start = chrono::high_resolution_clock::now();
			}
		}
	}
	/*
		Dump into result file.
	*/
	fstream fs;
	fs.open("result/binary_tree_uniform_insert_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < valSize/SAMPLE_PERIOD; idx++){
		fs << idx*SAMPLE_PERIOD << " " << msecInsert[idx] << endl;
	}
	fs.close();
	cout<<"Finish binary tree insertion "<<valSize <<" elements"<<endl;

	fs.open("result/binary_tree_uniform_search_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < valSize/SAMPLE_PERIOD; idx++){
		fs << idx*SAMPLE_PERIOD << " " << msecSearch[idx] << endl;
	}
	fs.close();

	cout<<"Finish binary tree insertion "<<valSize <<" elements"<<endl;
	
	return 0;
}
