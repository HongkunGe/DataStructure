#include "LeetCode.h"

/*
input: [ [1, 2, 3], [4, 5, 6] ]
output: [ [1], [2, 3], [3, 5], [6] ]
*/
void zigzagPrint(const vector<vector<int>>& matrix) {
	if (matrix.empty())
		return;
	int row = matrix.size(), col = matrix[0].size();
	for (int cnt = 0; cnt <= row + col - 2; cnt++) {
		for (int i = cnt; i >= 0; i--) {
			if (cnt - row < i && i < col) {
				cout << matrix[cnt - i][i] << " ";
			}
		}
		cout << endl;
	}
}

/*
Use string "(value, lt, rt)" to restore a tree. For example,
(5,(3,(1,null,null),(4,null,null)),(8,null,(9,null,null))

*/
TreeNode* parseStringToTree::parseTree(string input, int& idx) {
	if (idx == input.length())
		return NULL;
	if (input[idx] == 'n') {
		idx += 4;
		return NULL;
	}

	TreeNode* root = NULL;
	if (input[idx] == '(') {
		root = new TreeNode(0);
		idx++;
		int num = 0;
		while (idx < input.length() && '0' <= input[idx] && input[idx] <= '9') {
			num = 10 * num + (input[idx] - '0');
			idx++;
		}
		root->val = num;
		idx++; // skip the ','
		root->left = parseTree(input, idx);
		idx++; // skip the ','
		root->right = parseTree(input, idx);
		idx++; // skip the ')'
	}
	return root;
}
TreeNode* parseStringToTree::parseTree(string input) {
	int idx = 0;
	return parseTree(input, idx);
}


/*
find all the strings in dictionary whose character belongs to alpher.
alper "aaterr" dic = {"aaa", "aar", "qsc", "aate"} => {"aar", "aate"}
*/
void checkInDicDFS(vector<string>& res, string instance, unordered_map<char, int>& alpStore, TrieNode* root) {
	if (root->leaf) {
		res.push_back(instance);
	}
	for (char c = 'a'; c <= 'z'; c++) {
		if (root->child[c - 'a'] != nullptr) {
			if (alpStore.count(c) > 0 && alpStore[c] > 0) {
				alpStore[c] --;
				TrieNode *node = root->child[c - 'a'];
				instance += c;
				checkInDicDFS(res, instance, alpStore, node);
				instance.erase(instance.end() - 1);
				alpStore[c] ++;
			}
		}
	}
}
vector<string> checkInDic(vector<char> alpher, vector<string> dic) {
	Trie dicTree;
	for (auto word : dic) {
		dicTree.insert(word);
	}
	unordered_map<char, int> alpStore;
	for (auto c : alpher)
		alpStore[c] ++;
	vector<string> res;
	string instance;
	checkInDicDFS(res, instance, alpStore, dicTree.root);
	return res;
}



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


BigInt::BigInt(string n) : number(n) {}

string BigInt::add(string other) {
	int len1 = number.length(), len2 = other.length();
	int i1 = len1 - 1, i2 = len2 - 1, carry = 0;
	string res;
	while (i1 >= 0 || i2 >= 0) {
		int cur = 0;
		if (i1 >= 0) {
			cur += (number[i1] - '0');
			i1--;
		}
		if (i2 >= 0) {
			cur += (other[i2] - '0');
			i2--;
		}
		cur += carry;
		res.insert(0, 1, (cur % 10 + '0'));
		carry = cur / 10;
	}
	if (carry)
		res.insert(0, 1, (carry + '0'));
	return res;
}

BigInt BigInt::operator+(const BigInt& bi) {
	BigInt res(this->number);
	res.set(res.add(bi.number));
	return res;
}

