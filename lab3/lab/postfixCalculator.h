#include <iostream>
#include <cstdlib>
#include <stack> 
#include <string> 
#include "stack.h"

using namespace std;

// wa | !clang++ postfixCalculator.cpp testPostfixCalc.cpp -fsanitize=address -fno-omit-frame-pointer -g; ./a.out
// https://uva-cs.github.io/pdr/labs/lab03/index.html 
// :SaveSession

// merely a wrapper for a method 
class postfixCalculator { 
public:
	postfixCalculator(); 
	static int compute(string expr); 	
private:

};


