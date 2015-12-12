#include "BloomFilter.h"
#include <assert.h>
int main() {
	BloomFilter bf(10, 32, 2);
	string s = "test1";
	bf.add(s);
	assert(bf.contains(s)== bf.containsCheck(s));
	return 0;
}