#include "LeetCode.h"
#include "dataStructure.cpp"

/*

An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
"0010",
"0110",
"0100"
]

and x = 0, y = 2,

Return 6.

*/

int minArea(vector<vector<char>>& image, int x, int y) {
	if (image.empty() || image[0].empty())
		return 0;
	int rEnd = image.size(), cEnd = image[0].size();
	int low, high;
	low = 0; high = image[0].size();
	int top = searchRow(image, low, high, 0, x, true);
	int bottom = searchRow(image, low, high, x + 1, rEnd, false);
	// use top and bottom as range for '1' searching in col.
	int left = searchCol(image, top, bottom, 0, y, true);
	int right = searchCol(image, top, bottom, y + 1, cEnd, false);
	return (bottom - top) * (right - left);
}
int searchRow(vector<vector<char>>& image, int low, int high, int rStart, int rEnd, bool topOpt) {
	while (rStart < rEnd) {
		int mid = rStart + (rEnd - rStart) / 2;
		int k = low;
		while (k < high && image[mid][k] == '0') k++;
		bool foundAtMid = (k < high);
		if (foundAtMid == topOpt) {
			rEnd = mid;
		}
		else {
			rStart = mid + 1;
		}
	}
	return rStart;
}
int searchCol(vector<vector<char>>& image, int low, int high, int cStart, int cEnd, bool leftOpt) {
	while (cStart < cEnd) {
		int mid = cStart + (cEnd - cStart) / 2;
		int k = low;
		while (k < high && image[k][mid] == '0') k++;
		bool foundAtMid = (k < high);
		if (foundAtMid == leftOpt) {
			cEnd = mid;
		}
		else {
			cStart = mid + 1;
		}
	}
	return cStart;
}

/*

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
[ 1, 0, 0],
[-1, 0, 3]
]

B = [
[ 7, 0, 0 ],
[ 0, 0, 0 ],
[ 0, 0, 1 ]
]


	 |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
	 |  0 0 1 |


*/

vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
	vector<vector<int>> res;
	if (A.empty() || B.empty())
		return res;

	int colA = A[0].size(), rowB = B.size();
	if (colA != rowB)
		return res;

	res = vector<vector<int>>(A.size(), vector<int>(B[0].size(), 0));
	vector<vector< pair<int, int> > > a, b;
	for (int i = 0; i < A.size(); i++) {
		vector< pair<int, int> > row;
		for (int j = 0; j < colA; j++) {
			if (A[i][j] != 0) {
				row.push_back(make_pair(j, A[i][j]));
			}
		}
		a.push_back(row);
	}

	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++) {
			for (int k = 0; k < a[i].size(); k++) {
				int AcolIdx = a[i][k].first;
				res[i][j] += a[i][k].second * B[AcolIdx][j];
			}
		}
	}
	return res;
}

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


/*
Given two strings S and T, determine if they are both one edit distance apart.
testCase:
"A""a"; "ba""a"; "ab""a"; "" "a"
*/
bool isOneEditDistance(string s, string t) {
	int len = min(s.length(), t.length());

	for (int i = 0; i < len; i++) {
		if (s[i] != t[i]) {
			if (s.length() > t.length()) {
				return s.substr(i + 1) == (t.substr(i));
			}
			else if (s.length() < t.length()) {
				return t.substr(i + 1) == (s.substr(i));
			}
			else {
				return s.substr(i + 1) == t.substr(i + 1);
			}
		}
	}
	int diff = s.length() - t.length();
	return diff == 1 || diff == -1;
}

