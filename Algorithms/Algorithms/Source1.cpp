#include "Algorithms.h"

vector<int> numIslands::numIslands2(int m, int n, vector<pair<int, int>>& positions) {
	vector<int> res;
	

}

int numIslands::index(int x, int y) {
	return x * n + y + 1; // transfer to be 1-based index.
}

int numIslands::add(int x, int y) {
	int idx = index(x, y);
	ds.makeSet(idx);
	return idx;
}