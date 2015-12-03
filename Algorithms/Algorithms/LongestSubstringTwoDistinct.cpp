#include "Algorithms.h"
/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.
TestCase:
""
"aaaa"
"a"
"cabbcaaacbabb"
*/
int LongestSubstringTwoDistinct::lengthOfLongestSubstringTwoDistinct(string s) {

	int sLen = s.length();
	if (sLen <= 2) return sLen;
	unordered_map<char, int> dup;
	dup[s[0]] ++;
	dup[s[1]] ++;
	int length = 0, p1 = 0, p2 = 2;
	while (p2 < sLen) {

		dup[s[p2]] ++;
		while (dup.size() > 2) {
			dup[s[p1]] --;
			if (dup[s[p1]] == 0)
				dup.erase(s[p1]);
			p1++;
		}
		length = max(length, p2 - p1 + 1);
		p2++;
	}
	return length;
}