#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct Node {
    string val;
    Node* next;
};

Node* sortPair(Node* p1, Node* p2) {
    assert(p1 != NULL && p2 != NULL);
    if(p1->val < p2->val) {
        p1->next = p2;
        p2->next = NULL;
        return p1;
    }
    else {
        p2->next = p1;
        p1->next = NULL;
        return p2;
    }
}
