#include "postfixCalculator.h"
#include <fstream> 

string getLineNumber(ifstream& file, int line) {
	string s; 
	for (int i = 1; i <= line; i++) {
		getline(file, s);
	}
	return s; 
}

int main() {
	ifstream fileInput;
	fileInput.open("./testinput.txt"); 	

	// 1 = addition, 2 = subtraction, 3 = multiplication, 4 = division, 5 = negation 
	// modify 2nd arg here 
	string expr = getLineNumber(fileInput, 4);  

	cout << "INPUT: " << expr << "\nOUTPUT: " << postfixCalculator::compute(expr) << endl;   


	return 0; 
}