BigInt BigInt::operator*(const BigInt& bi) {
	BigInt res(this->number);
	res.set(res.multiply(bi.number));
	return res;
}
string BigInt::multiply(string other) {
	int len1 = number.length(), len2 = other.length();
	string multiplyRes(len1 + len2, '0');
	for (int i = len1 - 1; i >= 0; i--) {
		int carry = 0;
		for (int j = len2 - 1; j >= 0; j--) {
			int current = carry + (multiplyRes[i + j + 1] - '0') + (number[i] - '0') * (other[j] - '0');
			multiplyRes[i + j + 1] = current % 10 + '0';
			carry = current / 10;
		}
		multiplyRes[i] += carry;
	}
	size_t found = multiplyRes.find_first_not_of("0");
	if (found != string::npos)
		return multiplyRes.substr(found);
	return "0";

}


/*

"abc01", "abc000", "abcd000" => "abc000", "abc01", "abcd000";

"abc012", "abc013", "abc0001", "abc010", "abc2", "abc11", "bbc11" =>
"abc0001", "abc2", "abc010", "abc11", "abc012", "abc013", "bbc11"
*/
bool isAlper(char c) {
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}
// s2 is larger than s1.
bool cString(const string& s1, const string& s2) {
	int i = 0;
	while (i < min(s1.length(), s2.length())) {
		if (isAlper(s1[i]) && isAlper(s1[i])) {
			if (s1[i] < s2[i])
				return true;
			else if (s1[i] > s2[i])
				return false;
		}
		else if (isAlper(s1[i])) { // s1 is one more letter. 
			return false;
		}
		else if (isAlper(s2[i])) { // s2 is one more letter. 
			return true;
		}
		else {
			break; // abcd012, abcd012, 0;
		}
		i++;
	}
	if (i == s1.length())
		return true; // s2 is longer
	else if (i == s2.length())
		return false; // s1 is longer

					  // compare the digit part.
	size_t found1 = s1.find_first_of("123456789");
	size_t found2 = s2.find_first_of("123456789");
	if (found1 == string::npos && found2 == string::npos)
		return s1.length() < s2.length();
	else if (found2 == string::npos)
		return false; // s2 is abcd000
	else if (found1 == string::npos)
		return true; // s1 is abcd000

	string digit1 = s1.substr(found1), digit2 = s2.substr(found2);
	if (digit1.length() != digit2.length())
		return digit1.length() < digit2.length();

	i = 0;
	while (i < digit1.length()) {
		if (digit1[i] < digit2[i])
			return true;
		else if (digit1[i] > digit2[i])
			return false;
		i++;
	}
	return true;
}

/*
find the next excel number A=>B   ZZ => AAA
*/
string nextExcel(string s) {
	int carry = 1;
	for (int i = s.length() - 1; i >= 0; i--) {
		s[i] += carry;
		if (s[i] > 'Z') {
			s[i] = 'A';
			carry = 1;
		}
		else {
			carry = 0;
			break;
		}
	}
	if (carry)
		s.insert(0, 1, 'A');
	return s;
}

/*

One-direction path: the path that starts from one node and continues in 
one single direction(continously left or continously right). 
find One-direction path, the node may not be the root of the tree.

*/
void find_longest_path(TreeNode* root, int& left, int& right, int& res)
{
	if (root == nullptr) {
		left = right = 0;
		return;
	}

	int left_left = 0, left_right = 0, right_left = 0, right_right = 0;
	find_longest_path(root->left, left_left, left_right, res);
	find_longest_path(root->right, right_left, right_right, res);

	left = left_left + 1;
	right = right_right + 1;
	res = max(res, max(left, right));
}


/*

get the amplitude of a tree. 
the amplitude of a path in a tree is the difference between the max and min in one path
from root to leaves. the amplitude of a tree is the max of amplitude of all the path.

*/
void amplitude(TreeNode* root, int maxNum, int minNum, int &res) {
	if (!root) {
		res = max(res, maxNum - minNum); // the end of one path.
		return;
	}
	maxNum = max(maxNum, root->val);
	minNum = min(minNum, root->val);

	amplitude(root->left, maxNum, minNum, res);
	amplitude(root->right, maxNum, minNum, res);
	return;
}
int amplitude(TreeNode* root) {
	int maxNum, minNum, res = 0;
	if (!root) return 0;
	maxNum = minNum = root->val;
	amplitude(root, maxNum, minNum, res);
	return res;
}

