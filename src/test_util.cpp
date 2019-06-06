#include <iostream>
#include <cstdlib>
#include "test_util.h"

/*
	We have constraints:
	* Keys are not duplicated
	* Key is in range (0, 2^30-1)
	* Delete must success and key always exist
*/

RC genDistinctKeys(KeyType* keys, unsigned int keySize){
	srand(0);
	unsigned int cnt = 0;
	unsigned int idx;

	KeyType r;
	while(cnt < keySize){
		r = rand();
		// Find r in keys
		for(idx=0; idx < cnt; idx++){
			if(r == keys[idx]){
				break;
			}
		}
		if(idx == cnt){
			keys[cnt++] = r;
		}
	}

	return SUCCESS;
}

RC genSkewedKeys(KeyType* keys, unsigned int keySize){
	unsigned int cnt = 0;

	while(cnt < keySize){
		keys[cnt] = cnt;
		cnt++;
	}

	return SUCCESS;
}
