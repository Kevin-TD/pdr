/*
 * Filename: ListItr.h
 * Description: ListItr class definition
 */
#ifndef LISTITR_H
#define LISTITR_H

#include "ListNode.h"
#include "List.h"

template <class T> 
class ListItr {
public:
    // Constructors
    ListItr();
    ListItr(ListNode<T>* theNode);

    // Returns true if the iterator is currently pointing past the end position
    // in the list (i.e., it's pointing to the dummy tail), else false
    bool isPastEnd() const;

    // Returns true if the iterator is currently pointing past (before) the first position
    // in list (i.e., it's pointing to the dummy head), else false
    bool isPastBeginning() const;

    // Advances `current` to the next position in the list (unless already past the end of the list)
    void moveForward();

    // Moves `current` back to the previous position in the list (unless already past the beginning of the list)
    void moveBackward();

    // Returns the value of the item in the current position of the list
    T retrieve() const;

private:
    ListNode<T>* current; // Holds the position in the list

    template <class U>
    friend class List; // List class needs access to "current"
};

template <class T> 
ListItr<T>::ListItr() {

}

template <class T> 
ListItr<T>::ListItr(ListNode<T>* theNode) {
    current = theNode; 
}

// Returns true if the iterator is currently pointing past the end position
// in the list (i.e., it's pointing to the dummy tail), else false
template <class T> 
bool ListItr<T>::isPastEnd() const {
    return current->next == NULL;
}


// Returns true if the iterator is currently pointing past (before) the first position
// in list (i.e., it's pointing to the dummy head), else false
template <class T> 
bool ListItr<T>::isPastBeginning() const {
    return current->previous == NULL;
}

// Advances `current` to the next position in the list (unless already past the end of the list)
template <class T> 
void ListItr<T>::moveForward() {
    if (!isPastEnd()) 
        current = current->next; 
}

// Moves `current` back to the previous position in the list (unless already past the beginning of the list)
template <class T> 
void ListItr<T>::moveBackward() {
    if (!isPastBeginning()) 
        current = current->previous; 
}

// Returns the value of the item in the current position of the list
template <class T> 
T ListItr<T>::retrieve() const {
    return current->value;
}

#endif