void amplitude2(TreeNode* root, int maxNum, int minNum, int &res) {
	if (!root) return;
	if (!root->left && !root->right) {
		res = max(res, maxNum - minNum); // the end of one path.
	}
	if (root->left) {
		maxNum = max(root->left->val, maxNum);
		minNum = min(root->left->val, minNum);
		amplitude2(root->left, maxNum, minNum, res);
	}
	if (root->right) {
		maxNum = max(root->right->val, maxNum);
		minNum = min(root->right->val, minNum);
		amplitude2(root->right, maxNum, minNum, res);
	}
	return;
}
int amplitude2(TreeNode* root) {
	int maxNum, minNum, res = 0;
	if (!root) return 0;
	maxNum = minNum = root->val;
	amplitude2(root, maxNum, minNum, res);
	return res;
}

/*
insert a node into cyclic linked list. The head provided may not be the one with min value.
Find the min node first.
*/

ListNode* insertCycleLinkedlist(ListNode* head, int val) {
	if (!head) {
		head = new ListNode(val);
		head->next = head;
		return head;
	}
	// find the node with min value.
	int minValue = head->val;
	ListNode* runner = head->next, *minHead = head;
	while (runner != head) {
		if (minValue > runner->val) {
			minValue = runner->val;
			minHead = head;
		}
		runner = runner->next;
	}
	ListNode* prev = minHead, *cur = prev->next;
	bool inserted = false;
	while (cur != minHead) {
		if (prev->val <= val && val <= cur->val) {			
			ListNode* newNode = new ListNode(val);
			newNode->next = cur;
			prev->next = newNode;
			inserted = true;
			break;
		}
		cur = cur->next;
		prev = prev->next;
	}
	if (inserted)
		return minHead;

	ListNode* newNode = new ListNode(val);
	newNode->next = minHead;
	prev->next = newNode;
	if (val < minHead->val)
		return newNode;
	else if (val > prev->val)
		return minHead;
}

/*
ArithmeticSlice
Given array A, returns the number of arithmetic slices in A. 
*/

int countArithmeticSlice(vector<int> arr) {
	int size = arr.size();
	if (size < 3)
		return 0;
	int lastDiff = INT_MAX, curDiff = 0, start = 0, countPerDiff = 0, res = 0;
	for (int i = 1; i < size; i++) {
		curDiff = arr[i] - arr[i - 1];
		if (curDiff == lastDiff)
			countPerDiff += i - start - 1;
		else {
			start = i - 1;
			res += countPerDiff;
			countPerDiff = 0;
			lastDiff = curDiff;
		}
	}
	res += countPerDiff;
	return res;
}

/*
Amazon
Cache Miss, given the max size of a LRU cache and a input array, calculate the miss time
*/

int LRUCacheMiss(vector<int> input, int maxSize) {
	typedef list<int> LI;
	typedef list<int>::iterator LII;		// key iterator 
	typedef unordered_map<int, LII> MLII;	// key, (key iterator)

	LI cache;
	MLII check;
	int count = 0;
	for (int i = 0; i < input.size(); i++) {
		if (check.count(input[i]) > 0) {
			// found in the LRU cache.
			cache.erase(check[input[i]]);
			cache.push_front(input[i]);
			check[input[i]] = cache.begin();
		}
		else {
			// not found, miss happens.
			count++;
			cache.push_front(input[i]);
			check[input[i]] = cache.begin();
			if (cache.size() > maxSize) {
				int key = cache.back();
				cache.pop_back();
				check.erase(key);
			}
		}
	}
	return count;
}
int cachMiss(vector<int> array, int size) {
	int len = array.size();
	vector<int> store;
	vector<int>::iterator iter;
	int count = 0;
	for (int i = 0; i < len; ++i) {
		iter = find(store.begin(), store.end(), array[i]);
		// hit
		if (iter != store.end()) {
			store.erase(iter);
			store.push_back(array[i]);
		}
		// miss
		else {
			count++;
			if (store.size() == size) {
				store.erase(store.begin());
				store.push_back(array[i]);
			}
			else
				store.push_back(array[i]);
		}
	}
	return count;
}

