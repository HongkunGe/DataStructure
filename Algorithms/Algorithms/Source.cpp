#include "Algorithms.h"
#include "disjointSet.cpp"
#include <assert.h>
int main() {
	vector<char> vc;
	disjointSet<char> ds;
		ds.makeSet('a');
		ds.makeSet('b');
		ds.makeSet('c');
		ds.makeSet('d');
		ds.makeSet('e');
		ds.makeSet('f');
		for (char i = 'a'; i <= 'f'; i++)
			assert(ds.find(i) == i, true);

	return 0;
}
