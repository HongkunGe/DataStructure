#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

class allSubstr {

	void getSortedSubstr(vector<string>& res, string);
	int longestCommonPrefix(string, string);
public:
	vector<string> getAllSubstr(string);
	int sizeOfSubstr(string);
};

class alienDict {
public:
	string alienOrder(vector<string>& words);
};

template<class T>
class disjointSet {
	unordered_map<T, T> parent;
	unordered_map<T, int> rank;  // record the depth of the set
public:
	disjointSet(vector<T>);
	disjointSet() {};
	void makeSet(T);
	T find(T);
	void unionSet(T set1, T set2);
};

#endif ALGORITHMS_H