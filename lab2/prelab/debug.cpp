//----------------------------------------------------------------------
// This program reads five numbers from the keyboard, and prints out the
// average and the maximum value
//----------------------------------------------------------------------

#include <iostream>
using namespace std;

// Global Constants
const int MAX = 5;

// Function Prototypes
double GetAverage( int nIn[], int nMax);
int GetMax( int nIn[], int nMax );


int main() {

    int nValues[MAX];
    int nCount;

    // Display a prompt:
    cout << "Enter five numbers: " << endl;

    // First we read in the numbers.
    for ( nCount = 0; nCount < MAX; nCount++ ) {
        cout << "Enter the next number : ";
        cin >> nValues[nCount];
    }

    // Now we echo the input back to the user
    for ( nCount = 0; nCount < MAX; nCount++) {
        cout << "Value [" << nCount << "] is : " << nValues[nCount] << endl;
    }

    // Now lets call a function to get the average:
    cout << "The average is " << GetAverage(nValues, MAX ) << endl;

    // Now lets call a function to get the max:
    cout << "The max is " << GetMax(nValues, MAX ) << endl;

    return 0;

} // End of main


double GetAverage(int nIn[], int nMax) {

    double temp = 0.0;
    for ( int i = 0; i < nMax; i++)
        temp += nIn[i];
    temp /= nMax;

    return temp;
} // End of GetAverage()


int GetMax( int nIn[], int nMax) {
    int nBiggest = nIn[0];
    for ( int i = 0; i < nMax; i++)
        if (nBiggest < nIn[i])
            nBiggest = nIn[i];
    return nBiggest;
} // End of GetMax()

//----------------------------------------------------------------------
// END OF LISTING
//----------------------------------------------------------------------


// clang++ debug.cpp -Wall -g -o lab2
// We’ve seen -Wall and -g already – the -o lab2 flag (short for --output) will cause the output executable to be lab2 instead of a.out. Thus, we also need to run lldb with lldb lab2 rather than lldb a.out.

// bt: shows a list of the function calls that got us to this point (we are only in the main() method at this point, so it’s not all that interesting)
// list: shows a listing of the source code where the breakpoint occurred
// frame variable shows the current variables, and their values. Note that the variables have not been initialized, so they have strange values!
// p nCount will print the current value in nCount
// p nValues shows all the values in the array nValues

// Enter n (or next) – this steps OVER the next command. This stepped over the cout command – if we had entered s, it would have started showing the execution of the cout function call, which is not what we want. Note after we entered the n, it showed the output (“Enter five numbers:”) to the screen. We were stopped BEFORE the line executed, so by single stepping, we caused the computer to execute that one line. Nothing else has changed (frame variable, bt, etc. are the same), so let’s press n again.

// Now the cout statement inside the for loop is the current line. Also notice that now the nCount variable (via frame variable or print nCount) has a value - it is zero, because that’s where our for loop begins. Press n again. The prompt for the next number is displayed, since the cout statement has executed. Step through another line of code.

// The code is now stopped on the cin statement. You will need to enter a value and press enter.

// You should see these changes:

// The number you typed shows after the prompt.
// frame variable shows that the 2 was entered into the array at index 1 (not 0!)