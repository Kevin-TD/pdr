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
                    outputFile << g.dirToString(wordDir.dir) << " " << "(" << i << ", " << j << "): " << wordDir.word << "\n";
                    wordsFound++; 
                }
             }

        }
    }
    outputFile << wordsFound << " words found";
    outputFile.close(); 

    t.stop(); 

    std::cout << t.getTime() << std::endl; 

}