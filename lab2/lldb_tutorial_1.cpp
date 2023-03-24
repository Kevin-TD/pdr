// https://uva-cs.github.io/pdr/tutorials/02-lldb/index.html
// LLDB command summary https://uva-cs.github.io/pdr/docs/lldb_summary.html 
// GDB vs LLDB https://uva-cs.github.io/pdr/docs/gdb_vs_lldb.html 


#include <iostream>
using namespace std;

void my_subroutine() {
    cout << "Hello world" << endl;
}

int main() {
    int x = 4;
    int *p = NULL;
    my_subroutine();
    *p = 3;
    cout << x << ", " << *p << endl;
    return 0;
}

// Programs normally have to be compiled with a special option to allow debugging to take place. On UNIX, the option for clang++ is the -g option. For example:
// clang++ prog1.cpp -Wall -g
// We also include the -Wall option, which lists warnings (the ‘all’ is to list all warnings).
// The -g option (short for --debug) causes the compiler to include information about the source file (the .cpp file) that is needed for debugging as part of the executable file. This causes the executable to be larger in size, and slightly slower, but allows for debugging. So when you run the debugger, you specify the executable file (not the source file) as the input to the debugger.

// The LLVM C++ compiler, clang, has an accompanying debugger: lldb. To run the command-line version, compile your program as described above, and then type:
// lldb a.out

// Once in lldb, use the run command to start your program running. It will run until it completes, until it crashes, or until it reaches a breakpoint that you set (more on this later) – and it will pause for input, of course. Once it finishes, you’re still in lldb, so you can run it again from the beginning.

/* If your program requires command-line arguments, you can give them after the run command. If you would normally run the program on the command line by entering:

./a.out 100 test1.dat
In the debugger, you would enter:

run 100 test1.dat */

// When you run a program inside a debugger, you can easily see what the current line is when a program crashes. Type f to see the current and surrounding lines.

// More usefully, you can see a list of the function calls that led you to this point in your program. Your program may have died deep inside a function that is called many times in your program, and you need to know which sequence of nested functions calls led to the failure. In the command-line mode, type **bt** to show this list.
// IMPORTANT: this command is one of the most important and useful debugging commands you’ll see in this lesson!

// While we’re talking about reaching a point in a sequence of nested function calls, sometimes in lldb you will need to understand the concept of frames. When a program stops, you can examine local variables, view lines of code, etc. that are local to that function. If you need to move up to the function that called this one, you need to move up to the higher frame using the up command to debug there. The down command moves you back down a frame towards where you started. The up and down commands let you move up and down the calling stack (of nested function calls) so you can issue debug commands about the function that’s “active” at each level.

// Breakpoints
// One of the most fundamental things you want to do while debugging is make the program pause at a particular line or at the start of a function. These locations in a program where execution pauses are called “breakpoints”.
// IMPORTANT: You must choose a line of code that actually executes something: not a comment, for example.

// In lldb you can set breakpoints by typing either break or b followed by information on where you want the program to pause. After the b command, you can put either:
/*
a function name (e.g., b my_subroutine)
a line number (e.g., b 12)
either of the above preceded by a file name (e.g., b
prog1.cpp:12 or b prog1.cpp:my_subroutine) */ 

// At any time you can see information about all the breakpoints that have been defined by entering breakpoint list (or br list). You can remove a breakpoint using the breakpoint delete command (or just br del). You can delete all breakpoints (br del) or a specific one (br del 1 or br del my_subroutine).

// Breakpoints stick around until you delete them. This is handy if you put a breakpoint inside a function that is called more than once or if you put one inside a loop. You can set a temporary breakpoint with the tbreak command; the program pauses the first time, but after it pauses there, that breakpoint is cleared.

// An important thing to keep in mind with breakpoints is that if you set a breakpoint for line 12, then the program will pause BEFORE executing that line.



// Controlling Execution After a Breakpoint
// After you make your program pause, you may want to execute it line-by-line to see what it does next. There are two commands that make a program execute the next line and then pause again: next and step.
// The difference between these two is how they behave when the program reaches a function call. The step command steps into that function; in other words, you see the debugging session move into the called function. The next command steps over that function call, and you see the current line as the one after the function call. Both are useful, depending on what level of detail you need.
// Sometimes after you’ve hit a break point and are doing line-by-line execution, you want to resume normal execution until the next breakpoint is reached (or the program completes). The command to do this is continue. A useful variant on this is the finish command which finishes executing the current function and then pauses.
// You can use the abbreviations s, n and c for the common commands described in this section.


// Displaying Variables and Expressions
// Another thing you often want to do when the program pauses is to see what value a variable or an expression has. To do this, just type print or p followed by the variable name or expression. If the variable or expression is a pointer or an address, you can print the value that this address references using the print * command (i.e. print *foo). In addition, you can enter frame variable to see all the arguments and local variables (and their values) displayed.
// It is often handy to have the debugger automatically display one or more variable values at all times so you could watch how they change. You do this with the display <var> command, and lldb will display that variable’s value each time the program execution hits a breakpoint. You can use ‘display’ more than once to show multiple variables.
// To see info on all variables chosen for display, just enter display. To remove a variable from the automatic display list, use the undisplay command followed by the display variable’s numeric-id (entering display shows the variables’ numeric ids).



// Changing a Variable’s Value
// If you see that a variable has the wrong value, and you’d like to change that value in mid-stream before continuing execution, you can do this easily. Enter expr followed by the variable, an equals symbol (=), and the value or expression. It’s like a C++ assignment statement but without the semi-colon at the end. For example:
// expr x = 5
// The expression can be any C++ expression, including a function call. So a statement like this is legal:
// expr y = countNegValues(list, num)

// Sometimes you want to actually execute a function “by hand” while the program is stopped, even if this function isn’t what would normally be called at this point in the code. You can do this using the set command as shown above, or by making the function call the argument to the print command. For example, you could type:
// print initQueue(&myQueue)
// And the function would be called right now while the program is paused. This works even if the function returns void.