#include "grid.h"
#include <string> 
#include <list>
#include <iostream>


// insert 3x3.grid.text instead of ./data/3x3.grid.txt 
Grid::Grid(std::string filename, bool logOutput) {
    // try to open the file
    std::ifstream file("./data/" + filename);


    // first comes the number of rows
    file >> rows;
    if(logOutput) std::cout << "There are " << rows << " rows." << std::endl;

    // then the columns
    file >> cols;
    if(logOutput) std::cout << "There are " << cols << " cols." << std::endl;

    // and finally the grid itself
    std::string data;
    file >> data;


    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
            if(logOutput) std::cout << grid[r][c];
        }
        if(logOutput) std::cout << std::endl;
    }
}

std::string Grid::getWordInGrid (int startRow, int startCol, int dir, int len) {
    static std::string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
   for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= cols || r >= rows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case Grid::Directions::north:
                r--;
                break;    
            case Grid::Directions::north_east:
                r--;
                c++;
                break;     
            case Grid::Directions::east:
                c++;
                break;     
            case Grid::Directions::south_east:
                r++;
                c++;
                break;     
            case Grid::Directions::south:
                r++;
                break;     
            case Grid::Directions::south_west:
                r++;
                c--;
                break;    
            case Grid::Directions::west:
                c--;
                break;     
            case Grid::Directions::north_west:
                r--;
                c--;
                break;     
        }
    }

    return output;
}

std::string* Grid::getWordsInGrid (int startRow, int startCol, int len) {
    std::string* words = new std::string[8];
    for (int i = 0; i < 8; i++) {
        words[i] = getWordInGrid(startRow, startCol, i, len);
    }
    return words; 
}


std::list<WordDir> Grid::getAllWordsInAllDirs (int startRow, int startCol, int minLen, HashTable prefixTable) {
    static std::string output;

    std::list<WordDir> outputs; 

    // the position in the output array, the current row, and the
    // current column
    int r, c;
    int dir = 0;
    while (dir != 8) {
        r = startRow, c = startCol;
        bool prefixChecked = false; 
        output.clear(); 
        output.reserve(256);

        while(true) {
            // if the current row or column is out of bounds, then break
            if (c >= cols || r >= rows || r < 0 || c < 0) {
                break;
            }

            // set the next character in the output array to the next letter
            // in the grid
            output += grid[r][c];

            if (output.length() >= minLen) {
                // WordDir wd; 
                // wd.word = output; 
                // wd.dir = dir; 
                // outputs.push_back(wd);
                
                if (prefixTable[output] || output.length() == 3 || prefixChecked) {
                    WordDir wd; 
                    wd.word = output; 
                    wd.dir = dir; 
                    outputs.push_back(wd);
                    prefixChecked = true; 
                } else {
                    break;
                }
            }

            // move in the direction specified by the parameter
            switch (dir) { // assumes grid[0][0] is in the upper-left
                case Grid::Directions::north:
                    r--;
                    break;    
                case Grid::Directions::north_east:
                    r--;
                    c++;
                    break;     
                case Grid::Directions::east:
                    c++;
                    break;     
                case Grid::Directions::south_east:
                    r++;
                    c++;
                    break;     
                case Grid::Directions::south:
                    r++;
                    break;     
                case Grid::Directions::south_west:
                    r++;
                    c--;
                    break;    
                case Grid::Directions::west:
                    c--;
                    break;     
                case Grid::Directions::north_west:
                    r--;
                    c--;
                    break;     
            }
        }
        dir++; 
    }


    return outputs;
}

void Grid::printGrid() {
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            std::cout << grid[r][c];
        }
        std::cout << "\n";
    }
}

int Grid::getRows() {
    return rows; 
}
int Grid::getCols() {
    return cols; 
}
char Grid::getEntry(int row, int col) {
    return grid[row][col];
}

std::string Grid::dirToString(int dir) {
    switch (dir) { // assumes grid[0][0] is in the upper-left
        case Grid::Directions::north:
            return "N";
        case Grid::Directions::north_east:
            return "NE";     
        case Grid::Directions::east:
            return "E";
        case Grid::Directions::south_east:
            return "SE";     
        case Grid::Directions::south:
            return "S";     
        case Grid::Directions::south_west:
            return "SW";    
        case Grid::Directions::west:
            return "W";     
        case Grid::Directions::north_west:
            return "NW";     
    }
    return "NOT FOUND";
}


void Grid::getAllDictWords (int startRow, int startCol, int minLen, HashTable dict, HashTable prefixHashTable) {
 
    int wordsFound = 0; 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int r, c;
            int startRow = i; 
            int startCol = j; 
            static std::string output;

            int dir = 0;

            while (dir != 8) {
                r = startRow, c = startCol;
                bool prefixChecked = false; 
                output.clear(); 
                output.reserve(256);

                while(true) {
                    // if the current row or column is out of bounds, then break
                    if (c >= cols || r >= rows || r < 0 || c < 0) {
                        break;
                    }

                    // set the next character in the output array to the next letter
                    // in the grid
                    output += grid[r][c];

                    if (output.length() >= minLen) {
                        // WordDir wd; 
                        // wd.word = output; 
                        // wd.dir = dir; 
                        // outputs.push_back(wd);
                        if (dict[output]) {
                            wordsFound++; 
                        }
                        else if (!prefixHashTable[output]) {
                            break;
                        }
                        
                        // if (prefixHashTable[output] || prefixChecked) {
                        //     prefixChecked = true; 
                        // } else {
                        //     if (dict[output]) {
                        //         std::cout << dirToString(dir) << " " << "(" << i << ", " << j << "): " << output << "\n";
                        //         wordsFound++; 
                        //     }
                        //     else if (!prefixChecked) {
                        //         break; 
                        //     }
                        // }
                    }

                    // move in the direction specified by the parameter
                    switch (dir) { // assumes grid[0][0] is in the upper-left
                        case Grid::Directions::north:
                            r--;
                            break;    
                        case Grid::Directions::north_east:
                            r--;
                            c++;
                            break;     
                        case Grid::Directions::east:
                            c++;
                            break;     
                        case Grid::Directions::south_east:
                            r++;
                            c++;
                            break;     
                        case Grid::Directions::south:
                            r++;
                            break;     
                        case Grid::Directions::south_west:
                            r++;
                            c--;
                            break;    
                        case Grid::Directions::west:
                            c--;
                            break;     
                        case Grid::Directions::north_west:
                            r--;
                            c--;
                            break;     
                    }
                }
                dir++; 
            }


        }
    }
    std::cout << "words found = " << wordsFound << "\n";
   
}