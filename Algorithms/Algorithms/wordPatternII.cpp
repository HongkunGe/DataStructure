#include "Algorithms.h"
/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

TestCase:

pattern = "ab", str = "aa" should return false.
pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false.
pattern = "itwasthebestoftimes", str = "ittwaastthhebesttoofttimes" true;

Notes:
You may assume both pattern and str contains only lowercase letters.

*/
// Backtrack
bool wordPattern::wordPatternMatch(string pattern, string str) {
	unordered_map<string, int> s2i;

	// c2len record the length of matching substring of char.
	unordered_map<char, int> c2i, c2Len;
	return dfs(pattern, str, s2i, c2i, c2Len, 0, 0);
}
bool wordPattern::dfs(string& pattern, string& str,
	unordered_map<string, int>& s2i,
	unordered_map<char, int>& c2i,
	unordered_map<char, int>& c2Len, int cIdx, int sIdx) {
	if (cIdx == pattern.length() && sIdx == str.length())
		return true;
	if (cIdx == pattern.length() || sIdx == str.length())
		return false;

	if (c2i.count(pattern[cIdx]) > 0) {
		int pLen = c2Len[pattern[cIdx]];
		if (pLen + sIdx > str.length())
			return false;

		string matchStr = str.substr(sIdx, pLen); //pattern = "itwasthebestoftimes", str = "ittwaastthhebesttoofttimes"
		if (s2i.count(matchStr) == 0 || s2i[matchStr] != c2i[pattern[cIdx]])
			return false;

		return dfs(pattern, str, s2i, c2i, c2Len, cIdx + 1, sIdx + pLen);
	}
	else {
		for (int i = sIdx; i < str.length(); i++) {
			string subs = str.substr(sIdx, i - sIdx + 1);
			if (s2i.count(subs) > 0)  // pattern = "ab", str = "aa"
				continue;
			c2Len[pattern[cIdx]] = i - sIdx + 1;
			s2i[subs] = c2i[pattern[cIdx]] = i + 1;
			if (dfs(pattern, str, s2i, c2i, c2Len, cIdx + 1, i + 1))
				return true;
			s2i.erase(subs);
			c2i.erase(pattern[cIdx]);
		}
	}
	return false;
}