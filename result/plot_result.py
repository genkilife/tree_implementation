import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
import glob
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

offset = 10

keySize = 32749.0

def dump_performance(filename):
	plt.cla()
	with open(filename[1]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		binaryXasis = [x[0] for x in data[offset:]]
		binaryYasis = [x[1] for x in data[offset:]]
	with open(filename[2]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		avlXasis = [x[0] for x in data[offset:]]
		avlYasis = [x[1] for x in data[offset:]]
	with open(filename[3]) as f:
		data = [x.split(' ',1) for x in f.read().splitlines()]
		bplusXasis = [x[0] for x in data[offset:]]
		bplusYasis = [x[1] for x in data[offset:]]
	
	plt.ylabel('Time per 500 operation(ms)')
	plt.xlabel('loading factor')
	plt.plot(binaryXasis, binaryYasis, '-', color='red')
	plt.plot(avlXasis, avlYasis, '-', color='green')
	plt.plot(bplusXasis, bplusYasis, '-', color='#ff7f0eff')
	plt.legend(['Bianry tree', 'AVL tree', 'B-plus tree'], loc='upper left')
	plt.savefig(filename[0])

uniform_insert = ['uniform_insert.png',
                  'binary_tree_uniform_insert_timestamp.txt',
                  'avl_tree_uniform_insert_timestamp.txt',
                  'bplus_tree_uniform_insert_timestamp.txt']

dump_performance(uniform_insert)

uniform_search = ['uniform_search.png',
                  'binary_tree_uniform_search_timestamp.txt',
                  'avl_tree_uniform_search_timestamp.txt',
                  'bplus_tree_uniform_search_timestamp.txt']

dump_performance(uniform_search)

skewed_insert = [ 'skewed_insert.png',
                  'binary_tree_skewed_insert_timestamp.txt',
                  'avl_tree_skewed_insert_timestamp.txt',
                  'bplus_tree_skewed_insert_timestamp.txt']

dump_performance(skewed_insert)

skewed_search = [ 'skewed_search.png',
                  'binary_tree_skewed_search_timestamp.txt',
                  'avl_tree_skewed_search_timestamp.txt',
                  'bplus_tree_skewed_search_timestamp.txt']

dump_performance(skewed_search)
