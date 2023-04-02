// https://uva-cs.github.io/pdr/labs/lab02/index.html
// https://uva-cs.github.io/pdr/docs/readings.html
// https://en.wikibooks.org/wiki/Data_Structures/LinkedLists

/*
 * Filename: List.h
 * Description: List class definition
 * 	also includes the prototype for non-member function printList()
 */
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "ListNode.h"
#include "ListItr.h"
using namespace std;

// When reading in ListItr.h first, it starts reading in this file
// before declaring that ListItr is a class.  This file then include
// ListItr.h, but beacuse of the #ifndef LISTITR_H statement, the code
// in that file is not read.  Thus, in this case, this List.h file
// will be read in, and will not know that ListItr is a class, which
// will cause compilation problems later on in this file.  Got it?
// Isn't C++ fun???
template <class T> 
class ListItr;

template <class T> 
class List {
public:
    // The default constructor.
    // It should initialize all private data members
    // and set up the basic list structure with the dummy head and tail nodes.
    List();

    // The copy constructor.
    // It should create a **new** list of ListNodes whose contents
    // are the same values as the ListNodes in `source`.
    List(const List& source);

    // The destructor.
    // It should empty the list and reclaim the memory allocated in the constructor for head and tail.
    ~List();

    // The copy assignment operator.
    // It should copy the contents of every ListNode in `source`
    // into an **existing** list (the reference to the calling List object itself).
    List& operator=(const List& source);

    // Returns true if empty, else false
    bool isEmpty() const;

    // Removes (deletes) all items except the dummy head/tail.
    // The list should be a working empty list after this.
    void makeEmpty();

    // Returns an iterator that points to the first ListNode **after** the dummy head node (even on an empty list!)
    ListItr<T> first();

    // Returns an iterator that points to the last ListNode **before** the dummy tail node (even on an empty list!)
    ListItr<T> last();

    // Inserts x after current iterator position
    void insertAfter(T x, ListItr<T> position);

    // Inserts x before current iterator position
    void insertBefore(T x, ListItr<T> position);

    // Inserts x at tail of list
    void insertAtTail(T x);

    // Returns an iterator that points to the first occurrence of x.
    // When the parameter is not in the list, return a ListItr object that points to the dummy tail node.
    // This makes sense because you can test the return from find() to see if isPastEnd() is true.
    ListItr<T> find(T x);

    // Removes the first occurrence of x
    void remove(T x);

    // Returns the number of elements in the list
    int size() const;

private:
    ListNode<T>* head;       // Dummy node representing the beginning of the list
    ListNode<T>* tail;       // Dummy node representing the end of the list
    int count;            // Number of elements in the list
};

template <class T> 
List<T>::List() {
    /*ListNode* head;       // Dummy node representing the beginning of the list
    ListNode* tail;       // Dummy node representing the end of the list
    int count;            // Number of elements in the list*/
    head = new ListNode<T>();
    tail = new ListNode<T>(); 

    head->next = tail; 
    tail->previous = head; 

    head->previous = NULL; 
    tail->next = NULL; 
    
    count = 0;
}

// The copy constructor.
// It should create a **new** list of ListNodes whose contents
// are the same values as the ListNodes in `source`.
template <class T> 
List<T>::List(const List<T>& source) {
    head = new ListNode<T>(); 
    tail = new ListNode<T>(); 

    head->next = tail; 
    tail->previous = head; 

    head->previous = NULL; 
    tail->next = NULL; 

    count = 0;

    ListItr<T> sourceCurrent = source.head->next; 
    while (!sourceCurrent.isPastEnd()) {
        insertAtTail(sourceCurrent.current->value);
        sourceCurrent = sourceCurrent.current->next; 
    }
}

// The destructor.
// It should empty the list and reclaim the memory allocated in the constructor for head and tail.
template <class T> 
List<T>::~List() {
	
    makeEmpty(); 
    delete head; 
    delete tail; 
}

// The copy assignment operator.
// It should copy the contents of every ListNode in `source`
// into an **existing** list (the reference to the calling List object itself).
template <class T> 
List<T>& List<T>::operator=(const List& source) {
    if (this == &source) return *this; 

    makeEmpty(); 
    ListItr<T> current = source.head->next; 
    while (!current.isPastEnd()) {
        insertAtTail(current.current->value);
        current = current.current->next; 
    }
    return *this;
}

