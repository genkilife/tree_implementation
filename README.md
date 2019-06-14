
# Problem scope
Based on the project requirement, I implemented following trees in C++:
* Binary tree
* AVL tree
* B+ tree
I choose B+ tree because it is commonly used in latest database system and I want to investigate how good it is.

# Code structure
.
├── bin  -> compiled binary file
├── include -> header definition files
├── makefile -> makefile to compile project
├── makefile.inc -> included variables
├── obj -> intermediate compiled object files
├── README.md -> explanation of the project
├── result -> Collect experiment data
├── src -> hash function core source code
├── test -> test patterns to evaluate performance

# Experiment step
```makefile
cd $PROJECT_ROOT
module load gcc/5.4.0
make clean
make all
make run
```
******
# Benchmark & Experiment
To create the test cases, I design 2 different test cases. One test is fully random test case and the another is the skewed data test case.

I use C++ rand() function to generate random number and create a set of random number without duplication. Because C++ random function will output a 32bit number, I can directly take the output number and save it as a integer data type.

The other test case is to generate sequential data from 1 to a given upper bound. We can insert the data into different trees and compare the performance difference between different trees.

When we run the test case, we setup a sample period of 500 key insertion. Every 500 key insertion, the test cases will invoke search method and call 500 times of key search. We collect the performance of each block of insertion and search.
******
# Tree implementation

``` C++
########################
## Binary tree method ##
########################
// We set up a iterator which begins at root node.
// Iterator keeps compare the data with the current node's data
// If data doesn't match, then it moves into next layer.
// We reach the bottom and insert the data on leaf node.
// The expected time complexity is O(log h)
// when the data is uniformly inserted into the tree.
// The worst time complexity is O(n)
// when data is severely skewed (ex: only has left children)
RC BinaryTree::insert(ValType data){
    BinaryNode* iter = root;

    // if it is empty tree
    if(iter == NULL){
        root = new BinaryNode();
        root->data = data;
        return SUCCESS;
    }   

    while(iter != NULL){
        if(iter->data == data){
            printf("Error: insert existing val\n");
            return -1;
        }   
        if(data < iter->data){
            if(iter->left == NULL){
                iter->left = new BinaryNode(data);
                return SUCCESS;
            }   
            else{
                iter = iter->left;
            }   
        }else{
            if(iter->right == NULL){
                iter->right = new BinaryNode(data);
                return SUCCESS;
            }   
            else{
                iter = iter->right;
            }   
        }   
    }   
    return -1;
}
// Search is similar to insert but it doesn't add new data into the tree.
// Time complexity is the same as insert.
// The expected time complexity is O(log h)
// when the data is uniformly inserted into the tree.
// The worst time complexity is O(n)
// when data is severely skewed (ex: only has left children)
RC BinaryTree::search(ValType data){
    BinaryNode* iter = root;

    // if it is empty tree
    while(iter != NULL){
        if(iter->data == data){
            return SUCCESS;
        }
        if(data < iter->data){
            iter = iter->left;
        }else{
            iter = iter->right;
        }
    }

    return -1;
}

```


``` C++
#####################
## AVL tree method ##
#####################

// Insert function is the same as binary tree
// but it has to do balance in the end of insert.
// Balance operation needs to traverse from the leaf node to root node
// and check whether height property holds in every intermediate node.
// If any node doesn't hold the maximum height difference property,
// we takes O(1) to rotate the tree.
// The expected time complexity is O(log h) for both search and
// rotate when the data is uniformly inserted into the tree.
// The worst time complexity is also O(log n) because
// the tree is balanced in the mid of insert operation.
RC AvlTree::insert(ValType data){
    BinaryNode* iter = root;
    std::vector< BinaryNode* > visitedNodes;

    // if it is empty tree
    if(iter == NULL){
        root = new BinaryNode();
        root->data = data;
        return SUCCESS;
    }

    while(iter != NULL){
        visitedNodes.push_back(iter);

        if(iter->data == data){
            printf("Error: insert existing val\n");
            return -1;
        }
        if(data < iter->data){
            if(iter->left == NULL){
                iter->left = new BinaryNode(data);
                break;
            }
            else{
                iter = iter->left;
            }
        }else{
            if(iter->right == NULL){
                iter->right = new BinaryNode(data);
                break;
            }
            else{
                iter = iter->right;
            }
        }
    }

    // Balance
    while(visitedNodes.size()!=0){
        BinaryNode* cur = visitedNodes.back();
        visitedNodes.pop_back();

        int left_height = (cur->left == NULL) ? 0 : cur->left->height;
        int right_height = (cur->right == NULL) ? 0 : cur->right->height;
        // If left tree is higher, then rotate right
        if((left_height-right_height)>=2){
            if(rotate_right(visitedNodes, cur) != SUCCESS){
                return -1;
            }
        }
        //If right tree is higher, then rotate left
        else if((right_height-left_height)>=2){
            if(rotate_left(visitedNodes, cur) != SUCCESS){
                return -1;
            }
        }
    }

    return SUCCESS;
}

// AVL search is the same as binary tree's search method.
// The expected time complexity is O(log h)
// when the data is uniformly inserted into the tree.
// The worst time complexity is O(n)
// when data is severely skewed. (ex: only has left children)
```