/*
Amazon
Day changes: 1D Game of Life
two neighbors of one cell are the same => set 0, otherwise => set 1. 
*/
vector<int> dayChange(vector<int> original, int days) {

	int len = original.size();

	vector<int> curr(len, 0), dayBefore = original;
	if (days <= 0 || len <= 0)
		return original;

	if (len == 1) {
		curr[0] = 0;
		return curr;
	}
	for (int i = 0; i < days; i++) {
		for (int j = 1; j < len - 1; j++) {
			curr[j] = (dayBefore[j - 1] == dayBefore[j + 1]) ? 0 : 1;
		}
		curr[0] = (dayBefore[1] == 0) ? 0 : 1;
		curr[len - 1] = (dayBefore[len - 2] == 0) ? 0 : 1;
		dayBefore = curr;
	}
	return curr;
}

/*
Amazon
window sum
*/
vector<int> windowSum(vector<int>& input, int window) {
	vector<int> res;
	int sum = 0, count = 0;

	for (int i = 0; i < window && i < input.size(); i++)
		sum += input[i];
	res.push_back(sum);
	if (window >= input.size())
		return res;

	for (int i = window; i < input.size(); i++) {
		sum = sum - input[i - window] + input[i];
		res.push_back(sum);
	}
	return res;
}

/*
Amazon
kth closest points in a grid.

int k = 2;
vector<Node> pts;
Node p1(-2, -4);
pts.push_back(p1);
Node p2(0, 0);
pts.push_back(p2);
Node p3(10, 15);
pts.push_back(p3);
Node p4(5, 6);
pts.push_back(p4);
Node p5(7, 8);
pts.push_back(p5);
Node p6(-10, -30);
pts.push_back(p6);

origin = Node(0, 0);
auto res = findKClosestPoint(pts, k);
*/
struct Node {
	int x, y;
	Node(int xx = 0, int yy = 0) : x(xx), y(yy) {};
};
Node origin(0, 0);
double distance(Node n) {
	return ((double)n.x - origin.x) * ((double)n.x - origin.x) + ((double)n.y - origin.y) * ((double)n.y - origin.y);
}
struct cmp {
	bool operator()(Node n1, Node n2) {
		return distance(n1) < distance(n2); // maxHeap
	}
};
vector<Node> findKClosestPoint(vector<Node> nodes, int k) {
	if (k >= nodes.size())
		return nodes;
	priority_queue<Node, vector<Node>, cmp> pq(nodes.begin(), nodes.begin() + k);
	for (int i = k; i < nodes.size(); i++) {
		if (distance(nodes[i]) < distance(pq.top())) {
			pq.push(nodes[i]);
			pq.pop();
		}
	}
	vector<Node> res;
	for (int i = 0; i < k; i++) {
		res.push_back(pq.top());
		pq.pop();
	}
	return res;
}
/*
Amazon
rotate a matrix 90 degree in clockwise or anti-clockwise.
*/
void rotateMatrix(vector<vector<int>>& matrix, bool direction) {
	if (matrix.empty())
		return;
	int n = matrix.size(), m = matrix[0].size();
	vector<vector<int>> rotated(m, vector<int>(n, 0));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			rotated[j][i] = direction ? matrix[i][j] : matrix[n - 1 - i][m - 1 - j];

	int half = n / 2;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < half; j++)
			swap(rotated[i][j], rotated[i][n - 1 - j]);

	matrix = rotated;
}


