#ifndef GRID_H
#define GRID_H 

#include <string> 
#include <fstream> 
#include <iostream>
#include <list>

#define MAXROWS 500
#define MAXCOLS 500

struct WordDir {
    std::string word; 
    int dir; 
};

class Grid {
    public: 
    Grid(std::string filename, bool logOutput);
    std::string getWordInGrid (int startRow, int startCol, int dir, int len);
    std::string* getWordsInGrid (int startRow, int startCol, int len);
    std::list<WordDir> getAllWordsInAllDirs (int startRow, int startCol, int minLen);
    void printGrid(); 
    int getRows(); 
    int getCols();
    char getEntry(int row, int col); 
    
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