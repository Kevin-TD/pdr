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

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) {
    // YOUR IMPLEMENTATION GOES HERE	
	// TODO: HEIGHT, THEN CALL BALANCE 	
	
	if (find(x)) return; // prevents duplicates 

	recentInsertionOrDeletion = x; 

	AVLNode* newNode = new AVLNode();
	newNode->value = x;
		
	if (root == NULL) {
		root = newNode;  
		return; 
	}
	
	AVLNode* currentNode = root; 

	while (true) {
		if (x > currentNode->value) {
			// right child
			if (currentNode->right == NULL) {
				currentNode->right = newNode; 
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
				break;   
			}
			else {
				currentNode = currentNode->left;
			}
		}
		
	}
	
	setHeights(root);
	setDeepestImbalance(root);

	// no imbalance
	if (deepestImbalance == "?") return; 


	balanceTree(); 
}



void AVLTree::balanceTree() {
	// deepest imbalance node 
	AVLNode* diNode = nodeOf(deepestImbalance); 
	// useful later for flipping trees 
	AVLNode* diNodeCopy = makeCopy(diNode); 

	//  determines rotation type 
	stack<bool> directions = directionsTo(recentInsertionOrDeletion, diNode);

	bool rot2 = directions.top();
	directions.pop(); 
	bool rot1 = directions.top();
	
	// tree balancing 

	// right right 
	if (rot1 && rot2) {
		/*
				a 
			   / \
			  A   b
			 	 / \      
				B	c
				   / \
				  C   D
		perform single rotate left 
		similar idea for rest of rotations 
		
		*/
		string a = diNodeCopy->value;
		string b = diNodeCopy->right->value;
		string c = diNodeCopy->right->right->value; 
		AVLNode* A = diNodeCopy->left;
		AVLNode* B = diNodeCopy->right->left;
		AVLNode* C = diNodeCopy->right->right->left;
		AVLNode* D = diNodeCopy->right->right->right; 

		diNode->value = b; 
		diNode->right->value = c; 

		if (diNode->left == NULL) diNode->left = new AVLNode(); 
		diNode->left->value = a; 

		diNode->left->left = A;
		diNode->left->right = B; 
		diNode->right->left = C; 
		diNode->right->right = D; 	

	}
	// right left 
	else if (rot1 && !rot2) {
		string a = diNodeCopy->value;
		string b = diNodeCopy->right->value;
		string c = diNodeCopy->right->left->value; 
		AVLNode* A = diNodeCopy->left;  			
		AVLNode* B = diNodeCopy->right->left->left;
		AVLNode* C = diNodeCopy->right->left->right; 
		AVLNode* D = diNodeCopy->right->right; 

		diNode->value = c; 
		diNode->right->value = b; 

		if (diNode->left == NULL) diNode->left = new AVLNode(); 
		diNode->left->value = a; 
		
		diNode->left->left = A;
		diNode->left->right = B; 
		diNode->right->left = C; 
		diNode->right->right = D; 

	}
	// left right 
	else if (!rot1 && rot2) {
		string a = diNodeCopy->value;
		string b = diNodeCopy->left->value; 
		string c = diNodeCopy->left->right->value; 
		AVLNode* A = diNodeCopy->right;			
		AVLNode* B = diNodeCopy->left->left; 
		AVLNode* C = diNodeCopy->left->right->left; 
		AVLNode* D = diNodeCopy->left->right->right; 

		diNode->value = c;
		diNode->left->value = b; 

		if (diNode->right == NULL) diNode->right = new AVLNode(); 
		diNode->right->value = a; 

		diNode->left->left = B;
		diNode->left->right = C; 
		diNode->right->left = D; 
		diNode->right->right = A; 

	}
	// left left 
	else if (!rot1 && !rot2) {
		string a = diNodeCopy->value; 
		string b = diNodeCopy->left->value; 
		string c = diNodeCopy->left->left->value; 
		AVLNode* A = diNodeCopy->right;			
		AVLNode* B = diNodeCopy->left->right; 
		AVLNode* C = diNodeCopy->left->left->right; 
		AVLNode* D = diNodeCopy->left->left->left; 

		diNode->value = b;
		diNode->left->value = c; 

		if (diNode->right == NULL) diNode->right = new AVLNode(); 
		diNode->right->value = a; 

		diNode->left->left = D;
		diNode->left->right = C; 
		diNode->right->left = B; 
		diNode->right->right = A; 

	}
	
	deepestImbalance = "?";
	setHeights(root);
	
}

