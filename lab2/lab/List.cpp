#include "List.h"
#include "ListNode.h"

// clang++ List.cpp ListItr.cpp ListNode.cpp ListTest.cpp -fsanitize=address -fno-omit-frame-pointer -g; ./a.out

// The default constructor.
// It should initialize all private data members
// and set up the basic list structure with the dummy head and tail nodes.
List::List() {
    /*ListNode* head;       // Dummy node representing the beginning of the list
    ListNode* tail;       // Dummy node representing the end of the list
    int count;            // Number of elements in the list*/
    head = new ListNode();
    tail = new ListNode(); 

    head->next = tail; 
    tail->previous = head; 

    head->previous = NULL; 
    tail->next = NULL; 
    
    count = 0;
}

// The copy constructor.
// It should create a **new** list of ListNodes whose contents
// are the same values as the ListNodes in `source`.
List::List(const List& source) {
    head = new ListNode(); 
    tail = new ListNode(); 

    head->next = tail; 
    tail->previous = head; 

    head->previous = NULL; 
    tail->next = NULL; 

    count = 0;

    ListItr sourceCurrent = source.head->next; 
    while (!sourceCurrent.isPastEnd()) {
        insertAtTail(sourceCurrent.current->value);
        sourceCurrent = sourceCurrent.current->next; 
    }
}

// The destructor.
// It should empty the list and reclaim the memory allocated in the constructor for head and tail.
List::~List() {
    makeEmpty(); 
    delete head; 
    delete tail; 
}

// The copy assignment operator.
// It should copy the contents of every ListNode in `source`
// into an **existing** list (the reference to the calling List object itself).
List& List::operator=(const List& source) {
    if (this == &source) return *this; 

    makeEmpty(); 
    ListItr current = source.head->next; 
    while (!current.isPastEnd()) {
        insertAtTail(current.current->value);
        current = current.current->next; 
    }
    return *this;
}

// Returns true if empty, else false
bool List::isEmpty() const {
    return count == 0; 
}

// Removes (deletes) all items except the dummy head/tail.
// The list should be a working empty list after this.
void List::makeEmpty() {
    if (isEmpty()) return; 

    ListNode* current = head; 
    ListNode* toDelete[count]; 

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


void List::insertAtTail(int x) {
    ListNode* newItem = new ListNode(); 
    newItem->value = x; 

    ListNode* prevPrevious = tail->previous; 

    tail->previous = newItem; 

    newItem->next = tail; 
    newItem->previous = prevPrevious; 

    prevPrevious->next = newItem; 
    
    count++;
}

// Returns an iterator that points to the first ListNode **after** the dummy head node (even on an empty list!)
ListItr List::first() {
    if (count == 0)
        return head; 
    return head->next;
}

// Returns an iterator that points to the last ListNode **before** the dummy tail node (even on an empty list!)
ListItr List::last() {
    if (count == 0)
        return tail; 
    return tail->previous;
}

// Inserts x after current iterator position
void List::insertAfter(int x, ListItr position) {
    ListNode* previousNext = position.current->next; 

    ListNode* newItem = new ListNode(); 
    newItem->value = x; 
    
    position.current->next = newItem; 
    
    previousNext->previous = newItem; 

    newItem->next = previousNext; 
    newItem->previous = position.current; 

    count++; 
}

// Inserts x before current iterator position
void List::insertBefore(int x, ListItr position) {
    ListNode* previousPrevious = position.current->previous; 

    ListNode* newItem = new ListNode(); 
    newItem->value = x; 

    position.current->previous = newItem; 

    previousPrevious->next = newItem; 

    newItem->next = position.current; 
    newItem->previous = previousPrevious;
}

// Returns an iterator that points to the first occurrence of x.
// When the parameter is not in the list, return a ListItr object that points to the dummy tail node.
// This makes sense because you can test the return from find() to see if isPastEnd() is true.
ListItr List::find(int x) {
    // search from head to tail 
    ListNode* current = head; 

    while (current->next != NULL) {
        if (current->value == x) 
            return ListItr(current); 
        current = current->next; 
    }

    return ListItr(tail); 
}

// Removes the first occurrence of x (head -> tail)
void List::remove(int x) {
    ListNode* current = head; 

    while (current->next != NULL) {
        if (current->value == x) {
            ListNode* prevPrevious = current->previous; 
            ListNode* prevNext = current->next; 

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
int List::size() const {
    return count; 
}

// printList: non-member function prototype
// prints list forwards (head -> tail) when forward is true
// or backwards (tail -> head) when forward is false
// You **must** use your ListItr class to implement this function!
void printList(List& source, bool forward) {
    if (source.isEmpty()) return; 

    if (forward) {
        ListItr firstEl = source.first(); 
        cout << "LL FWD: "; 

        while (!firstEl.isPastEnd()) {
            cout << firstEl.retrieve() << " "; 
            firstEl.moveForward();
        }

        cout << "\n";
        return;
    }

    // backward 
    ListItr lastEl = source.last(); 
    
    cout << "LL BWD: "; 

    while (!lastEl.isPastBeginning()) {
        cout << lastEl.retrieve() << " "; 
        lastEl.moveBackward();
    }

    cout << "\n";
}