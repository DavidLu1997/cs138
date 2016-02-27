#include <iostream>
#include <string>
using namespace std;

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
		cout << "    \"" << root->key << "\"" << endl;
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
	//No children
	else if (node->left == NULL && node->right == NULL) {
		delete node;
	}
	//One children, right
	else if (node->left == NULL) {
		if (parent->left == node) {
			parent->left = node->right;
		}
		if (parent->right == node) {
			parent->right = node->right;
		}
		delete node;
	}
	//One children, left
	else if (node->right == NULL) {
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

int main() {

}