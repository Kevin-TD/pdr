// https://uva-cs.github.io/pdr/slides/06-hashes.html#/4/1
// made for string-int pairs 

#include <list>
#include <utility>
#include <iostream>
#include <string>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class HashTable { 
    public:
    HashTable(int tbSize); 
    HashTable(std::string fileName); 
    ~HashTable(); 
    void insert(std::pair<std::string, bool> pairToInsert); 
    bool retrieve(std::string toRetrieve); 
    bool operator[](std::string toRetrieve);
    void log(); 
    float getLoadFactor(); 

    private: 
    int tableSize;
    std::list<std::pair<std::string, bool> >* buckets;
    int hash(std::string stringToHash); 
    float elementCount;
};

#endif 
