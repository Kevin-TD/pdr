#include <iostream>
#include <fstream>
#include <string>
#include "hash_table/hash.h"
#include "grid.h"
#include "timer.h"

#define DEBUG true
#if DEBUG
#define printd(x) std::cout << x << std::endl
#else
#define printd(x) 
#endif 

// able to get all words but need optimizations 

// 140x70: my time = 5.46285 s    their time = 1.68816 seconds


int main(int argc, char* argv[]) {
    timer t; 
    
    string wordsFile, gridFile; 

     for ( int i = 1; i < argc; i++ ) {
        std::string s(argv[i]);
        if (i == 1) wordsFile = s;
        if (i == 2) gridFile = s; 
    }
    
    t.start(); 

    HashTable dictionary = HashTable(wordsFile); 
    Grid g = Grid(gridFile, false);

    int rows = g.getRows();
    int cols = g.getCols(); 
    int wordsFound = 0; 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
             std::list<WordDir> allWords = g.getAllWordsInAllDirs(i, j, 3);
             for (auto wordDir : allWords) {
                if(dictionary[wordDir.word]) {
                    std::cout << g.dirToString(wordDir.dir) << " " << "(" << i << ", " << j << "): " << wordDir.word << "\n";
                    wordsFound++; 
                }
             }

        }
    }
    std::cout << wordsFound << " words found\n";

    t.stop(); 

    printd("execution time = " << t.getTime() << " seconds");

}