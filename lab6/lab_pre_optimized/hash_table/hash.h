// https://uva-cs.github.io/pdr/slides/06-hashes.html#/4/1
// made for string-int pairs 

#include <list>
#include <utility>
#include <iostream>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class HashTable { 
    public:
    HashTable(int tbSize); 
    ~HashTable(); 
    void insert(std::pair<std::string, bool> pairToInsert); 
    bool retrive(std::string toRetrieve); 

    private: 
    int tableSize;
    std::list<std::pair<std::string, bool> >* buckets;
    int hash(std::string stringToHash); 
};

#endif 