//http://matchstickpuzzles.blogspot.com/2011/06/55-4x4-square-how-many-squares.html
int countSquare(vector<vector<bool>>& horizontal, vector<vector<bool>>& vertical) {
	if (horizontal.empty() || vertical.empty())
		return 0;
	int n = horizontal.size(), m = vertical.size();
	if (n == 0 || m == 0 || n != vertical[0].size() || m != horizontal[0].size())
		return 0;

	vector<vector<int>> lengthHor(n, vector<int>(m, 0)), lengthVer(m, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		lengthHor[i][0] = horizontal[i][0];
		for (int j = 1; j < m; j++) {
			if (horizontal[i][j]) {
				lengthHor[i][j] = lengthHor[i][j - 1] + 1;
			}
			else {
				lengthHor[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < n; j++) {
		lengthVer[0][j] = vertical[0][j];
		for (int i = 1; i < m; i++) {
			if (vertical[i][j]) {
				lengthVer[i][j] = lengthVer[i - 1][j] + 1;
			}
			else {
				lengthVer[i][j] = 0;
			}
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int len = 1; len <= min(m - i, m - j); len++) {
				if (lengthHor[i][len + j - 1] >= len &&
					lengthHor[i + len][len + j - 1] >= len &&
					lengthVer[i + len - 1][j] >= len &&
					lengthVer[i + len - 1][j + len] >= len) {
					res++;
				}
			}
		}
	}
	return res;
}

/*

delete all node with Fibonacci index. 
*/
bool isPerfectSquare(int n)
{
	//Perfect squares can only end in 0, 1, 4, or 9 in base 16
	int h = n & 0xF;  // h is the last hex "digit"
	if (h > 9)
		return 0;
	// Use lazy evaluation to jump out of the if statement as soon as possible
	if (h == 0 || h == 1 || h == 4 || h == 9)
	{
		int t = (int)floor(sqrt((double)n) + 0.5);
		return t*t == n;
	}
	return 0;
}
bool isFibonacci(int n) {
	return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}
ListNode* deleteFibonacci(ListNode* head) {
	int index = 0;
	ListNode* runner = head;
	ListNode dummy(0), *prev = &dummy;
	dummy.next = head;
	while (runner) {
		if (isFibonacci(index)) {
			cout << index << " ";
			ListNode* cur = runner;
			runner = runner->next;
			prev->next = runner;
			delete cur;
		}
		else {
			runner = runner->next;
			prev = prev->next;
		}
		index++;
	}
	return dummy.next;
}

/*
Amazon
Largest Arithmetic Sequence.
*/
int getLAS(int array[], int size) {
	if (size < 3)
		return 0;
	int res = 0;
	int diff = INT_MIN;
	int count = 0;
	int start = 0;
	for (int i = 1; i < size; ++i) {
		int currDiff = array[i] - array[i - 1];
		if (diff == currDiff) {
			count += i - start - 1 > 0 ? i - start - 1 : 0;
		}
		else {
			start = i - 1;
			diff = currDiff;
			res += count;
			count = 0;
		}
	}
	res += count;
	return res;
}

/*
Groupon
find k most occuring string.
*/
typedef pair<string, int> node;
// minHeap.
class cmpC {
public:
	bool operator()(node n1, node n2) {
		return n1.second > n2.second;
	}
};
// find k most occuring string.
vector<string> findKmostOccurString(vector<string> dataStream, int k) {
	unordered_map<string, int> cntString;
	for (auto word : dataStream)
		cntString[word] ++;

	priority_queue< node, vector<node>, cmpC > pq;
	vector<string> res;
	for (auto it = cntString.begin(); it != cntString.end(); it++) {
		if (pq.size() < k) {
			pq.push(make_pair(it->first, it->second));
		}
		else {
			if (it->second > pq.top().second) {
				pq.pop();
				pq.push(make_pair(it->first, it->second));
			}
		}
	}
	int total = pq.size();
	for (int i = 0; i < total; i++) {
		res.push_back(pq.top().first);
		pq.pop();
	}
	return res;
}

//bucket sort
/*
Sort a large set of floating point numbers which are in range from 0.0 to 1.0 and are uniformly distributed across the range
Asume we already know the max of the array.
1. declare n empty buckets.
2. j = x[i] / max(x) * n;  put x[i] in the bucket[j];
3. sort each bucket
4. concatenate all the buckets.
*/
// assume max = 1000.0 
//?
vector<float> bucketSort(vector<float>& data) {
	const int n = data.size();
	vector<list<float>> buckets(n, list<float>());
	vector<float> res;
	for (auto num : data) {
		int j = num / 1000 * n; // j = 0..n-1
								// insert into each bucket
		auto it = buckets[j].begin();
		auto prev = it;
		while (it != buckets[j].end()) {
			if (*it < num) {
				prev = it;
				it++;
			}
			else {
				buckets[j].insert(prev, num);
				break;
			}
		}

		if (it == buckets[j].end())
			buckets[j].insert(it, num);
	}
	for (int j = 0; j < n; j++) {
		for (auto it = buckets[j].begin(); it != buckets[j].end(); it++) {
			res.push_back(*it);
		}
	}
	return res;
}

/*
Groupon

To get the lowdown on recursion and recursive functions, please see C++ Recursion Example 1 (Understanding the Basics)To get the lowdown on recursion and recursive functions, please see C++ Recursion Example 1 (Understanding the Basics)To get the lowdown on recursion and recursive functions, please see C++ Recursion Example 1 (Understanding the Basics)To get the lowdown on recursion and recursive functions, please see C++ Recursion Example 1 (Understanding the Basics)

Tree-traversal and recursion are truly soul-mates. Tree-traversal is somewhat unintuitive with regular
loop structures, but it falls naturally into the Divide and Conquer paradigm. A tree
is generally a data structure that contains a list of additional data structures within itself. Please
see PseudoDirectory.cpp for an example.

The code should mainly speak for itself. PseudoDirectory is a C++ class that contains a list of
more PseudoDirectories and a name. The goal is to visit all the directories and print out the name
of each one.

This is a depth-first tree traversal because we start at the parent and visit the immediate child until
there are no more children to visit. So if we had this tree:
A
--B
----C
--D
----E

We would visit A, B, C, D, E in that order.

A breadth-first tree traversal would visit A, B, D, C, E in that order.

The depth param is for formatting purposes only, and isn't actually necessary to recurse a tree. In this
example it is used to print out spaces so we can more easily see the logical parent-child hierarchy.
*/
class PseudoDirectory
{
public:
	string name;
	vector<PseudoDirectory> childDirs;

	PseudoDirectory(string dirName) : name(dirName) { }
	PseudoDirectory() : name("") { }
};
/*
We don't want the user worrying about the depth param in the recursive function above, so we just wrap
that function here to make the function call more intuitive and convenient.
*/

void traverse(const PseudoDirectory& dir, int depth)
{
	for (int i = 0; i < depth; i++)
		std::cout << " ";

	//Write the name of each directory out to the console and then move down to a new line.
	std::cout << "-";
	std::cout << dir.name << std::endl;

	//Loop through all child directories and traverse them as well.
	for (int i = 0; i < dir.childDirs.size(); i++)
		traverse(dir.childDirs[i], depth + 1);
}


void traverse(const PseudoDirectory& dir)
{
	traverse(dir, 0);
}

/*

Optimal coin for money changes.

*/

/*
S[i] means the minimum number of coins needed for the changes with value i; S[change] is the min number of
coins needed for "change".
seq[i] means the needed coin index for current change. coin index sequence.
*/
int CoinChange(vector<int> C, int change)
{
	vector<int> S(change + 1, INT_MAX);
	vector<int> seq(change + 1);
	S[0] = 0;
	for (int i = 1; i < change + 1; i++)
	{
		for (int j = 0; j < C.size(); j++)
		{
			if (i >= C[j] && 1 + S[i - C[j]] < S[i])
			{
				S[i] = 1 + S[i - C[j]];
				seq[i] = j;
			}
		}
	}

	cout << "Coins: " << endl;
	int j = change;
	while (j)
	{
		cout << " " << C[seq[j]];
		j = j - C[seq[j]];
	}
	cout << endl;
	return S[change];
}

/*
count how many solutions to find changes for a amount of money.
*/
int Coins_rec(int * S, int m, int n) {
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	if (m <= 0 && n >= 0) {
		return 0;
	}
	return (Coins_rec(S, m - 1, n) + Coins_rec(S, m, n - S[m - 1]));
}

//http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
int Coins_memoization(int * S, int m, int n, vector<vector<int>>& memo) {
	// If n is 0 then there is 1 solution (do not include any coin)
	if (n == 0)
		return 1;
	// If n is less than 0 then no solution exists
	if (n < 0)
		return 0;
	// If there are no coins and n is greater than 0, then no solution exist
	if (m <= 0 && n >= 0)
		return 0;
	// count is sum of solutions (i) no S[m-1] + (ii) at least one S[m-1] 
	if (memo[m][n] != -1) {
		return memo[m][n];
	}
	else
	{
		memo[m][n] = (Coins_memoization(S, m - 1, n, memo) + Coins_memoization(S, m, n - S[m - 1], memo));
		return memo[m][n];
	}
}

int Coins_tabulation(int * S, int m, int n)
{
	vector<vector<int>> L(m + 1, vector<int>(n + 1, 0));	//L[i][j] -> Minimum number of 'i' different types of coins required to make final amonut j
	int i, j;

	L[0][0] = 1;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			if (i == 0 && j >= 0) {
				L[0][j] = 0;
			}
			else if (i > 0 && j == 0) {
				L[i][0] = 1;
			}
			else {
				// count is sum of solutions (i) no S[m-1] + (ii) at least one S[m-1] 
				L[i][j] = ((i >= 1) ? L[i - 1][j] : 0) + ((j - S[i - 1] >= 0) ? L[i][j - S[i - 1]] : 0);
			}
		}
	}
	return L[m][n];
}


