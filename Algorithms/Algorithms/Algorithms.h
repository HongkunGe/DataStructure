#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class allSubstr {

	void getSortedSubstr(vector<string>& res, string);
	int longestCommonPrefix(string, string);
public:
	vector<string> getAllSubstr(string);
	int sizeOfSubstr(string);
};



#endif ALGORITHMS_H