```C++
########################
## B-plus tree method ##
########################
// Inside B+ tree insert function, we first have to reach leaf node.
// Then we insert data on the leaf node.
// We then move upward from leaf node to the root.
// If we find out any node whose size is equal to the maximum node size.
// We then do split on that node by creating 2 nodes and copy half of the data
// to the new node.
// The expected and worst time complexity are both O(log h) for
// both search and split no matter whether data is uniformly distributed or skewed.
// Split operation can balance the tree structure to avoid worst skewed scenario.

RC BplusTree::insert(ValType data){
    BplusNode* iter = root;
    BplusNode* n_iter = NULL;
    std::vector<BplusNode*> visitedNodes;
    RC status;

    while(iter != NULL){
        // reach leaf
        status = iter->findData(data, n_iter);
        if(status == SUCCESS){
            printf("We don't expect to insert duplicated datas!\n");
            return -1;
        }

        visitedNodes.push_back(iter);

        if(n_iter == NULL){
            break;
        } else{
            iter = n_iter;
        }
    }

    // iter is at leaf page
    if(iter->insertData(data) >= maxChildSize){
        return -1;
    }

    // check merge
    iter = visitedNodes.back();
    visitedNodes.pop_back();

    // split nodes and move upwards
    while(iter != NULL && iter->getDatasSize() == maxChildSize){
        // split node and promte
        // pick up the pivot data
        unsigned int pivotIndex = maxChildSize/2;
        ValType pivotData = iter->getData(pivotIndex);

        // this is root
        if(visitedNodes.size()==0){
            BplusNode* oldRoot = root;
            // put pick up data onto the node
            root = new BplusNode(maxChildSize);
            root->insertData(pivotData);
            root->setChildPtr(0, oldRoot);

            // create siblings and copy data into other sibling(right)
            root->newChildPtr(1);
            BplusNode* sibling = root->getChildPtr(1);
            for(unsigned int i=pivotIndex+1; i < maxChildSize; i++){
                sibling->insertData(oldRoot->getData(i));
            }
            for(unsigned int i=pivotIndex+1; i <= maxChildSize; i++){
                sibling->setChildPtr(i-pivotIndex-1, oldRoot->getChild(i));
            }

            // recude left node size
            oldRoot->resizeNode(pivotIndex);
            break;
        } else{
            // push key into upper layer
            BplusNode* parent = visitedNodes.back();

            unsigned int parIndex = parent->insertData(pivotData);
            if(parIndex >= maxChildSize){
                return -1;
            }

            parent->newChildPtr(parIndex+1);
            BplusNode* sibling = parent->getChildPtr(parIndex+1);

            for(unsigned int i=pivotIndex+1; i < maxChildSize; i++){
                sibling->insertData(iter->getData(i));
            }
            for(unsigned int i=pivotIndex+1; i <= maxChildSize; i++){
                sibling->setChildPtr(i-pivotIndex-1, iter->getChild(i));
            }

            // recude left node size
            iter->resizeNode(pivotIndex);
        }

        // TODO: check active later
        iter = visitedNodes.back();
        visitedNodes.pop_back();
    }

    return SUCCESS;
}
// Search is similar to insert but it doesn't need to add new data or split nodes.
// It searches down to the leaf and return if find matched data.
// Time complexity is the same as insert.
// The expected and worst time complexity are both O(log h).
RC BplusTree::search(ValType data){
    BplusNode* iter = root;
    BplusNode* n_iter;
    RC status;

    while(iter != NULL){
        status = iter->findData(data, n_iter);
        if(status == SUCCESS){
            return SUCCESS;
        }   
        if(n_iter == NULL){
            return -1;
        }   
        iter = n_iter;
    }   
    return -1;
}
```

# Performance result
We have test_cases_02, test_cases_03 inside tests directory. Case 02 uses random keys sequence while case 03 uses sequential data sequence to create skewed input.

We use C++ chrono library to sample the running time of the function and get the consuming time on each operation.

In test case 02, we first generate distinct random keys and insert the keys into the tree one-by-one. Every 500 insert, we would switch to search operation and collect the execution time of search. Search keys are shuffled from the inserted keys. It ensures we are always measuring random search's performance.

Test case 03 is similar to case 02 but it uses skewed input keys which is a sequential key sequence.

* Uniform Insert
![uniform_insert](/assets/uniform_insert.png)
The function of binary tree is very simple and it takes very small coefficient of O(1).
AVL tree and B+ tree takes similar time complexity because both of them need to update tree structure.
We can see all of them are increasing slowly and it matches the expected O(log h) complexity.

* Uniform Search
![uniform_insert](/assets/uniform_search.png)
B+ tree takes larger coefficient of O(1) to do search operation because it needs to traverse all of the item in the node.
AVL tree has slightly lower search time than binary tree but it is not obvious.
All of the 3 trees increase search time slowly and it matches time complexity O(log h).

* Skewed Insert
![uniform_insert](/assets/skewed_insert.png)
Time complexity of AVL and binary trees behave almost linear increasing.
I guess AVL tree is always balancing back and forth that cause it can't be idealy log(h) complexity.
B+ tree keeps relatively static insert time increase which is log(h).

* Skewed Search
![uniform_insert](/assets/skewed_search.png)
AVL tree has better performance then binary tree but it doesn't that much good.
B-plus tree doesn't increase time complexity as much as binary tree or AVL tree and keeps slightly increase.

# Conclusion
We can conclude B+ tree is very tolerant to skewed data and performance is impacted slightly in worst case.
If data is pretty random, binary tree doesn't need too much tree adjust and it runs fast because the tree's function is simple.
AVL tree structure update generates a lot of performance costs. It doesn't outperform too much in uniform or worst case then normal unadjusted binary tree.
