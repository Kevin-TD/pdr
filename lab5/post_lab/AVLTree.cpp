#include "AVLNode.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
#include <stack> 
using namespace std;

AVLTree::AVLTree() {
    root = NULL;
	deepestImbalance = "?"; 
}

AVLTree::~AVLTree() {
    delete root;
    root = NULL;
}

template <class T>
void reverseStack(stack<T>& s)
{
   T item;
   stack<T> tmpStack;

   while (!s.empty())
   {
      item = s.top();
      s.pop();
      tmpStack.push(item);
   }


   s = tmpStack;
   return;
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) {
    // YOUR IMPLEMENTATION GOES HERE	
	// TODO: HEIGHT, THEN CALL BALANCE 	
	
	if (find(x)) return; // prevents duplicates 

	AVLNode* newNode = new AVLNode();
	newNode->value = x;
		
	if (root == NULL) {
		root = newNode;  
		return; 
	}
	
	AVLNode* currentNode = root; 

	while (true) {
		cout << "f5\n";
		if (x > currentNode->value) {
			// right child
			if (currentNode->right == NULL) {
				currentNode->right = newNode; 
				currentNode->right->parent = currentNode; 
				break;  
			} 
			else {
				currentNode = currentNode->right;
			}
		}
		else {
			// left child
			if (currentNode->left == NULL) {
				currentNode->left = newNode;
				currentNode->left->parent = currentNode; 
				break;   
			}
			else {
				currentNode = currentNode->left;
			}
		}
		
	}
	
	setHeights(root);
	setDeepestImbalance(root);
	cout << "imbal = " << deepestImbalance << endl; 

	// no imbalance
	if (deepestImbalance == "?") return; 

	cout << "f1\n";
	stack<bool> directions = directionsTo(x);
	cout << "f2\n";
	AVLNode* deepestImbalanceNode = nodeOf(deepestImbalance); 


	bool rot2 = directions.top();
	directions.pop(); 
	bool rot1 = directions.top();
	
	printTree();
	
	// right right 
	if (rot1 && rot2) {
		

		AVLNode* a = nodeOf(deepestImbalance);  
		AVLNode* _a = a;
		// makeCopy(deepestImbalance) 
		
		cout << "OG TREE\n";
		printTree(a, NULL, false);
		cout << "COPY TREE\n";
		printTree(_a, NULL, false);
				
		a = _a->right;
		a->left = _a;
		a->right = _a->right->right;
		a->right->right = _a->right->right->right; 
		a->right->left = _a->right->right->left;
		a->left->left = _a->left; 
		a->left->right = _a->right->left; 
	
		a->left->parent = a;
		a->right->parent = a;
		a->parent = NULL;  

		if (a->right->right != NULL) a->right->right->parent = a->right; 
		if (a->right->left != NULL) a->right->left->parent = a->right; 
		if (a->left->left != NULL) a->left->left->parent = a->left; 
		if (a->left->right != NULL) a->left->right->parent = a->left; 	
		cout << "TEST: " << a->left->parent->value << endl; 
		
		cout << "POST OG TREE\n";
		printTree(a, NULL, false); 
		cout << "POST COPY TREE\n";
		printTree(_a, NULL, false); 
	
	}
	// right left 
	else if (rot1 && !rot2) {
		
	}
	// left right 
	else if (!rot1 && rot2) {
		
	}
	// left left 
	else if (!rot1 && !rot2) {
		
	}

}

AVLNode* AVLTree::makeCopy(AVLNode* node) {
	AVLNode* cpy = new AVLNode(); 
	if (node == NULL) return cpy;

	cpy->value = node->value; 
	cpy->height = node->height;
	cpy->parent = node->parent;  
	if (node->left != NULL) cpy->left = makeCopy(node->left); 
	if (node->right != NULL) cpy->right = makeCopy(node->right); 

	return cpy;
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) {
    root = remove(root, x);
}

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string& x) const {
    // YOUR IMPLEMENTATION GOES HERE
	string pathTaken;  
	
	if (root == NULL) return ""; 	
	
	pathTaken = root->value + " "; 

	if (x == root->value ) {
		return pathTaken; 
	}
	
	AVLNode* currentNode = root;
	

	while (true) {
		if (x > currentNode->value) {
			// right child
			if (currentNode->right != NULL) {
				pathTaken += currentNode->right->value + " ";
				
				if (currentNode->right->value == x) {
					return pathTaken;
				}
				else {
					currentNode = currentNode->right; 
				}
			} 
			else {
				return ""; 
			}
		}
		else {
			// left child
			if (currentNode->left != NULL) {
				pathTaken += currentNode->left->value + " ";

				if (currentNode->left->value == x) {
					return pathTaken; 
				}
				else {
				currentNode = currentNode->left; 
				}
			}
			else {
				return ""; 
			}
		}
	}
	
	return ""; 
}