/*
Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
testCase: [0,1,98,99],0,99; [0],0,99;
[] 0,0; []0,9;
[0, 100, 200] -2, 202;[0, 100, 200] 10, 202
[0, 100, 200] -1, 201;
*/
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
	vector<string> res;
	nums.insert(nums.begin(), lower - 1);
	nums.push_back(upper + 1);
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] - nums[i - 1] > 2) {
			res.push_back(to_string(nums[i - 1] + 1) + "->" + to_string(nums[i] - 1));
		}
		else if (nums[i] - nums[i - 1] == 2) {
			res.push_back(to_string(nums[i] - 1));
		}
	}
	return res;
}
vector<string> findMissingRanges2(vector<int>& nums, int lower, int upper) {
	vector<string> res;
	if (nums.empty()) {  // [] 0,0; []0,9;
		if (lower == upper) {
			res.push_back(to_string(lower));
		}
		else {
			res.push_back(to_string(lower) + "->" + to_string(upper));
		}
		return res;
	}

	if (nums[0] - lower >= 2) { // [0, 100, 200] -2, 202;[0, 100, 200] 10, 202
		res.push_back(to_string(lower) + "->" + to_string(nums[0] - 1));
	}
	else if (nums[0] - lower == 1) {
		res.push_back(to_string(lower)); // [-99, 25, 199] -100, 200
	}
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] - nums[i - 1] > 2) {
			res.push_back(to_string(nums[i - 1] + 1) + "->" + to_string(nums[i] - 1));
		}
		else if (nums[i] - nums[i - 1] == 2) {
			res.push_back(to_string(nums[i] - 1));
		}
	}
	if (upper - nums.back() >= 2) {
		res.push_back(to_string(nums.back() + 1) + "->" + to_string(upper));
	}
	else if (upper - nums.back() == 1) {
		res.push_back(to_string(upper));
	}
	return res;
}

/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.

*/
int minDistance(vector<int>& points) {
	int i = 0, j = points.size() - 1, sum = 0;
	while (i < j)
		sum += points[j--] - points[i++];
	return sum;
}
int minTotalDistance(vector<vector<int>>& grid) {
	if (grid.empty())
		return 0;
	int row = grid.size(), col = grid[0].size();
	// two separate dimensions.
	vector<int> rows, cols;

	for (int r = 0; r < row; r++)
		for (int c = 0; c < col; c++)
			if (grid[r][c] == 1)
				rows.push_back(r);

	for (int c = 0; c < col; c++)
		for (int r = 0; r < row; r++)
			if (grid[r][c] == 1)
				cols.push_back(c);

	return minDistance(rows) + minDistance(cols);
}

/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

*/

void buildBFS(vector<vector<int>>& reach, vector<vector<int>>& distance, vector<vector<int>>& grid, int i, int j) {
	int row = grid.size(), col = grid[0].size();
	vector<vector<bool>> visited(row, vector<bool>(col, false));
	queue<pair<int, int>> q;
	q.emplace(i, j);
	int distForOneBuilding = 0;
	vector<vector<int>> dirs = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	while (!q.empty()) {
		distForOneBuilding++;
		int cnt = q.size();

		for (int k = 0; k < cnt; k++) {
			auto cur = q.front();
			q.pop();
			int x = cur.first, y = cur.second;
			reach[x][y] ++;
			for (auto dir : dirs) {
				int nghbX = x + dir[0], nghbY = y + dir[1];
				if (0 <= nghbX && nghbX < row && 0 <= nghbY && nghbY < col
					&& !visited[nghbX][nghbY] && grid[nghbX][nghbY] == 0) {
					distance[nghbX][nghbY] += distForOneBuilding;
					visited[nghbX][nghbY] = true;
					q.emplace(nghbX, nghbY);
				}
			}
		}

	}
}
int shortestDistance(vector<vector<int>>& grid) {
	//BFS
	if (grid.empty())
		return -1;
	int row = grid.size(), col = grid[0].size();

	vector<vector<int>> reach(row, vector<int>(col, 0));
	vector<vector<int>> distance(row, vector<int>(col, 0));

	int building = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (grid[i][j] == 1) {
				building++;
				buildBFS(reach, distance, grid, i, j);
			}

	int res = INT_MAX;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (reach[i][j] == building && grid[i][j] == 0) {
				res = min(res, distance[i][j]);
			}

	return res == INT_MAX ? -1 : res;
}

/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,

	1
	 \
	  3
	 / \
	2   4
		 \
		  5

