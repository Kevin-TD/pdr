/*
 * Filename: ListNode.h
 * Description: ListNode class definition
 */

#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

// next line needed because NULL is part of std namespace
using namespace std;

template <class T> 
class ListNode {
public:
    ListNode();         // Constructor

private:
    T value;          // The value of the node!
    ListNode* next;     // The next ListNode in the List
    ListNode* previous; // The previous ListNode in the list

    // List needs access to value, next, and previous
    template <class U> 
    friend class List;

    // ListItr needs access to value
    template <class U> friend class ListItr;

    // Not writing a destructor is fine in this case since there is no
    // dynamically allocated memory in this class.
};

template <class T> 
ListNode<T>::ListNode() {
    
}

#endif
