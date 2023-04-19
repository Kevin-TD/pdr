#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "hash_table/hash.h"
#include "grid.h"
#include "timer.h"

#define DEBUG true
#if DEBUG
#define printd(x) std::cout << x << std::endl
#else
#define printd(x) 
#endif 

// chmod +x averagetime.sh ; ./averagetime.sh

// [settings]: [unopt avg time] -> [opt avg time]  Speedup = unopt/opt

// 140x70 words: 2.59s -> 33 ms    Speedup = 784 
// 300x300 words: 200 seconds -> 298 ms   Speedup = 67114   (4 minutes to 0.3 seconds!). Pre-preprocessing only takes 10 seconds (optimized).


std::list<std::string> genPrefixes(std::string fileName, HashTable wordDict);

int main(int argc, char* argv[]) {
    timer t; 

    string wordsFile, gridFile, outputFileName; 

     for ( int i = 1; i < argc; i++ ) {
        std::string s(argv[i]);
        if (i == 1) wordsFile = s;
        else if (i == 2) gridFile = s; 
        else if (i == 3) outputFileName = s; 
    }
    
    HashTable dictionary = HashTable(wordsFile); 
    Grid g = Grid(gridFile, false);

    std::list<std::string> prefixes = genPrefixes(wordsFile, dictionary);
    HashTable prefixHashTable = HashTable(prefixes);


    t.start(); 
    g.getAllDictWords(3, dictionary, prefixHashTable, outputFileName);
    t.stop(); 

    std::cout << t.getTime() << std::endl; 

}

std::list<std::string> genPrefixes(std::string fileName, HashTable wordDict) {
    std::list<std::string> prefixes; 
    std::ifstream file("./data/" + fileName); 
    std::string line; 

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.length() >= 3) {
                int lineLength = line.length(); 
                std::string s = line.substr(0, 2);
                for (int i = 2; i < lineLength - 1; i++) {
                    s += line[i]; 
                    bool found = (std::find(prefixes.begin(), prefixes.end(), s) != prefixes.end());
                    if (!found)
                        prefixes.push_back(s);
                }

            }
        }
        file.close(); 
    }

    return prefixes;

}