Longest consecutive sequence path is 3-4-5, so return 3.

	2
	 \
	  3
	 /
	2
   /
  1

Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

*/
int longestConsecutive(TreeNode* root) {
	int res = 0;
	if (!root)
		return res;
	dfs(root, 0, root->val, res);
	return res;
}
void dfs(TreeNode* root, int cur, int target, int& res) {
	if (!root)
		return;
	if (root->val == target)
		cur++;
	else
		cur = 1;
	res = max(res, cur);
	dfs(root->left, cur, root->val + 1, res);
	dfs(root->right, cur, root->val + 1, res);
}

/*
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.

Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
0  -1 INF INF

After running your function, the 2D grid should be:

3  -1   0   1
2   2   1  -1
1  -1   2  -1
0  -1   3   4

*/

void wallsAndGates(vector<vector<int>>& rooms) {
	//BFS
	if (rooms.empty())
		return;
	queue<pair<int, int>> q;
	int row = rooms.size(), col = rooms[0].size();
	vector<vector<int>> dirs = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (rooms[i][j] == 0)
				q.emplace(i, j);
		}
	}
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		int x = cur.first, y = cur.second;
		for (auto dir : dirs) {
			int nghbX = x + dir[0], nghbY = y + dir[1];
			if (0 <= nghbX && nghbX < row && 0 <= nghbY && nghbY < col && rooms[nghbX][nghbY] == INT_MAX) {
				rooms[nghbX][nghbY] = rooms[x][y] + 1;
				q.emplace(nghbX, nghbY);
			}
		}
	}
}

/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
https://leetcode.com/discuss/59787/share-my-java-recursive-solution
*/
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
	while (root && root->val <= p->val) {
		root = root->right;
	}
	if (!root)
		return NULL;
	TreeNode* left = inorderSuccessor(root->left, p);
	return (left != NULL && left->val > p->val) ? left : root;
}

/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

[1,2,3]
[4,5,6,7]
[8,9]

It should return [1,4,8,2,5,9,3,6,7].
*/

class ZigzagIterator {
	queue<pair<vector<int>::iterator, vector<int>::iterator>> q;
public:
	ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		if (!v1.empty())
			q.emplace(v1.begin(), v1.end());
		if (!v2.empty())
			q.emplace(v2.begin(), v2.end());
	}

	int next() {
		auto cur = q.front();
		q.pop();
		auto it = cur.first; // which is v1.begin()
		if (it + 1 != cur.second)
			q.emplace(it + 1, cur.second);
		return *it;
	}

	bool hasNext() {
		return !q.empty();
	}
};

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4]. 

The final sorted nums needs to satisfy two conditions:

If i is odd, then nums[i] >= nums[i - 1];
If i is even, then nums[i] <= nums[i - 1].

The code is just to fix the orderings of nums that do not satisfy 1 and 2.
*/

void wiggleSort(vector<int>& nums) {
	for (int i = 1; i < nums.size(); i++) {
		if (i % 2 && nums[i - 1] > nums[i] || !(i % 2) && nums[i - 1] < nums[i])
			swap(nums[i - 1], nums[i]);
	}
}

/*

Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.

Note: There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1. 
*/
bool knows(int a, int b) {
	return true || false; // forward knows function somehow indicate a knows b or not.
}
int findCelebrity(int n) {
	int cnddt = 0;
	for (int i = 1; i < n; i++) {
		if (!knows(i, cnddt)) {
			cnddt = i;
		}
	}
	for (int i = 0; i < n; i++) {
		if (i == cnddt)
			continue;
		if (knows(cnddt, i) || !knows(i, cnddt))
			return -1;
	}
	return cnddt;
}

/*
There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers.
*/

int numWays(int n, int k) {
	if (n == 0)
		return 0;
	if (n == 1)
		return k;
	int diffColor = k * (k - 1), sameColor = k;
	for (int i = 2; i < n; i++) {
		int lastDiff = diffColor;
		diffColor = (diffColor + sameColor) * (k - 1);
		sameColor = lastDiff;
	}
	return sameColor + diffColor;
}


