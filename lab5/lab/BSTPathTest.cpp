#include "BinarySearchTree.h"
#include <iostream>
#include <fstream> 
#include <string> 

using namespace std;

int main() {
    BinarySearchTree bst;
	ifstream fileInput("./testfile1.txt"); 
	
	string instr, word; 
	while (fileInput >> instr >> word) {
		cout << instr << " " << word << endl; 
		if (instr == "I") {
            bst.insert(word);
        } else if (instr == "R") {
            bst.remove(word);
        } else if (instr == "L") {
            cout << "BST path: " << bst.pathTo(word) << endl;
        }
	}

		
    cout << "BST numNodes: " << bst.numNodes() << endl;
	bst.printTree(); 
	fileInput.close(); 
}
