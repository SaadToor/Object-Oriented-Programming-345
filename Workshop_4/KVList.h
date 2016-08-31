#pragma once
#include <iostream>

template <typename K, typename V, int N>
class KVList {
	K k[N];
	V v[N];
	size_t count;
public:
	KVList():count(0){}
	size_t size() const { return count;}
	const K& key(size_t i) const { return k[i]; }
	const V& value(size_t i) const { return v[i]; }
	KVList& add(const K& kk, const V& vv){
		if (count < N) {
			k[count] = kk;
			v[count] = vv;
			count++;
		}
		return *this;
	}
	int find(const K& kk) const {
		for (size_t i = 0; i < count; i++) {
			if (kk == k[i]) {
				return i;
			}
		}
		return 0;
	}
	KVList& replace(size_t i, const K& kk, const V& vv) {
		if (i < count) {
			k[i] = kk;
			v[i] = vv;
		}
		return *this;
	}
};