/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

Given target value is a floating point.
You may assume k is always valid, that is: k ? total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.

*/



//O(N)
void inorderTraversalPre(stack<int>& sPre, TreeNode* root, double target) {
	if (!root)
		return;
	inorderTraversalPre(sPre, root->left, target);
	if (root->val >= target)
		return;
	sPre.push(root->val);
	inorderTraversalPre(sPre, root->right, target);
}
void inorderTraversalSuc(stack<int>& sSuc, TreeNode* root, double target) {
	if (!root)
		return;
	inorderTraversalSuc(sSuc, root->right, target);
	if (root->val < target)
		return;
	sSuc.push(root->val);
	inorderTraversalSuc(sSuc, root->left, target);
}
vector<int> closestKValues(TreeNode* root, double target, int k) {
	// O(N) Inorder traversal, push all the closest value into the stack.
	stack<int> sPre, sSuc;
	inorderTraversalPre(sPre, root, target);
	inorderTraversalSuc(sSuc, root, target);
	vector<int> res;
	while (k > 0) {
		if (sPre.empty()) {
			res.push_back(sSuc.top());
			sSuc.pop();
		}
		else if (sSuc.empty()) {
			res.push_back(sPre.top());
			sPre.pop();
		}
		else {

			double preDiff = abs(double(sPre.top()) - target);
			double sucDiff = abs(double(sSuc.top()) - target);
			if (preDiff > sucDiff) {
				res.push_back(sSuc.top());
				sSuc.pop();
			}
			else {
				res.push_back(sPre.top());
				sPre.pop();
			}
		}
		k--;
	}
	return res;
}
/*
[] 1.00 5 empty
[1] 0.000 1  single element.
[3,2,4,1] 2.00 1   target is in the tree.
[5,3,6,1,4,null,null,null,2] 2.571429, 1  target isn't in the tree. attention double.

*/
// O(kLogN)
void initPre(stack<TreeNode*>& sPre, double target, TreeNode* root) {
	while (root) {
		if (root->val == target) {
			sPre.push(root);
			break;
		}
		else if (root->val > target) {
			root = root->left;
		}
		else if (root->val < target) {
			sPre.push(root);
			root = root->right;
		}
	}
}
void initSuc(stack<TreeNode*>& sSuc, double target, TreeNode* root) {
	while (root) {
		if (root->val == target) {
			sSuc.push(root);
			break;
		}
		else if (root->val > target) {
			sSuc.push(root);
			root = root->left;
		}
		else if (root->val < target) {
			root = root->right;
		}
	}
}
int getNextPre(stack<TreeNode*>& sPre) {
	TreeNode* cur = sPre.top();
	sPre.pop();
	int res = cur->val;
	cur = cur->left;
	while (cur) {
		sPre.push(cur);
		cur = cur->right;
	}
	return res;
}
int getNextSuc(stack<TreeNode*>& sSuc) {
	TreeNode* cur = sSuc.top();
	sSuc.pop();
	int res = cur->val;
	cur = cur->right;
	while (cur) {
		sSuc.push(cur);
		cur = cur->left;
	}
	return res;
}

vector<int> closestKValues(TreeNode* root, double target, int k) {
	vector<int> res;
	if (!root)
		return res;

	// the top of sPre is the Predecessor of target, the largest value that is less than target or the target itself.  sSuc vice visa.
	stack<TreeNode*> sPre, sSuc;
	initPre(sPre, target, root);
	initSuc(sSuc, target, root);

	// [3,2,4,1] 2.00 1 (sPre [2], sSuc [3,2] 2 is the top of sPre and sSuc.) get rid of one of 2 in pre or suc. 
	if (!sPre.empty() && sPre.top()->val == target && !sSuc.empty() && sSuc.top()->val == target)
		getNextPre(sPre);

	while (k > 0) {
		if (sPre.empty()) {
			int next = getNextSuc(sSuc);
			res.push_back(next);
		}
		else if (sSuc.empty()) {
			int next = getNextPre(sPre);
			res.push_back(next);
		}
		else {
			double preDiff = abs(sPre.top()->val - target);
			double sucDiff = abs(sSuc.top()->val - target);
			if (preDiff > sucDiff) {
				int next = getNextSuc(sSuc);
				res.push_back(next);
			}
			else {
				int next = getNextPre(sPre);
				res.push_back(next);
			}
		}
		k--;
	}
	return res;
}