/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
*/

// one guy can take part in as much as meeting as he can. How many can he attend?  => greedy algorithm
bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.second < b.second)
		return true;
	return false;
}

int attendMaxMeeting(vector<pair<int, int>> periods) {
	if (periods.empty())
		return 0;
	sort(periods.begin(), periods.end(), cmp);
	vector<pair<int, int>> canAttend;
	canAttend.push_back(periods[0]);
	for (auto meeting : periods) {
		if (meeting.first >= canAttend.back().second) {
			canAttend.push_back(meeting);
		}
	}
	return canAttend.size();
}


// Definition for an interval.
/*
find the minimum number of conference rooms required.
*/
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct cmpEnd {
	bool operator()(Interval i1, Interval i2) {
		return i1.end > i2.end;
	}
};
bool cmpStart(Interval i1, Interval i2) {
	return i1.start < i2.start;
}
int minMeetingRooms(vector<Interval>& intervals) {
	if (intervals.empty())
		return 0;
	priority_queue<Interval, vector<Interval>, cmpEnd > pq;
	sort(intervals.begin(), intervals.end(), cmpStart);
	pq.push(intervals[0]);
	for (int i = 1; i < intervals.size(); i++) {
		// find the meeting that finished earliest
		Interval minEndInv = pq.top();
		pq.pop();

		if (minEndInv.end <= intervals[i].start) {
			//merge the two intervals, no need a new room.
			minEndInv.end = intervals[i].end;
		}
		else {
			// a new room is needed.
			pq.push(intervals[i]);
		}
		pq.push(minEndInv);
	}
	return pq.size();
}

