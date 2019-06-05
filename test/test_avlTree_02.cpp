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
#include "AvlTree.h"

using namespace std;

int main(){
	AvlTree* avlPtr = new AvlTree();
	avlPtr->printTreeMethod();

	/*
		Generate distinct keys.
	*/
	unsigned int valSize = MODPRIME * 0.8;
	ValType* vals = new ValType[valSize];

	genDistinctKeys(vals, valSize);

	/*
		Initialize hash and insert keys
	*/
	avlPtr->create();

	/*
		Begin meassuring performance
	*/
	auto start = chrono::high_resolution_clock::now();

	long long *msecInsert = new long long[(valSize/SAMPLE_PERIOD) + 1];
	long long *msecSearch = new long long[(valSize/SAMPLE_PERIOD) + 1];
	msecSearch[0] = 0;


	for(unsigned int idx=0; idx < valSize; idx++){
		if(avlPtr->insert(vals[idx]) != SUCCESS){
			assert(false);
		}
		if((idx % SAMPLE_PERIOD) == 0){
			// Calcualte execution time of insert
			auto elapsed = chrono::high_resolution_clock::now() - start;
			msecInsert[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();
			if(idx > 0){
				start = chrono::high_resolution_clock::now();
				for(unsigned iidx=idx-SAMPLE_PERIOD; iidx < idx; iidx++){
					if(avlPtr->search(vals[iidx]) != SUCCESS){
						assert(false);
					}
				}
				elapsed = chrono::high_resolution_clock::now() - start;
				msecSearch[idx/SAMPLE_PERIOD] = chrono::duration_cast<chrono::microseconds>(elapsed).count();

				start = chrono::high_resolution_clock::now();
			}
		}
	}
	/*
		Dump into result file.
	*/
	fstream fs;
	fs.open("result/avl_tree_uniform_insert_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < valSize/SAMPLE_PERIOD; idx++){
		fs << idx*SAMPLE_PERIOD << " " << msecInsert[idx] << endl;
	}
	fs.close();
	cout<<"Finish avl tree insertion "<<valSize <<" elements"<<endl;

	fs.open("result/avl_tree_uniform_search_timestamp.txt", fstream::out);
	for(unsigned int idx=0; idx < valSize/SAMPLE_PERIOD; idx++){
		fs << idx*SAMPLE_PERIOD << " " << msecSearch[idx] << endl;
	}
	fs.close();

	cout<<"Finish avl tree insertion "<<valSize <<" elements"<<endl;
	vector<ValType> shuffledKeys_v(vals, vals+valSize);
	random_shuffle(shuffledKeys_v.begin(), shuffledKeys_v.end());

	ValType* shuffledKeys = new ValType[valSize];
	for(unsigned int idx=0; idx < valSize; idx++){
		shuffledKeys[idx] = shuffledKeys_v[idx];
	}
	
	start = chrono::high_resolution_clock::now();

	delete [] vals;
	delete [] shuffledKeys;
	return 0;
}