/*
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:
string encode(vector<string> strs) {
// ... your code
return encoded_string;
}

Machine 2 (receiver) has the function:
vector<string> decode(string s) {
//... your code
return strs;
}

So Machine 1 does:
string encoded_string = encode(strs);

and Machine 2 does:
vector<string> strs2 = decode(encoded_string);

strs2 in Machine 2 should be the same as strs in Machine 1.
Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.

TestCase test = { "/123/123/123/", "123/12/6/3/", "", "12" ,  "/", "aa"};
*/
// Encodes a list of strings to a single string.
string encode(vector<string>& strs) {
	string res;
	for (auto str : strs) {
		int len = str.length();
		res += to_string(len) + "/" + str;
	}
	return res;
}

// Decodes a single string to a list of strings.
vector<string> decode(string s) {
	int i = 0;
	vector<string> res;
	while (i < s.length()) {
		size_t found = s.find_first_of("/");
		int count = stoi(s.substr(0, found));
		string elem = s.substr(found + 1, count);
		res.push_back(elem);
		s = s.substr(found + 1 + elem.length());
	}
	return res;
}
/*

Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:
Given s = "aabb", return ["abba", "baab"].
Given s = "abc", return [].

Hint:

If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

test = { "aba", "", "abba", "abcba", "abc", "1234" , "a"};
*/

void dfs(vector<string>& res, string instance, string& s, vector<bool>& check) {
	if (instance.length() == s.length()) {
		res.push_back(instance);
		return;
	}
	for (int i = 0; i < s.length(); i++) {
		if (check[i]) continue;
		if (i > 0 && s[i] == s[i - 1] && !check[i - 1]) continue;
		check[i] = true;
		instance += s[i];
		dfs(res, instance, s, check);
		instance = instance.substr(0, instance.length() - 1);
		check[i] = false;
	}
}
vector<string> permutationII(string s) {
	vector<string> res;
	string instance;
	vector<bool> check(s.length(), false);
	sort(s.begin(), s.end());
	dfs(res, instance, s, check);
	return res;
}

vector<string> generatePalindromes(string s) {
	unordered_map<char, int> m;
	vector<string> res;
	for (auto c : s)
		m[c] ++;
	string half;
	int odd = 0;
	char oddChar;
	for (auto it = m.begin(); it != m.end(); it++) {
		if (it->second % 2) {
			odd++;
			oddChar = it->first;
		}
		if (odd >= 2)
			return res;
		half += string(it->second / 2, it->first);
	}
	res = permutationII(half);
	for (auto & elem : res) {
		string revElem = elem.substr(0, elem.length());
		reverse(revElem.begin(), revElem.end());
		if (s.length() % 2) {
			elem = elem + oddChar + revElem;
		}
		else {
			elem = elem + revElem;
		}
	}
	return res;
}

/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

*/

int minCost(vector<vector<int>>& costs) {
	if (costs.empty())
		return 0;
	int numOfHouse = costs.size();
	int r, g, b;
	r = g = b = 0;
	for (int i = 0; i < numOfHouse; i++) {
		int rr = r, gg = g, bb = b;
		r = costs[i][0] + min(bb, gg);
		g = costs[i][1] + min(rr, bb);
		b = costs[i][2] + min(gg, rr);
	}
	return min(r, min(g, b));
}


