#ifndef AVL_H
#define AVL_H

#include <string>
#include "AVLNode.h"
#include <stack>

using namespace std;

// You do not need to know how Trunk works.
struct Trunk {
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    // insert finds a position for x in the tree and places it there, rebalancing
    // as necessary.
    void insert(const string& x);
    // remove finds x's position in the tree and removes it, rebalancing as
    // necessary.
    void remove(const string& x);
    // printTree pretty-prints the tree to aid debugging.
    void printTree();

    // pathTo finds x in the tree and returns a string representing the path it
    // took to get there.
    string pathTo(const string& x) const;
    // find determines whether or not x exists in the tree.
    bool find(const string& x) const;
    // numNodes returns the total number of nodes in the tree.
    int numNodes() const;

private:
    // Declare a root node
    AVLNode* root;

    // private helper for remove to allow recursion over different nodes. returns
    // an AVLNode* that is assigned to the original node.
    AVLNode* remove(AVLNode*& n, const string& x);
    // min finds the string with the smallest value in a subtree.
    string min(AVLNode* node) const;
    // height returns the value of the height field in a node. If the node is
    // null, it returns -1.
    int height(AVLNode* node) const;

    // private helper for printTree to allow recursion over different nodes.
    void printTree(AVLNode* root, Trunk* prev, bool isRight);

    // Any other methods you need...
    int numNodes(AVLNode* node) const; 
	
	// sets deepestImbalance; null if none
    // typically i would make this be something that returns an AVLNode* but i came across the most bizarre seg fault of my entire C++ programming career where a seg fault occurred after i returned a value and before the code came back to the code invocation site; and i was trying to debug this but lldb had some fatal error over comparing two integers ("balance <= -2")    and it was just ???? 
    // but making a string that grabs the return value directly instead of returning it from a function works so i'm just going to with that 
	void setDeepestImbalance(AVLNode* node); 
	
	// sets heights of each node
	void setHeights(AVLNode* node); 
	
	int getNodeHeight(AVLNode* node); 

    string deepestImbalance;
    string recentInsertionOrDeletion; 

    void balanceTree();
    void balanceTreeDeletion(); 

    stack<bool> directionsTo(const string& x, AVLNode* startingPoint)  const;

    AVLNode* nodeOf(const string& x) const;

    AVLNode* makeCopy(AVLNode* node); 

    int getBalance(AVLNode* node);
};

// max returns the greater of two integers.
int max(int a, int b);

#endif
