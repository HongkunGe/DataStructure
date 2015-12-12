#include "BloomFilter.h"
/*
Given the number of items, we can get estimate the approximate number of 
BITSET length needed for a better false positive rate. Finally we can set the 
number of hash function.
32bit bloom filter
BloomFilter(10, 32, 2)
*/
BloomFilter::BloomFilter(int nItemNum, int bitsetLength, int kHashFunc) 
	: nHashFunc(kHashFunc), bitVecLength(bitsetLength), nItem(nItemNum) {

	srand(time(NULL));
	if (bitsetLength > MAX_BITSET_LENGTH)
		throw runtime_error("Invalid Bit set length!");

	bitVec = 0;
	for (int i = 0; i < kHashFunc; i++)
		seedsForHash.push_back((unsigned int)rand());
}

void BloomFilter::add(string s) {
	store.insert(s);
	for (int i = 0; i < nHashFunc; i++) {
		// length of hashCode is 32bit.
		unsigned int hashCode = murmurhash2(s.c_str(), s.length(), seedsForHash[i]);

		// set the bit of input string.
		bitVec |= hashCode;
	}
}

bool BloomFilter::contains(string s) {
	
	int bitCur = bitVec;
	for (int i = 0; i < nHashFunc; i++) {
		unsigned int hashCode = murmurhash2(s.c_str(), s.length(), seedsForHash[i]);
		// if some of bits in hashCode is not in bitCur, the string is not in the set.
		unsigned int test = bitCur & hashCode;
		if (test != hashCode) {
			return false;
		}
	}
	return true;
}

bool BloomFilter::containsCheck(string s) {
	return store.count(s) > 0;
}