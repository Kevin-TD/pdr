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

//3878 words found in 140x70 words
//27409 words found in 300x300 words

// pre optimizations: on words.txt, 4x7.grid,  average time = 2507 ms 
// 300x300 on words.txt takes ~4 minutes (215.276 seconds)
// 140x70 ~4 to 5 seconds


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

    std::ofstream outputFile;
    outputFile.open("./output/" + outputFileName);

    std::ofstream prefixesFile;
    prefixesFile.open("./output/prefixes.txt");
    
    HashTable dictionary = HashTable(wordsFile); 
    Grid g = Grid(gridFile, false);

    std::list<std::string> prefixes = genPrefixes(wordsFile, dictionary);
    for (auto s : prefixes) {
        prefixesFile << s << "\n";
    }
    prefixesFile.close();

    HashTable prefixHashTable = HashTable(prefixes);

    t.start(); 

    // int rows = g.getRows();
    // int cols = g.getCols(); 

    // int wordsFound = 0; 
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //          std::list<WordDir> allWords = g.getAllWordsInAllDirs(i, j, 3, prefixHashTable);
    //          for (auto wordDir : allWords) {
    //             if(dictionary[wordDir.word]) {
    //                 outputFile << g.dirToString(wordDir.dir) << " " << "(" << i << ", " << j << "): " << wordDir.word << "\n";

    //                 wordsFound++; 
    //             }
    //          }

    //     }
    // }
    // outputFile << wordsFound << " words found\n";
    g.getAllDictWords(0, 0, 3, dictionary, prefixHashTable);

    t.stop(); 

    std::cout << t.getTime() << std::endl; 
    outputFile << t.getTime();

    outputFile.close(); 

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
                    bool found1 = (std::find(prefixes.begin(), prefixes.end(), s) != prefixes.end());
                    // bool found2 = wordDict[s];

                    if (!found1)
                        prefixes.push_back(s);
                }

            }
        }
        file.close(); 
    }

    return prefixes;

}