AVLNode* AVLTree::nodeOf(const string& x) const {
	AVLNode* dummy = new AVLNode(); 
	
	if (root == NULL) return dummy; 

	if (x == root->value ) {
		return root; 
	}
	
	AVLNode* currentNode = root;
	

	while (true) {
		if (x > currentNode->value) {
			// right child
			if (currentNode->right != NULL) {
				
				if (currentNode->right->value == x) {
					return currentNode;
				}
				else {
					currentNode = currentNode->right; 
				}
			} 
			else {
				return dummy;
			}
		}
		else {
			// left child
			if (currentNode->left != NULL) {
				
				if (currentNode->left->value == x) {
					return currentNode; 
				}
				else {
				currentNode = currentNode->left; 
				}
			}
			else {
				return dummy;
			}
		}
	}
	
	return dummy; 
}
// 0 = left, 1 = right 
// stops after it's filled by 2 because that's all thats needed for our impl 
stack<bool> AVLTree::directionsTo(const string& x) const {
    // YOUR IMPLEMENTATION GOES HERE
	stack<bool> leftRightTurnsTaken;  
	stack<bool> dummy; 
	
	if (root == NULL) return dummy;

	if (x == root->value) {
		return dummy; 
	}
	
	AVLNode* currentNode = root;
	

	while (true) {
		if (leftRightTurnsTaken.size() == 2) return leftRightTurnsTaken;

		if (x > currentNode->value) {
			// right child
			if (currentNode->right != NULL) {
				leftRightTurnsTaken.push(true);
				
				if (currentNode->right->value == x) {
					return leftRightTurnsTaken;
				}
				else {
					currentNode = currentNode->right; 
				}
			} 
			else {
				return dummy;
			}
		}
		else {
			// left child
			if (currentNode->left != NULL) {
				leftRightTurnsTaken.push(false);

				if (currentNode->left->value == x) {
					return leftRightTurnsTaken; 
				}
				else {
					currentNode = currentNode->left; 
				}
			}
			else {
				return dummy;
			}
		}
	}
	
	return dummy; 
}




// find determines whether or not x exists in the tree.
bool AVLTree::find(const string& x) const {
    // YOUR IMPLEMENTATION GOES HERE
    if (root == NULL) return false;  	
	
	if (x == root->value ) {
		return true; 
	}
	
	AVLNode* currentNode = root;
	

	while (true) {
		if (x > currentNode->value) {
			// right child
			if (currentNode->right != NULL) {
				if (currentNode->right->value == x) {
					return true;
				}
				else {
					currentNode = currentNode->right; 
				}
			} 
			else {
				return false; 
			}
		}
		else {
			// left child
			if (currentNode->left != NULL) {
				if (currentNode->left->value == x) {
					return true;
				}
				else {
					currentNode = currentNode->left; 
				}
			}
			else {
				return false; 
			}
		}
	}

}

int AVLTree::numNodes(AVLNode* node) const {
	if (node == NULL) return 0; 

	int total = 0;
	
	if (node == root) total++; 
	if (node->left != NULL) total++; 
	if (node->right != NULL) total++; 

	return total + numNodes(node->left) + numNodes(node->right); 
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const {
	return numNodes(root); 	
}


void AVLTree::setDeepestImbalance(AVLNode* node) {
	AVLNode* dummy = new AVLNode(); 
	if (numNodes() <= 2) return; 

	int leftHeight = 0;
	int rightHeight = 0; 

	if (node->left != NULL) {
		leftHeight = node->left->height; 
	}
	if (node->right != NULL) {
		 rightHeight = node->right->height;
	}

	int balanceFactor = leftHeight - rightHeight;  
	
	// go right 	
	if (balanceFactor <= -2) {
		setDeepestImbalance(node->right); 
	}
	// go left 	
	else if (balanceFactor >= 2) {
		setDeepestImbalance(node->left); 
	}
	// too far
	else {
		deepestImbalance = node->parent->value;
	}

	
	
}

int AVLTree::getNodeHeight(AVLNode* node) {
	if (node == NULL) return 0; 
	int leftHeight = getNodeHeight(node->left);
	int rightHeight = getNodeHeight(node->right); 
	return 1 + max(leftHeight, rightHeight); 	
}

void AVLTree::setHeights(AVLNode* node) {
	if (node == NULL) return;

	node->height = getNodeHeight(node); 

	if (node->left != NULL) {
		node->left->height = getNodeHeight(node->left); 
		setHeights(node->left); 
	}
	if (node->right != NULL) {
		node->right->height = getNodeHeight(node->right); 
		setHeights(node->right); 
	}
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode*& n) {
    // YOUR IMPLEMENTATION GOES HERE
}

// rotateLeft performs a single rotation on node n with its right child.
AVLNode* AVLTree::rotateLeft(AVLNode*& n) {
    // YOUR IMPLEMENTATION GOES HERE
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode* AVLTree::rotateRight(AVLNode*& n) {
    // YOUR IMPLEMENTATION GOES HERE
}

// private helper for remove to allow recursion over different nodes.
// Returns an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
    if (n == NULL) {
        return NULL;
    }

    // first look for x
    if (x == n->value) {
        // found
        if (n->left == NULL && n->right == NULL) {
            // no children
            delete n;
            n = NULL;
            return NULL;
        } else if (n->left == NULL) {
            // Single child (left)
            AVLNode* temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        } else if (n->right == NULL) {
            // Single child (right)
            AVLNode* temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        } else {
            // two children -- tree may become unbalanced after deleting n
            string sr = min(n->right);
            n->value = sr;
            n->right = remove(n->right, sr);
        }
    } else if (x < n->value) {
        n->left = remove(n->left, x);
    } else {
        n->right = remove(n->right, x);
    }

    // Recalculate heights and balance this subtree
    n->height = 1 + max(height(n->left), height(n->right));
    balance(n);

    return n;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode* node) const {
    // go to bottom-left node
    if (node->left == NULL) {
        return node->value;
    }
    return min(node->left);
}

// height returns the value of the height field in a node.
// If the node is null, it returns -1.
int AVLTree::height(AVLNode* node) const {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// max returns the greater of two integers.
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Helper function to print branches of the binary tree
// You do not need to know how this function works.
void showTrunks(Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode* root, Trunk* prev, bool isRight) {
    if (root == NULL) return;

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight) {
        trunk->str = ".---";
        prev_str = "   |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->value << " " << root->height << endl;

    if (prev) prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);

    delete trunk;
}

void AVLTree::printTree() {
    printTree(root, NULL, false);
}
