#ifndef _TEST_UTIL_
#define _TEST_UTIL_

typedef int RC;

typedef unsigned int KeyType;
typedef unsigned int ValType;

#define MAXNUMITEM 65536

// for non-return usage
#define SUCCESS 0

#define SAMPLE_PERIOD 300

RC genDistinctKeys(KeyType*, unsigned int);
RC genSkewedKeys(KeyType*, unsigned int);

#endif
