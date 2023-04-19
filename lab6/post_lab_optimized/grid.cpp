#include "grid.h"
#include <string> 
#include <list>
#include <iostream>
#include <fstream>


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

void Grid::getAllDictWords (int minLen, HashTable dict, HashTable prefixHashTable, std::string outputFileName) {
    int wordsFound = 0; 

    std::ofstream outputFile;
    outputFile.open("./output/" + outputFileName);

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
                        if (dict[output]) {
                            outputFile << dirToString(dir) << " " << "(" << i << ", " << j << "): " << output << "\n";
                            wordsFound++; 
                        }
                        else if (!prefixHashTable[output]) {
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


        }
    }
    outputFile << "words found = " << wordsFound;
    
    outputFile.close(); 
}