#pragma once
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H


#include <iostream>
#include <bitset>
#include <vector>
#include <time.h>
#include <string>
#include <set>
#include "murmurHash2.h"

#define MAX_HASHES 8
#define MAX_BITSET_LENGTH 32
using namespace std;

class BloomFilter {
	int nHashFunc;
	int nItem;
	int bitVecLength;
	
	unsigned int bitVec;
	vector<unsigned int> seedsForHash;

	set<string> store;
public:
	BloomFilter(int nItemNum, int bitsetLength, int kHashFunc);
	void add(string s);
	bool contains(string s);
	bool containsCheck(string s);
};


#endif BLOOMFILTER_H