// Returns true if empty, else false
template <class T> 
bool List<T>::isEmpty() const {
    return count == 0; 
}

// Removes (deletes) all items except the dummy head/tail.
// The list should be a working empty list after this.
template <class T> 
void List<T>::makeEmpty() {
    if (isEmpty()) return; 

    ListNode<T>* current = head; 
    ListNode<T>* toDelete[count]; 

    int iterator = 0; 
    while (current->next->next != NULL) {
        current = current->next;
        toDelete[iterator] = current;
        iterator++; 
    }

    for (int i = 0; i < count; i++) {
        delete toDelete[i];
    }

    head->next = tail; 
    tail->previous = head; 

    count = 0; 
}

template <class T> 
void List<T>::insertAtTail(T x) {
    ListNode<T>* newItem = new ListNode<T>(); 
    newItem->value = x; 

    ListNode<T>* prevPrevious = tail->previous; 

    tail->previous = newItem; 

    newItem->next = tail; 
    newItem->previous = prevPrevious; 

    prevPrevious->next = newItem; 
    
    count++;
}

// Returns an iterator that points to the first ListNode **after** the dummy head node (even on an empty list!)
template <class T> 
ListItr<T> List<T>::first() {
    if (count == 0)
        return head; 
    return head->next;
}

// Returns an iterator that points to the last ListNode **before** the dummy tail node (even on an empty list!)
template <class T> 
ListItr<T> List<T>::last() {
    if (count == 0)
        return tail; 
    return tail->previous;
}

// Inserts x after current iterator position
template <class T> 
void List<T>::insertAfter(T x, ListItr<T> position) {
    ListNode<T>* previousNext = position.current->next; 

    ListNode<T>* newItem = new ListNode<T>(); 
    newItem->value = x; 
    
    position.current->next = newItem; 
    
    previousNext->previous = newItem; 

    newItem->next = previousNext; 
    newItem->previous = position.current; 

    count++; 
}

// Inserts x before current iterator position
template <class T> 
void List<T>::insertBefore(T x, ListItr<T> position) {
    ListNode<T>* previousPrevious = position.current->previous; 

    ListNode<T>* newItem = new ListNode<T>(); 
    newItem->value = x; 

    position.current->previous = newItem; 

    previousPrevious->next = newItem; 

    newItem->next = position.current; 
    newItem->previous = previousPrevious;
	
	count++; 
}

// Returns an iterator that points to the first occurrence of x.
// When the parameter is not in the list, return a ListItr object that points to the dummy tail node.
// This makes sense because you can test the return from find() to see if isPastEnd() is true.
template <class T> 
ListItr<T> List<T>::find(T x) {
    // search from head to tail 
    ListNode<T>* current = head; 

    while (current->next != NULL) {
        if (current->value == x) 
            return ListItr<T>(current); 
        current = current->next; 
    }

    return ListItr<T>(tail); 
}

// Removes the first occurrence of x (head -> tail)
template <class T> 
void List<T>::remove(T x) {
    ListNode<T>* current = head; 

    while (current->next != NULL) {
        if (current->value == x) {
            ListNode<T>* prevPrevious = current->previous; 
            ListNode<T>* prevNext = current->next; 

            prevPrevious->next = prevNext; 
            prevNext->previous = prevPrevious; 

            delete current; 
            count--;
            return; 
            
        }
        current = current->next; 
    }

}

// Returns the number of elements in the list
template <class T> 
int List<T>::size() const {
    return count; 
}

// printList: non-member function prototype
// prints list forwards (head -> tail) when forward is true
// or backwards (tail -> head) when forward is false
// You **must** use your ListItr class to implement this function!
template <class T> 
void printList(List<T>& source, bool forward) {
    if (source.isEmpty()) return; 

    if (forward) {
        ListItr<T> firstEl = source.first(); 
        cout << "LL FWD: "; 

        while (!firstEl.isPastEnd()) {
            cout << firstEl.retrieve() << " "; 
            firstEl.moveForward();
        }

        cout << "\n";
        return;
    }

    // backward 
    ListItr<T> lastEl = source.last(); 
    
    cout << "LL BWD: "; 

    while (!lastEl.isPastBeginning()) {
        cout << lastEl.retrieve() << " "; 
        lastEl.moveBackward();
    }

    cout << "\n";
}

#endif