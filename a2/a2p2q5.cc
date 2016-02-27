#include <iostream>
#include <string>
using namespace std;

struct Node {
    string val;
    Node* next;
};

Node* makePairList(string s1, string s2) {
    Node *p1 = new Node;
    Node *p2 = new Node;

    p1->val = s1;
    p2->val = s2;

    if(s1 < s2) {
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
