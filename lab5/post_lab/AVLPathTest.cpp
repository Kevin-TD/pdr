#include "AVLTree.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    AVLTree avl;
    ifstream fileInput("./testfile3.txt"); 

	string instr, word; 
	while (fileInput >> instr >> word) {
		cout << instr << " " << word << endl; 
        if (instr == "I") {
            avl.insert(word);
        } else if (instr == "R") {
            avl.remove(word);
        } else if (instr == "L") {
            cout << "AVL path: " << avl.pathTo(word) << endl;
        }
    }
    cout << "AVL numNodes: " << avl.numNodes() << endl;
	avl.printTree(); 

	fileInput.close(); 
}
