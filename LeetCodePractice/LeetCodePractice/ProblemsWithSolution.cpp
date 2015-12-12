#include "LeetCode.h"
#include "dataStructure.cpp"

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

/*

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -,
you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move
and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.
For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.

T(N) = T(N-2) + T(N-3) + [T(2) + T(N-4)] + [T(3) + T(N-5)] + ...
[T(N-5) + T(3)] + [T(N-4) + T(2)] + T(N-3) + T(N-2)
= 2 * sum(T[i])  (i = 3..N-2)
T(N) = 2^(N-1) satisfies the above equation.

*/
/*
Explanation: for 10:"++++++++++" there is a solution "++++--++++", for all branches of this solution:
"--++--++++"(T),"+--+--++++"(T),"++----++++"(T), all return true. so "++++--++++" returns false. in the top of the recursive function tree, "++++++++++" returns true, jump out of the for loop, we are good.
Construct the strategy tree, "++++++++++", we choose "++++--++++", no matter what position the second player choose in next step. we have a way to win, so we are guaranteed to be the winner.
*/
bool filpGame::canWin(string s) {
	unordered_map<string, bool> record;
	return canWinDfs(s, record);
}
bool filpGame::canWinDfs(string& s, unordered_map<string, bool>& record) {
	if (record.count(s) > 0)
		return record[s];
	bool wins = false;
	for (int i = 1; i < s.length(); i++) {
		if (s[i] == '+' && s[i - 1] == '+') {

			s[i] = s[i - 1] = '-';
			wins = !canWinDfs(s, record);
			record[s] = !wins;
			s[i] = s[i - 1] = '+';

			if (wins)
				return true;
		}
	}
	return wins;
}

vector<string> filpGame::generatePossibleNextMoves(string s) {
	vector<string> res;
	int upper = s.length() - 1;
	for (int i = 0; i < upper; i++) {
		if (s[i] == '+' && s[i + 1] == '+') {
			s[i] = s[i + 1] = '-';
			res.push_back(s);
			s[i] = s[i + 1] = '+';
		}
	}
	return res;
}


/*

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0

We return the result as an array: [1, 1, 2, 3]


*/
// all indexes are >= 1
int numIslands::index(int x, int y, int n, int m) {
	if (0 <= x && x < m && 0 <= y && y < n) {
		int idx = x * n + y + 1;
		return idx;
	}
	return 0;
}
int numIslands::add(int x, int y, int n, int m) {
	int idx = index(x, y, n, m);
	ds.makeSet(idx);
	return idx;
}
vector<int> numIslands::numIslands2(int m, int n, vector<pair<int, int>>& positions) {
	vector<vector<int>> neighbors = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	vector<int> res;
	for (auto p : positions) {
		int x = p.first, y = p.second;
		int idx = add(p.first, p.second, n, m);

		for (auto nghb : neighbors) {
			int xn = x + nghb[0], yn = y + nghb[1];
			int idxNeighbor = index(xn, yn, n, m);
			if (!ds.contain(idxNeighbor))  // all nodes in ds are >= 1
				continue;

			ds.unionSet(idx, idxNeighbor);
		}
		res.push_back(ds.size());
	}
	return res;
}

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

/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string.

*/

int StrobogrammaticNumber::minus(string n1, string n2) {
	int len1 = n1.length(), len2 = n2.length();
	if (len1 > len2)
		return 1;
	else if (len1 < len2)
		return -1;

	for (int i = 0; i < len1; i++) {
		if (n1[i] > n2[i])
			return 1;
		else if (n1[i] < n2[i])
			return -1;
	}
	return 0;
}
void StrobogrammaticNumber::numDfs(int& count, string instance, int max) {
	if (instance.length() == max) {
		if (minus(instance, l) >= 0 && minus(h, instance) >= 0)
			count++;
		return;
	}
	if (instance.length() > max) {
		return;
	}
	if (instance.length() == 0) {
		vector<string> start = { "0", "1", "8" };
		for (auto s : start)
			numDfs(count, s, max);
	}
	if (instance.length() < max - 2)
		numDfs(count, "0" + instance + "0", max);
	numDfs(count, "1" + instance + "1", max);
	numDfs(count, "8" + instance + "8", max);
	numDfs(count, "6" + instance + "9", max);
	numDfs(count, "9" + instance + "6", max);
}

int StrobogrammaticNumber::strobogrammaticInRange(string low, string high) {
	l = low;
	h = high;
	int lowLen = low.length(), highLen = high.length();
	int count = 0;
	for (int i = lowLen; i <= highLen; i++) {
		numDfs(count, "", i);
	}
	return count;
}



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



/*
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

1. The read function will only be called once for each test case.
2. The read function may be called multiple times.

////////////////////////////////////////////////////////////////////////
//1.  The read function will only be called once for each test case.
////////////////////////////////////////////////////////////////////////


/**
* @param buf Destination buffer
* @param n   Maximum number of characters to read
* @return    The number of characters read
*/

/*
testCase:
"ab",1 => min(res, n);  "",0 => TLE, add batch break;
*/

/*

// Forward declaration of the read4 API.

int read4(char *buf);
int read(char *buf, int n) {
int res = 0, batch = 0;
while (res < n) {
batch = read4(buf + res);
res += batch;
if (batch == 0)
break;
}
return min(res, n);
}

*/

////////////////////////////////////////////////////////////////////////
//2. The read function may be called multiple times.
////////////////////////////////////////////////////////////////////////

// TODO: Forward declaration of the read4 API.
int read4(char *buf)
{
	return 0;
}

class Solution {
	char *buffer4;
	int buf4Ptr, buf4Len;
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	Solution() {
		buffer4 = new char[4];
		buf4Ptr = buf4Len = 4;
	}
	int read(char *buf, int n) {
		int ptr = 0;
		while (ptr < n) {
			// only when buf4Ptr is 0, we read new data, which means buf4Ptr 
			// is changed from 4 to 0 or initialized. buffer4 is consumed by buf.
			if (buf4Ptr == 0)
				buf4Len = read4(buffer4);
			// read nothing.
			if (buf4Len == 0)
				break;
			// consume one whole buffer4 or part of buffer4. 
			while (ptr < n && buf4Ptr < buf4Len)
				buf[ptr++] = buffer4[buf4Ptr++];
			if (buf4Ptr == buf4Len)
				buf4Ptr = 0;
		}
		return ptr;
	}
};