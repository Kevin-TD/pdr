// :new | r!make 
// :bd! 


#include "hash_table/hash.h"
#include <string> 
#include <fstream> 


int getNumberOfLines(std::string fileName) {
    std::ifstream file(fileName); 
    std::string line;
    int count = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            count++;
        }
        file.close();
    }

    return count; 
}


int main() {
    HashTable dictionary = HashTable(getNumberOfLines("./data/words.txt")); 
    std::ifstream file("./data/words.txt"); 
    std::string line; 

    if (file.is_open()) {
	while (getline(file, line)) {
	    dictionary.insert(std::make_pair(line, true)); 
	}
	file.close(); 
    }
    





