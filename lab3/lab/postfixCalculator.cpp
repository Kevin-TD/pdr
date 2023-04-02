#include "postfixCalculator.h"
#include <string> 
#include "stack.h"

using namespace std;
const string SPECIAL_KEYS = "+-*/~";

postfixCalculator::postfixCalculator() {

}

template <class T>
void reverseStack(stack<T>& s)
{
   T item;
   stack<T> tmpStack;

   while (!s.empty())
   {
      item = s.top();
      s.pop();
      tmpStack.push(item);
   }


   s = tmpStack;
   return;
}

template <class T>
void reverseStackSLL(StackLinkedList<T>& s) {
   T item;
   StackLinkedList<T> tmpStack;

   while (!s.empty())
   {
      item = s.top();
      s.pop();
      tmpStack.push(item);
   }


   s = tmpStack;
   return;
}

bool isSpecialKey(char key) {
	return SPECIAL_KEYS.find(key) != string::npos; 
} 

int postfixCalculator::compute(string expr) {
	string curExpr = "";
	StackLinkedList<string> calcStack; 
	int stringLength = expr.length(); 

	for (int i = 0; i < stringLength; i++ ) {
		char token = expr[i]; 

		if (isSpecialKey(token)) {
			// check if it's a negative number or just minus by seeing if minus sign follows a number
			// i != stringLength - 1 ensures no segfaults; if minus is at end, it is definitely subtraction 
			if (i != stringLength - 1 && isdigit(expr[i+1])) {
				curExpr += token; 
				continue; 
			}
			if (curExpr.length() != 0) {
				calcStack.push(curExpr);
			}
			// pushes operator to stack 
			string s(1, token); 
			calcStack.push(s); 
			curExpr = ""; 
		}
		else if (isspace(token)) {

			if (curExpr.length() != 0)				
				calcStack.push(curExpr);
			curExpr = "";
		} 
		else {
			// number 
			curExpr += token; 
		}
	}
	
	// called so we can read expr from left to right
	reverseStackSLL(calcStack); 

	StackLinkedList<string> poppedStack; 

	while (!calcStack.empty()) {
		string token = calcStack.top(); 
		bool specialKeyFound = false; 	

		// special key 
		if (SPECIAL_KEYS.find(token) != string::npos) {
			specialKeyFound = true; 
			if (token.compare(string("+")) == 0) {
				calcStack.pop(); 
				int operand2 = stoi(poppedStack.top());
			   	poppedStack.pop(); 
				int operand1 = stoi(poppedStack.top());
				poppedStack.pop(); 
				int result = operand1 + operand2; 
				poppedStack.push(to_string(result)); 

				// push back popped stack to main (calc) stack 
				while (!poppedStack.empty()) {
					calcStack.push(poppedStack.top()); 
					poppedStack.pop(); 
				}	
			}
			// code for -*/ is same, only with a change of operator
			else if (token.compare(string("-")) == 0) {
				calcStack.pop(); // remove current -
				int operand2 = stoi(poppedStack.top());
			   	poppedStack.pop(); 
				int operand1 = stoi(poppedStack.top());
				poppedStack.pop(); 
				int result = operand1 - operand2; 
				poppedStack.push(to_string(result)); 
				while (!poppedStack.empty()) {
					calcStack.push(poppedStack.top()); 
					poppedStack.pop(); 
				}
			}
			else if (token.compare(string("*")) == 0) {
				calcStack.pop(); 
				int operand2 = stoi(poppedStack.top());
			   	poppedStack.pop(); 
				int operand1 = stoi(poppedStack.top());
				poppedStack.pop(); 
				int result = operand1 * operand2; 
				poppedStack.push(to_string(result)); 
				while (!poppedStack.empty()) {
					calcStack.push(poppedStack.top()); 
					poppedStack.pop(); 
				}
			}
			else if (token.compare(string("/")) == 0) {
				calcStack.pop();
				int operand2 = stoi(poppedStack.top());
			   	poppedStack.pop(); 
				int operand1 = stoi(poppedStack.top());
				poppedStack.pop(); 
				int result = operand1 / operand2; 
				poppedStack.push(to_string(result)); 
				while (!poppedStack.empty()) {
					calcStack.push(poppedStack.top()); 
					poppedStack.pop(); 
				}
			}
			else if (token.compare(string("~")) == 0) {
				calcStack.pop(); 
				int operand1 = stoi(poppedStack.top()); 
				poppedStack.pop(); 
				int result = -1 * operand1; 
				poppedStack.push(to_string(result));
				while(!poppedStack.empty()) {
					calcStack.push(poppedStack.top()); 
					poppedStack.pop(); 
				}
			}
		}
		else {
			poppedStack.push(token); 
		}
		
		if (!specialKeyFound) 
			calcStack.pop(); 
		
		if (calcStack.empty()) 
			return stoi(token); 
		
	}

	return 0; 
			
}

