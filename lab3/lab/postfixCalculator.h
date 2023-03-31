#include <iostream>
#include <cstdlib>
#include <stack> 
#include <string> 

using namespace std;

//  clang++ postfixCalculator.cpp testPostfixCalc.cpp -fsanitize=address -fno-omit-frame-pointer -g; ./a.out
//  ./a.out < addition.txt
// :mksession ~/pdrlab3session.vim
// vim -S ~/pdrlab3session.vim
// https://uva-cs.github.io/pdr/labs/lab03/index.html 


// merely a wrapper for a method 
class postfixCalculator { 
public:
	postfixCalculator(); 
	static int compute(string expr); 	
private:

};


