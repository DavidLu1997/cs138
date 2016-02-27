#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct Node {
    string val;
    Node* next;
};

Node* append(Node* p1, Node* p2) {
    assert(p1 != NULL);
    Node *head = p1;
    while(p1->next != NULL) {
        p1 = p1->next;
    }
    p1->next = p2;
    return head;
}
