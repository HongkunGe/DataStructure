#include "Algorithms.h"
/*

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
"wrt",
"wrf",
"er",
"ett",
"rftt"
]

The correct order is: "wertf".

Note:

You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.


*/
/*

testCase: ["z", "z"](exactly the same words in the dict) => "z"
["wrt","wrf","er","ett","rftt"] => "wertf"
["wrt","wrf","er","ett","wftt"] => "" (circle)

*/
string alienDict::alienOrder(vector<string>& words) {
	// TOPOLOGICAL SORT
	vector<vector<int>> adj(128, vector<int>());
	unordered_map<char, int> degree;

	for (auto word : words)
		for (auto c : word)
			degree[c] = 0;

	// adjcency table and in degree.
	for (int i = 1; i < words.size(); i++) {
		int minLen = min(words[i].length(), words[i - 1].length()), j = 0;
		for (; j < minLen; j++) {
			if (words[i][j] != words[i - 1][j])
				break;
		}
		// if there are two exactly same words => j == minLen
		if (j < minLen) {
			adj[words[i - 1][j]].push_back(words[i][j]);
			degree[words[i][j]] ++;
		}
	}

	queue<int> q;
	string res;
	for (int i = 'a'; i <= 'z'; i++) {
		if (degree.count(i) > 0 && degree[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		res += cur;
		for (auto n : adj[cur]) {
			degree[n] --;
			if (degree[n] == 0)
				q.push(n);
		}
	}

	// circle return empty string.
	if (res.length() != degree.size()) return "";
	return res;
}