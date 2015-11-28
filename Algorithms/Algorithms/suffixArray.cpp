#include "Algorithms.h"



void allSubstr::getSortedSubstr(vector<string>& res, string word) {
	for (int i = 0; i < word.size(); i++) {
		string suffix = word.substr(i, word.size() - i);
		res.push_back(suffix);
	}
	sort(res.begin(), res.end());
}

int allSubstr::longestCommonPrefix(string word1, string word2) {
	int l = 0, minLen = min(word1.length(), word2.length());

	while (l < minLen) {
		if (word1[l] == word2[l])
			l++;
		else
			break;
	}

	return l;
}

/* Get the number of distinct substring of input word*/
int allSubstr::sizeOfSubstr(string word) {

	if (word.empty())
		return 0;
	// generate sorted suffixes vector of given word albetically.
	vector<string> suffixes;
	getSortedSubstr(suffixes, word);

	int total = suffixes[0].length();
	for (int i = 1; i < suffixes.size(); i++) {
		int LCP = longestCommonPrefix(suffixes[i], suffixes[i - 1]);
		total += (suffixes[i].length() - LCP);
	}

	return total;
}

/* TODO: Generate all distinct substring of input word*/
vector<string> allSubstr::getAllSubstr(string word) {
	vector<string> res;
	return res;
}
