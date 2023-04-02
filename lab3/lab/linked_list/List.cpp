#include "List.h"
#include "ListNode.h"

// wa | clang++ -I /linked_list List.cpp ListItr.cpp ListNode.cpp ListTest.cpp -fsanitize=address -fno-omit-frame-pointer -g; ./a.out

// cpp files emptied as separating templated classes into .cpp and .h just does not work well; leads into unrecognized architecture errors/linkage errors 
// all impl details in .h files 