/*
TestCase test = { "/123/123/123/", "123/12/6/3/", "", "12" ,  "/", "aa" };
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

void reverseSecondHalf(ListNode* head) {
	// find the middle node;
	if (!head) return;
	ListNode* slow, *fast;
	slow = fast = head;
	while (fast && fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	// slow is middle node;
	ListNode* sndStart = slow->next, *prev = NULL;
	slow->next = NULL;
	while (sndStart) {
		ListNode* temp = sndStart->next;
		sndStart->next = prev;
		prev = sndStart;
		sndStart = temp;
	}
	slow->next = prev;
}










/*

SJF: Short Job First.

*/

struct task {
	int arrive;
	int execute;
	task(int a = 0, int e = 0) : arrive(a), execute(e) {};
};

struct cmp {
	bool operator()(task t1, task t2) {
		return t1.execute > t2.execute;
	}
};

float waitingTimeSJF(int* requestTimes, int *durations, int n) {
	int cur = 0, wait = 0, i = 0;
	priority_queue<task, vector<task>, cmp> pq;
	while (!pq.empty() || i < n) {
		if (!pq.empty()) {
			task t = pq.top();
			pq.pop();
			wait += (cur - t.arrive);
			cur += t.execute;
			for (; i < n; i++) {
				if (requestTimes[i] <= cur) {
					task newT(requestTimes[i], durations[i]);
					pq.push(newT);
				}
				else {
					break;
				}
			}
		}
		else {
			task newT(requestTimes[i], durations[i]);
			pq.push(newT);
			cur = requestTimes[i++];
		}
	}
	return (float)(wait) / n;
}

