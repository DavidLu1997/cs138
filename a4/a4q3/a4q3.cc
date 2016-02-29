#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//*****BST Code*****
struct BST_Node {
	string key;
	BST_Node *left;
	BST_Node *right;
};

typedef struct BST_Node* BST;

void BST_init(BST &root) {
	root = NULL;
}

bool BST_isEmpty(const BST& root) {
	return root == NULL;
}

bool BST_has(const BST& root, string key) {
	if (BST_isEmpty(root)) {
		return false;
	}
	else if (root->key == key) {
		return true;
	}
	else if (key < root->key) {
		return BST_has(root->left, key);
	}
	else {
		return BST_has(root->right, key);
	}
}

void BST_print(const BST& root) {
	if (!BST_isEmpty(root)) {
		BST_print(root->left);
		cout << root->key << endl;
		BST_print(root->right);
	}
}

void BST_insert(BST &root, string key) {
	if (BST_isEmpty(root)) {
		root = new BST_Node;
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
	else if (key < root->key) {
		BST_insert(root->left, key);
	}
	else {
		BST_insert(root->right, key);
	}
}

void BST_delete(BST &root, string key) {
	//Find node to delete
	BST parent = root;
	BST node = parent;
	while (node != NULL && key != node->key) {
		parent = node;
		if (key < parent->key) {
			node = parent->left;
		}
		else {
			node = parent->right;
		}
	}

	//Node not found
	if (node == NULL) {
		return;
	}

    //Deleting root
	else if(root->key == key) {
        //No children
        if(root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        //One node, left
        else if(root->left != NULL && root->right == NULL) {
            BST temp = root;
            root = root->left;
            delete temp;

        }
        //One node, right
        else if(root->left == NULL && root->right != NULL) {
            BST temp = root;
            root = root->right;
            delete temp;
        }
        //Both nodes
        else {
            BST largestLeft = root->left;
            while (largestLeft->right != NULL) {
                largestLeft = largestLeft->right;
            }
            root->key = largestLeft->key;
            BST_delete(largestLeft, largestLeft->key);
        }
	}

	else {
        //No children
        if (node->left == NULL && node->right == NULL) {
            delete node;
        }
        //One children, right
        else if (node->left == NULL && node->right != NULL) {
            if (parent->left == node) {
                parent->left = node->right;
            }
            if (parent->right == node) {
                parent->right = node->right;
            }
            delete node;
        }
        //One children, left
        else if (node->left != NULL && node->right == NULL) {
            if (parent->left == node) {
                parent->left = node->left;
            }
            if (parent->right == node) {
                parent->right = node->left;
            }
            delete node;
        }
        //Two children
        //Find largest node in left subtree
        else {
            BST largestLeft = node->left;
            while (largestLeft->right != NULL) {
                largestLeft = largestLeft->right;
            }
            node->key = largestLeft->key;
            BST_delete(largestLeft, largestLeft->key);
        }
	}
}

//*****Queue Code*****

struct Qnode {
	string val;
	Qnode *next;
};

struct Queue {
	Qnode *first;
	Qnode *last;
	int size;
};

void initQ(Queue &q) {
	q.first = NULL;
	q.last = NULL;
	q.size = 0;
}

bool isEmptyQ(const Queue &q) {
	return q.size == 0;
}

void enterQ(Queue &q, string val) {

	Qnode *n = new Qnode;
	n->val = val;
	n->next = NULL;

	//Empty queue
	if (isEmptyQ(q)) {
		q.first = n;
		q.last = n;
	}

	//One or more elements
	else {
		q.last->next = n;
		q.last = n;
	}

	q.size++;
}

string firstQ(const Queue &q) {
	assert(!isEmptyQ(q));

	return q.first->val;
}

void leaveQ(Queue &q) {
	assert(!isEmptyQ(q));

	//One element
	if (q.first == q.last) {
		delete q.last;
		q.first = NULL;
		q.last = NULL;
	}

	//More than one element
	else {
		Qnode *t = q.first;
		q.first = q.first->next;
		delete t;
	}

	q.size--;
}

void printQ(const Queue &q) {
	Qnode *t = q.first;

	while (t != NULL) {
		cout << t->val << endl;
		t = t->next;
	}
}

//*****SBL Code*****

struct SBL {
	Queue q;
	BST root;
};

void SBL_init(SBL& sbl) {
	initQ(sbl.q);
	BST_init(sbl.root);
}

int SBL_Size(const SBL& sbl) {
	return sbl.q.size;
}

void SBL_arrive(SBL& sbl, string name) {
	enterQ(sbl.q, name);
	BST_insert(sbl.root, name);
}

void SBL_Leave(SBL& sbl) {
	BST_delete(sbl.root, firstQ(sbl.q));
	leaveQ(sbl.q);
}

string SBL_first(const SBL& sbl) {
	return firstQ(sbl.q);
}

bool SBL_lookup(const SBL& sbl, string name) {
	return BST_has(sbl.root, name);
}

void SBL_printInArrivalOrder(const SBL& sbl) {
	printQ(sbl.q);
}

void SBL_printInAlphabeticalOrder(const SBL& sbl) {
	BST_print(sbl.root);
}

