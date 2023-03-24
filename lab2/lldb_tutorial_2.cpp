// LLDB command summary https://uva-cs.github.io/pdr/docs/lldb_summary.html
// GDB vs LLDB https://uva-cs.github.io/pdr/docs/gdb_vs_lldb.html 
// ill be using LLDB 

// When a program crashes, you can see the list of subroutine calls that led to that point via the bt command. This prints a stack trace, similar to what Java prints when an exception is thrown (but not caught). Each level in that stack trace is called a frame. Sometimes you may want to look at the variables and what-not a few frames up. To do so, you enter the frame command. Consider the following program:

#include <iostream>
using namespace std;
void recurse(int x) {
  int *y = NULL;
  if ( x == 0 )
    cout << *y << endl;
  recurse(x-1);
}
int main() {
  recurse(5);
  return 0;
}

/*This program will crash on the 5th recursive call to recurse(). If this program is compiled (remember to compile it with -g) and run through the debugger, it will crash, and the resulting stack trace looks like the following:

(lldb) bt
* thread #1: tid = 31030, 0x000000000040084a frame`recurse(x=0) + 29 at frame.cpp:6, name = 'frame', stop reason = invalid address (fault address: 0x0)
  * frame #0: 0x000000000040084a frame`recurse(x=0) + 29 at frame.cpp:6
    frame #1: 0x0000000000400872 frame`recurse(x=1) + 69 at frame.cpp:7
    frame #2: 0x0000000000400872 frame`recurse(x=2) + 69 at frame.cpp:7
    frame #3: 0x0000000000400872 frame`recurse(x=3) + 69 at frame.cpp:7
    frame #4: 0x0000000000400872 frame`recurse(x=4) + 69 at frame.cpp:7
    frame #5: 0x0000000000400872 frame`recurse(x=5) + 69 at frame.cpp:7
    frame #6: 0x0000000000400882 frame`main + 14 at frame.cpp:10
    frame #7: 0x00007f971522fec5 libc.so.6`__libc_start_main(main=0x0000000000400874, argc=1, argv=0x00007fff5a68bf08, init=<unavailable>, fini=<unavailable>, rtld_fini=<unavailable>, stack_end=0x00007fff5a68bef8) + 245 at libc-start.c:287
(lldb) */

// The frames are listed on the left-hand side, and you are in frame #0 by default (it states this in some of the lldb output that was not included above). You can enter up and down to move to different frames. You can then examine the contents of the variables in that frame before moving on.

