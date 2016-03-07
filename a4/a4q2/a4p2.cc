#include <iostream>
#include <string>
#include <cassert>
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
	BST parent = NULL;
	BST node = root;
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
	else if (root->key == key && parent == NULL) {
		//No children
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//One node, left
		else if (root->left != NULL && root->right == NULL) {
			BST temp = root;
			root = root->left;
			delete temp;
			temp = NULL;
		}
		//One node, right
		else if (root->left == NULL && root->right != NULL) {
			BST temp = root;
			root = root->right;
			delete temp;
			temp = NULL;
		}
		//Both nodes
		else {
			BST largestLeft = root->left;
			while (largestLeft->right != NULL) {
				largestLeft = largestLeft->right;
			}
			string temp = largestLeft->key;
			BST_delete(root, largestLeft->key);
			root->key = temp;
		}
	}

	else {
		//No children
		if (node->left == NULL && node->right == NULL) {
			if (parent->left == node) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
			delete node;
			node = NULL;
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
			node = NULL;
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
			node = NULL;
		}
		//Two children
		//Find largest node in left subtree
		else {
			BST largestLeft = node->left;
			while (largestLeft->right != NULL) {
				largestLeft = largestLeft->right;
			}
			string temp = largestLeft->key;
			BST_delete(root, largestLeft->key);
			node->key = temp;
		}
	}
}

int main() {
	BST bst;
	BST_init(bst);
	{
		assert(BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T:" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "5");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 5" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "5");
	{
		assert(BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T:" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "5");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 5" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "7");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 5 7" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "4");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 4 5 7" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "2");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 2 4 5 7" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "0");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 0 2 4 5 7" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "3");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 0 2 3 4 5 7" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "9");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 0 2 3 4 5 7 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "8");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 0 2 3 4 5 7 8 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "haha");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 0 2 3 4 5 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "1");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 0 1 2 3 4 5 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_insert(bst, "6");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 0 1 2 3 4 5 6 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	//removal stuff
	BST_delete(bst, "6");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 0 1 2 3 4 5 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "5");
	{
		assert(!BST_isEmpty(bst));
		assert(BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 0 1 2 3 4 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "0");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 1 2 3 4 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "4");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 1 2 3 7 8 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "8");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(BST_has(bst, "haha"));
		std::cout << "T: 1 2 3 7 9 haha" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "haha");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 1 2 3 7 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "7");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 1 2 3 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "1");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 2 3 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "3");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 2 9" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "9");
	{
		assert(!BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T: 2" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	BST_delete(bst, "2");
	{
		assert(BST_isEmpty(bst));
		assert(!BST_has(bst, "0"));
		assert(!BST_has(bst, "1"));
		assert(!BST_has(bst, "2"));
		assert(!BST_has(bst, "3"));
		assert(!BST_has(bst, "4"));
		assert(!BST_has(bst, "5"));
		assert(!BST_has(bst, "6"));
		assert(!BST_has(bst, "7"));
		assert(!BST_has(bst, "8"));
		assert(!BST_has(bst, "9"));
		assert(!BST_has(bst, "haha"));
		std::cout << "T:" << std::endl;
		std::cout << "A:";
		BST_print(bst);
		std::cout << std::endl;

	}
	std::cout << "it works" << std::endl;
	return 0;
}