#include "Trie.h"
#include <assert.h>

int main() {
	Trie t2;
	t2.insert("abcdefg");
	t2.insert("abcde");
	t2.insert("abc");
	assert(!t2.remove("zxcv"), true);

	assert(t2.search("abc"), true);
	assert(t2.search("abcdefg"), true);
	assert(t2.search("abcde"), true);

	assert(t2.remove("abcde"), true);

	assert(t2.search("abc"), true);
	assert(t2.search("abcdefg"), true);
	assert(!t2.search("abcde"), true);

	assert(!t2.isEmpty(), true);

	return 0;
}