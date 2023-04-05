// Insert your header information here
// TreeCalc.cpp:  CS 2150 Tree Calculator method implementations

#include "TreeCalc.h"
#include <iostream>

using namespace std;

// Constructor
TreeCalc::TreeCalc() {
}

// Destructor - frees memory
TreeCalc::~TreeCalc() {
}

// Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* tree) {
	if (tree->left != NULL) {
		cleanTree(tree->left); 
	}

	if (tree->right != NULL) {
		cleanTree(tree->right);
	}

	delete tree; 
}

const string SPECIAL_KEYS = "+-/*"; 
bool isSpecialKey(string key) {
	return SPECIAL_KEYS.find(key) != string::npos; 
}
// Gets data from user
// DO NOT MODIFY
void TreeCalc::readInput() {
    string response;
    cout << "Enter elements one by one in postfix notation" << endl
         << "Any non-numeric or non-operator character,"
         << " e.g. #, will terminate input" << endl;
    cout << "Enter first element: ";
    //cin >> response;
    //while input is legal
	
 //   while (isdigit(response[0]) || response[0] == '/' || response[0] == '*'
 //           || response[0] == '-' || response[0] == '+') {
 //       insert(response);
 //       cout << "Enter next element: ";
 //       cin >> response;
 //   }

  insert("34"); insert("6"); insert("+"); insert("-8"); insert("4"); insert("/"); insert("-"); 
}

// Puts value in tree stack
void TreeCalc::insert(const string& val) {
    // insert a value into the tree
	if (expressionStack.size() == 0) {
		TreeNode* newExpr = new TreeNode(val); 
		expressionStack.push(newExpr); 
	}	
	else {
		if (isSpecialKey(val)) {
			TreeNode* rightChild = expressionStack.top(); 
			expressionStack.pop(); 
			TreeNode* leftChild = expressionStack.top(); 
			expressionStack.pop(); 

			TreeNode* head = new TreeNode(val); 
			head->left = leftChild; 
			head->right = rightChild;

		   	expressionStack.push(head); 	
		}
		else {
			TreeNode* newExpr = new TreeNode(val);
			expressionStack.push(newExpr); 
		}
	}
}

// Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* tree) {
    // print the tree in prefix format
	cout << tree->value << " "; 
	
	if (tree->left != NULL) {
		printPrefix(tree->left); 
	}	

	if (tree->right != NULL) {
		printPrefix(tree->right); 
	}

}

// Prints data in infix form
void TreeCalc::printInfix(TreeNode* tree) {
    // print tree in infix format with appropriate parentheses
	if (tree->left != NULL) {
		cout << "(";
		printInfix(tree->left);
	   	cout << " "; 	
	}

	cout << tree->value; 

	if (tree->right != NULL) {
		cout << " "; 
		printInfix(tree->right); 
		cout << ")"; 
	}
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* tree) {
    // print the tree in postfix form
		if (tree->left != NULL) {
			printPostfix(tree->left); 
		}

		if (tree->right != NULL) {
			printPostfix(tree->right); 
		}

		cout << tree->value << " "; 

	// done so we can read original expr from left to right 
	
}


// Prints tree in all 3 (post, in, pre) forms
// DO NOT MODIFY
void TreeCalc::printOutput() {
    if (expressionStack.size() != 0 && expressionStack.top() != NULL) {
        TreeNode* tree = expressionStack.top();
        cout << "Expression tree in postfix expression: ";
        printPostfix(tree);
        cout << endl;

        cout << "Expression tree in infix expression: ";
        printInfix(tree);
        cout << endl;

        cout << "Expression tree in prefix expression: ";
        printPrefix(tree);
        cout << endl;
    } else {
        cout << "Size is 0." << endl;
    }
}

// Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode* tree) const {
    // Traverse the tree and calculates the result
		
	if (isSpecialKey(tree->value)) {
		int leftValue, rightValue; 

		if (tree->value == "+") {
				if (tree->left != NULL)  {
				if (isSpecialKey(tree->left->value)) {
					leftValue = calculate(tree->left);
				}
				else {
					leftValue = stoi(tree->left->value); 
				}
			}

			if (tree->right != NULL) {
				if (isSpecialKey(tree->right->value)) {
					rightValue = calculate(tree->right); 
				}
				else {
					rightValue = stoi(tree->right->value);
				}
			}

			return leftValue + rightValue; 			
		}
		else if (tree->value == "-") {
			if (tree->left != NULL)  {
				if (isSpecialKey(tree->left->value)) {
					leftValue = calculate(tree->left);
				}
				else {
					leftValue = stoi(tree->left->value); 
				}
			}

			if (tree->right != NULL) {
				if (isSpecialKey(tree->right->value)) {
					rightValue = calculate(tree->right); 
				}
				else {
					rightValue = stoi(tree->right->value);
				}
			}

			return leftValue - rightValue; 
		}
		else if (tree->value == "*") {
			if (tree->left != NULL)  {
				if (isSpecialKey(tree->left->value)) {
					leftValue = calculate(tree->left);
				}
				else {
					leftValue = stoi(tree->left->value); 
				}
			}

			if (tree->right != NULL) {
				if (isSpecialKey(tree->right->value)) {
					rightValue = calculate(tree->right); 
				}
				else {
					rightValue = stoi(tree->right->value);
				}
			}

			return leftValue * rightValue; 
		}
		else if (tree->value == "/") {
			if (tree->left != NULL)  {
				if (isSpecialKey(tree->left->value)) {
					leftValue = calculate(tree->left);
				}
				else {
					leftValue = stoi(tree->left->value); 
				}
			}

			if (tree->right != NULL) {
				if (isSpecialKey(tree->right->value)) {
					rightValue = calculate(tree->right); 
				}
				else {
					rightValue = stoi(tree->right->value);
				}
			}

			return leftValue / rightValue; 
		}
	}

	return 0; 

}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
    // call private calculate method here
    return calculate(expressionStack.top()); 
}
