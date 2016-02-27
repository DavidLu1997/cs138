#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct Node {
    string val;
    Node* next;
};

void printPairInOrder (Node *p1, Node *p2) {
    assert(p1 != NULL && p2 != NULL);
    if(p1->val < p2->val) {
        cout << p1->val << endl;
        cout << p2->val << endl;
    }
    else {
        cout << p2->val << endl;
        cout << p1->val << endl;
    }
}