void AVLTree::balanceTreeDeletion() {
	AVLNode* diNode = nodeOf(deepestImbalance); 
	// useful later for flipping trees 
	AVLNode* diNodeCopy = makeCopy(diNode); 
	
	bool rot1, rot2; 

	// determining rotation type 

	// left left 
	if (getBalance(diNode) > 1 && getBalance(root->left)) {
		rot1 = false, rot2 = false; 
	}
	// Left Right Case
	else if (getBalance(diNode) > 1 && getBalance(root->left) < 0){
		rot1 = false, rot2 = true; 
	}

	// Right Right Case
	else if (getBalance(diNode) < -1 && getBalance(root->right) <= 0) {
		rot1 = true, rot2 = true; 
	}

	// Right Left Case
	else if (getBalance(diNode) < -1 && getBalance(root->right) > 0){
		rot1 = true, rot2 = false; 
	}



	// tree balancing 

	// right right 
	if (rot1 && rot2) {
		/*
				a 
			   / \
			  A   b
			 	 / \      
				B	c
				   / \
				  C   D
		perform single rotate left 
		similar idea for rest of rotations 
		
		*/
		string a = diNodeCopy->value;
		string b = diNodeCopy->right->value;
		string c = diNodeCopy->right->right->value; 
		AVLNode* A = diNodeCopy->left;
		AVLNode* B = diNodeCopy->right->left;
		AVLNode* C = diNodeCopy->right->right->left;
		AVLNode* D = diNodeCopy->right->right->right; 

		diNode->value = b; 
		diNode->right->value = c; 

		if (diNode->left == NULL) diNode->left = new AVLNode(); 
		diNode->left->value = a; 

		diNode->left->left = A;
		diNode->left->right = B; 
		diNode->right->left = C; 
		diNode->right->right = D; 	

	}
	// right left 
	else if (rot1 && !rot2) {
		string a = diNodeCopy->value;
		string b = diNodeCopy->right->value;
		string c = diNodeCopy->right->left->value; 
		AVLNode* A = diNodeCopy->left;  			
		AVLNode* B = diNodeCopy->right->left->left;
		AVLNode* C = diNodeCopy->right->left->right; 
		AVLNode* D = diNodeCopy->right->right; 

		diNode->value = c; 
		diNode->right->value = b; 

		if (diNode->left == NULL) diNode->left = new AVLNode(); 
		diNode->left->value = a; 
		
		diNode->left->left = A;
		diNode->left->right = B; 
		diNode->right->left = C; 
		diNode->right->right = D; 

	}
	// left right 
	else if (!rot1 && rot2) {
		string a = diNodeCopy->value;
		string b = diNodeCopy->left->value; 
		string c = diNodeCopy->left->right->value; 
		AVLNode* A = diNodeCopy->right;			
		AVLNode* B = diNodeCopy->left->left; 
		AVLNode* C = diNodeCopy->left->right->left; 
		AVLNode* D = diNodeCopy->left->right->right; 

		diNode->value = c;
		diNode->left->value = b; 

		if (diNode->right == NULL) diNode->right = new AVLNode(); 
		diNode->right->value = a; 

		diNode->left->left = B;
		diNode->left->right = C; 
		diNode->right->left = D; 
		diNode->right->right = A; 

	}
	// left left 
	else if (!rot1 && !rot2) {
		string a = diNodeCopy->value; 
		string b = diNodeCopy->left->value; 
		string c = diNodeCopy->left->left->value; 
		AVLNode* A = diNodeCopy->right;			
		AVLNode* B = diNodeCopy->left->right; 
		AVLNode* C = diNodeCopy->left->left->right; 
		AVLNode* D = diNodeCopy->left->left->left; 

		diNode->value = b;
		diNode->left->value = c; 

		if (diNode->right == NULL) diNode->right = new AVLNode(); 
		diNode->right->value = a; 

		diNode->left->left = D;
		diNode->left->right = C; 
		diNode->right->left = B; 
		diNode->right->right = A; 

	}
	
	deepestImbalance = "?";
	setHeights(root);
	
}


AVLNode* AVLTree::makeCopy(AVLNode* node) {
	AVLNode* cpy; 
	if (node == NULL) return NULL;
	
	cpy = new AVLNode(); 
	cpy->value = node->value; 
	cpy->height = node->height;
	cpy->left = makeCopy(node->left); 
	cpy->right = makeCopy(node->right); 

	return cpy;
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) {
    root = remove(root, x);

	setHeights(root);
	setDeepestImbalance(root);

	// no imbalance
	if (deepestImbalance == "?") return; 

	balanceTreeDeletion(); 
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
					return currentNode->right;
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
					return currentNode->left; 
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
stack<bool> AVLTree::directionsTo(const string& x, AVLNode* startingPoint) const {
    // YOUR IMPLEMENTATION GOES HERE
	stack<bool> leftRightTurnsTaken;  
	stack<bool> dummy; 
	
	if (root == NULL) return dummy;

	if (x == root->value) {
		return dummy; 
	}
	
	AVLNode* currentNode = startingPoint;

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



int AVLTree::getBalance(AVLNode* node) {
	int leftHeight = 0;
	int rightHeight = 0; 

	if (node->left != NULL) {
		leftHeight = node->left->height; 
	}
	if (node->right != NULL) {
		 rightHeight = node->right->height;
	}

	return leftHeight - rightHeight; 
}

void AVLTree::setDeepestImbalance(AVLNode* node) {
	if (numNodes() <= 2) return; 

	int balanceFactor = getBalance(node);
	
	// go right 	
	if (balanceFactor <= -2) {
		deepestImbalance = node->value;
		setDeepestImbalance(node->right); 
	}
	// go left 	
	else if (balanceFactor >= 2) {
		deepestImbalance = node->value;
		setDeepestImbalance(node->left); 
	}

	if (node->left != NULL) {
		setDeepestImbalance(node->left); 
	}
	if (node->right != NULL) {
		setDeepestImbalance(node->right); 
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
    cout << root->value << endl;
	// root->height 

    if (prev) prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);

    delete trunk;
}

void AVLTree::printTree() {
    printTree(root, NULL, false);
}
