#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include "linkedList.h"
#include "exception.h"
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
	int count;
public:
	disjointSet(vector<T>);
	disjointSet() {};
	void makeSet(T);
	T find(T);
	bool contain(T);
	void unionSet(T set1, T set2);
	int size();
};

class parseStringToTree {
	TreeNode* parseTree(string input, int& idx);
public:
	TreeNode* parseTree(string input);
};

class BigInt {
	string number;
public:
	BigInt(string number);
	string add(string otherNum);
	// string multiply(string otherNum);
};
////////////////////////////////////////////////////////////////////////
//LeetCode Practice
////////////////////////////////////////////////////////////////////////

class filpGame {
	bool canWinDfs(string& s, unordered_map<string, bool>& record);
public:
	vector<string> generatePossibleNextMoves(string s);
	bool canWin(string s);
};

class wordPattern {
	bool dfs(string& pattern, string& str,
		unordered_map<string, int>& s2i,
		unordered_map<char, int>& c2i,
		unordered_map<char, int>& c2Len, int cIdx, int sIdx);
public:
	bool wordPatternMatch(string pattern, string str);
};

class LongestSubstringTwoDistinct {
public:
	int lengthOfLongestSubstringTwoDistinct(string s);
};

class numIslands {
	disjointSet<int> ds;
	int index(int x, int y, int n, int m);	
public:
	int add(int x, int y, int n, int m);
	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions);
};

class StrobogrammaticNumber {
	string l, h;
	int minus(string n1, string n2);
	void numDfs(int& count, string instance, int max);
public:
	int strobogrammaticInRange(string low, string high);
};
#endif ALGORITHMS_H