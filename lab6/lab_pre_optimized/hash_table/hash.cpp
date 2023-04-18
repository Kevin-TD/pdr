#include "hash.h"
#include <list>
#include <utility>
#include <iostream> 

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
} 

long long hashString(std::string str) {
	int p = 83; 
	int m = 1e9 + 9;
	long long hash_value = 0; 
	long long p_pow = 1; 
	for (char c : str) {
		hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
	}	
	return hash_value; 
}

HashTable::~HashTable() {
    delete[] buckets; 
}

HashTable::HashTable(int tbSize) {
    tableSize = getNextPrime(tbSize); 
    buckets = new std::list<std::pair<std::string, bool> >[tableSize];
}

void HashTable::insert(std::pair<std::string, bool> pairToInsert) {
    int hashedKey = hash(pairToInsert.first); 
    buckets[hashedKey].push_front(pairToInsert); 
}

int HashTable::hash(std::string stringToHash) {
    return hashString(stringToHash) % tableSize; 
}

bool HashTable::retrive(std::string toRetrieve) {
    int hashedKey = hash(toRetrieve);
    std::list<std::pair<std::string, bool> > bucket = buckets[hashedKey];

    for(auto it = bucket.begin(); it != bucket.end(); ++it) {
	if (it->first == toRetrieve)
	    return it->second; 
    }

    return false;  
}
