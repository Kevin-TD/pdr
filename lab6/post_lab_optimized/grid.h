#ifndef GRID_H
#define GRID_H 

#include <string> 
#include <fstream> 
#include <iostream>
#include <list>
#include "hash_table/hash.h"

#define MAXROWS 500
#define MAXCOLS 500

struct WordDir {
    std::string word; 
    int dir; 
};

class Grid {
    public: 
    Grid(std::string filename, bool logOutput);
    void getAllDictWords (int minLen, HashTable dict, HashTable prefixHashTable, std::string outputFileName);

    enum Directions {
        north, 
        north_east, 
        east, 
        south_east, 
        south, 
        south_west, 
        west, 
        north_west
    };

    std::string dirToString(int dir);

    private: 
    char grid[MAXROWS][MAXCOLS];
    int rows, cols; 
};

#endif 