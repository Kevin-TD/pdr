#include "postfixCalculator.h"
#include <fstream> 
#include "linked_list/List.h" 

string getLineNumber(ifstream& file, int line) {
	string s; 
	for (int i = 1; i <= line; i++) {
		getline(file, s);
	}
	return s; 
}

int main() {
	ifstream fileInput1, fileInput2, fileInput3, fileInput4, fileInput5;
	fileInput1.open("./testinput.txt"); 	
	fileInput2.open("./testinput.txt"); 	
	fileInput3.open("./testinput.txt"); 	
	fileInput4.open("./testinput.txt"); 	
	fileInput5.open("./testinput.txt"); 	

	// 1 = addition; 1 2 3 4 5 + + + + ; expected output 15 
	// 2 = subtraction; 20 10 - -3 10 - - 2 -; expected output 21
	// 3 = multiplication; -1 -2 -5 3 * 2 -2 * * * *; expected output 120 
	// 4 = division; -1512 -12 -2 / / -2 / 3 /; expected output 42 
	// 5 = negation; -1 ~ ~ ~; expected output 1

	string expr1 = getLineNumber(fileInput1, 1);
	string expr2 = getLineNumber(fileInput2, 2);
	string expr3 = getLineNumber(fileInput3, 3);
	string expr4 = getLineNumber(fileInput4, 4);
	string expr5 = getLineNumber(fileInput5, 5);

	cout << "INPUT: " << expr1 << "\nOUTPUT: " << postfixCalculator::compute(expr1) << endl;
	cout << "INPUT: " << expr2 << "\nOUTPUT: " << postfixCalculator::compute(expr2) << endl;
	cout << "INPUT: " << expr3 << "\nOUTPUT: " << postfixCalculator::compute(expr3) << endl;
	cout << "INPUT: " << expr4 << "\nOUTPUT: " << postfixCalculator::compute(expr4) << endl;
	cout << "INPUT: " << expr5 << "\nOUTPUT: " << postfixCalculator::compute(expr5) << endl;

	fileInput1.close(); 
	fileInput2.close(); 
	fileInput3.close(); 
	fileInput4.close(); 
	fileInput5.close(); 
	

	return 0; 
}
