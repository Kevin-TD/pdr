#include "hash.h"
#include <list>
#include <utility>
#include <iostream>

using namespace std; 

int main() {
	list<pair<string, int> > bucket;
	bucket.push_front(make_pair("a", 1));
	bucket.push_front(make_pair("b", 2));
	for(auto it = bucket.begin(); it != bucket.end(); ++it) {
		cout << it->first << " " << it->second << endl; 
	}
	HashTable m = HashTable(10); 
	m.insert(make_pair("abba", true));
	cout << m.retrive("abba") << endl; 	
} 
