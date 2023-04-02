#ifndef SLL_H
#define SLL_H

#include "linked_list/List.h"
#include <iostream> 

template <class T> 
class StackLinkedList {
public:
	// constructor
	StackLinkedList(); 
	
	// pushes new element to top of stack	
	void push(T e);

	// removes top element off stack
	void pop(); 
	
	// gets top of stack 
	T top(); 

	// returns true if stack is empty
	bool empty(); 
	
	// returns size
	int getSize(); 

	void printStack(); 
private: 
	List<T> internalList; 
	int size; 
};

template <class T>
StackLinkedList<T>::StackLinkedList() {
	size = 0; 	
}

template <class T> 
void StackLinkedList<T>::push(T e) {
	if (size == 0)
		internalList.insertAtTail(e); 
	else
		internalList.insertBefore(e, internalList.first()); 
	size++; 
}

template <class T>
void StackLinkedList<T>::pop() {
	internalList.remove(internalList.first().retrieve());
	size--; 
}

template <class T>
T StackLinkedList<T>::top() {
	return internalList.first().retrieve(); 
}

template <class T>
bool StackLinkedList<T>::empty() { 
	return (size == 0); 
}

template <class T>
int StackLinkedList<T>::getSize() {
	return size; 
}

template <class T>
void StackLinkedList<T>::printStack() { 
	printList(internalList, true); 
}

#endif