int find_optimal_flip2(vector<int>& arr)
{
	// initial number of ones
	int orig = accumulate(arr.begin(), arr.end(), 0);
	int max_change = -1;	// max increase of number of ones
	int prev_zero = -1;		// previous zero index (optimal i and j only happen at zero elements)
	int cur_change = 0;		// current increase of number of ones 
							// negative if there are more increases of zeros than ones

							// find the first zero element
	int i = 0;
	while (i < arr.size() && arr[i] != 0)
		++i;

	// if no zero, the maximum change is -1
	if (i == arr.size())
		return orig + max_change;

	// loop over all zero elements, 
	// if cur_change <=1, move the begin of sliding window
	// otherwise, keep the begin
	prev_zero = i;
	max_change = cur_change = 1;
	for (++i; i < arr.size(); ++i) {
		if (arr[i] == 1)
			--cur_change;
		else {
			++cur_change;
			max_change = max(max_change, cur_change);
			if (cur_change <= 1) {
				prev_zero = i;
				cur_change = 1;
			}
		}
	}

	return orig + max_change;
}



struct Process {
	int arriveTime;
	int executeTime;
	Process(int a, int e) : arriveTime(a), executeTime(e) {}
};

double roundRobin(int arrive[], int execute[], int q, int size) {
	int curTime = 0;
	int waitTime = 0;
	int next = 0;
	queue<Process*> myqueue;

	myqueue.push(new Process(arrive[next], execute[next]));
	//next++;
	curTime = arrive[next++]; // ?

	while (!myqueue.empty()) {
		Process* cur = myqueue.front();
		myqueue.pop();

		waitTime += (curTime - cur->arriveTime) >= 0 ? (curTime - cur->arriveTime) : 0;
		curTime += min(q, cur->executeTime);

		for (int i = next; i < size; ++i) {
			if (arrive[i] < curTime) {
				myqueue.push(new Process(arrive[i], execute[i]));
				next = i + 1;
			}
			else
				break;
		}
		if (q < cur->executeTime)
			myqueue.push(new Process(curTime, cur->executeTime - q));
	}
	return (double)waitTime / size;
}