/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Follow up:
Could you solve it in O(nk) runtime?
*/
int minCostII(vector<vector<int>>& costs) {
	if (costs.empty())
		return 0;
	int numOfHouse = costs.size(), k = costs[0].size();

	int minKey = 0, minValue = INT_MAX, minValue2 = INT_MAX;
	for (int j = 0; j < k; j++) {
		if (costs[0][j] < minValue) {
			minValue2 = minValue;
			minValue = costs[0][j];
			minKey = j;
		}
		else if (costs[0][j] < minValue2) {
			minValue2 = costs[0][j];
		}
	}

	for (int i = 1; i < numOfHouse; i++) {
		for (int j = 0; j < k; j++) {
			if (i > 0 && j == minKey)
				costs[i][j] += minValue2;
			else
				costs[i][j] += minValue;
		}

		// find min in color
		minKey = 0;
		minValue = minValue2 = INT_MAX;
		for (int j = 0; j < k; j++) {
			if (costs[i][j] < minValue) {
				minValue2 = minValue;
				minValue = costs[i][j];
				minKey = j;
			}
			else if (costs[i][j] < minValue2) {
				minValue2 = costs[i][j];
			}
		}
	}
	return minValue;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	deque<int> dq;
	vector<int> res;
	for (int i = 0; i < nums.size(); i++) {
		if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

		// ensure that the value whose keys are in the deque are in decreasing order. There are k numbers in total;
		/*
		 0	   1  2	   3  4	   5   6	7	8	9
		[100, 90, 96, 95, 90, 92, 94, 93, 92, 91] ,4  (i - k + 1 == i - 3)(i >= 3)
		i, deque
		0, 100 ==>
		1, 100,90 ==>
		2, 100,96(pop_back90) ==>
		3, 100,96,95(i==3,res[100]) ==>
		4, 96,95,90(0 < i - 3, so pop 100, res[100, 96])==>
		5, 96,95,92(1 < i - 3(2), 90 is already popped; res[100, 96, 96]) ==>
		6, 95,94(2 < i - 3(3), so pop 96, pop_back92, push94; res[100, 96, 96, 95]) ==>
		7, 94,93(3 < i - 3(4), so pop 95, push93;res[100, 96, 96, 95, 94] ==>
		8, 94,93,92(6 >= i - 3(5), push92;res[100, 96, 96, 95, 94, 94] ==>
		9, 94,93,92,91(6 >= i - 3(6), push91;res[100, 96, 96, 95, 94, 94, 94] ==>
		*/
		while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
		dq.push_back(i);

		// we can be sure that the front element is the max element within the k range.
		if (i >= k - 1) res.push_back(nums[dq.front()]);
	}
	return res;
}

//https://leetcode.com/problems/copy-list-with-random-pointer/
RandomListNode *copyRandomList2(RandomListNode *head) {
	RandomListNode dummy2(0), *newHead = &dummy2;
	RandomListNode dummy(0);
	dummy.next = head;
	while (head) {
		newHead->next = new RandomListNode(head->label);
		newHead = newHead->next;
		head = head->next;
	}
	head = dummy.next;
	newHead = dummy2.next;
	while (head) {
		RandomListNode* temp = head->next;
		head->next = newHead;
		RandomListNode* temp2 = newHead->next;
		newHead->next = temp;
		head = temp;
		newHead = temp2;
	}
	head = dummy.next;
	while (head) {
		if (head->random) {
			head->next->random = head->random->next;
		}
		head = head->next->next;
	}
	head = dummy.next;
	newHead = dummy2.next;
	while (head) {
		RandomListNode* temp = newHead->next;
		head->next = temp;
		head = head->next;
		if (head) {
			newHead->next = head->next;
			newHead = newHead->next;
		}
	}
	return dummy2.next;
}
RandomListNode *copyRandomList(RandomListNode *head) {
	//<original, copy>
	unordered_map<RandomListNode *, RandomListNode *> m;
	RandomListNode *runner = head;
	while (runner) {
		m[runner] = new RandomListNode(runner->label);
		runner = runner->next;
	}
	runner = head;
	while (runner) {
		m[runner]->random = m[runner->random];
		m[runner]->next = m[runner->next];
		runner = runner->next;
	}
	return m[head];
}

