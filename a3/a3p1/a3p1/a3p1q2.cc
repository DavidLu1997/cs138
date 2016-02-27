#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct Node {
	string val;
	Node* next;
	Node* prev;
};

struct Stew {
	Node* first;
	Node* last;
};

void initStew(Stew& q) {
	q.first = NULL;
	q.last = NULL;
}

bool isEmpty(const Stew& q) {
	return NULL == q.last;
}

void addBack(Stew& q, string val) {
	Node *n = new Node;
	n->val = val;
	n->next = NULL;
	n->prev = q.last;
	if (q.last != NULL) {
		q.last->next = n;
	}
	q.last = n;
	if (q.first == NULL) {
		q.first = n;
	}
}

void addFront(Stew& q, string val) {
	Node *n = new Node;
	n->val = val;
	n->next = q.first;
	n->prev = NULL;
	if (q.first != NULL) {
		q.first->prev = n;
	}
	q.first = n;
	if (q.last == NULL) {
		q.last = n;
	}
}

void leaveBack(Stew& q) {
	assert(!isEmpty(q));
	Node *temp = q.last->prev;
	delete q.last;
	q.last = temp;
	if (q.last != NULL) {
		q.last->next = NULL;
		if (q.last->prev == NULL) {
			q.first = q.last;
		}
	}
	else {
		q.first = NULL;
	}
}

string peekBack(const Stew& q) {
	assert(!isEmpty(q));
	return q.last->val;
}

void leaveFront(Stew& q) {
	assert(!isEmpty(q));
	Node *temp = q.first->next;
	delete q.first;
	q.first = temp;
	if (q.first != NULL) {
		q.first->prev = NULL;
		if (q.first->next == NULL) {
			q.last = q.first;
		}
	}
	else {
		q.last = NULL;
	}
}

string peekFront(const Stew& q) {
	assert(!isEmpty(q));
	return q.first->val;
}

void print(const Stew& q, char direction) {
	Node *temp;
	switch (direction) {
	case 'f':
		temp = q.first;
		while (temp != NULL) {
			cout << temp->val << endl;
			temp = temp->next;
		}
		delete temp;
		break;
	case 'r':
		temp = q.last;
		while (temp != NULL) {
			cout << temp->val << endl;
			temp = temp->prev;
		}
		delete temp;
		break;
	default:
		cerr << "Error, illegal direction: " << direction << endl;
	}
}

void nuke(Stew& s) {
	Node *temp = NULL, *head = s.first;
	while (head != NULL) {
		temp = head->next;
		delete head;
		head = temp;
	}
	delete head;
	s.first = NULL;
	s.last = NULL;
}

int main() {
	Stew stew;
	initStew(stew);
	assert(isEmpty(stew));
	addFront(stew, "1");
	assert(peekBack(stew) == "1");
	assert(peekFront(stew) == "1");
	leaveBack(stew);
	assert(stew.first == NULL);
	assert(stew.last == NULL);
	assert(isEmpty(stew));
	addFront(stew, "1");
	assert(peekBack(stew) == "1");
	assert(peekFront(stew) == "1");
	addBack(stew, "2");
	assert(peekBack(stew) == "2");
	assert(peekFront(stew) == "1");
	addBack(stew, "3");
	assert(peekBack(stew) == "3");
	assert(peekFront(stew) == "1");
	addFront(stew, "4");
	assert(peekBack(stew) == "3");
	assert(peekFront(stew) == "4");
	leaveBack(stew);
	assert(peekBack(stew) == "2");
	assert(peekFront(stew) == "4");
	leaveFront(stew);
	assert(peekBack(stew) == "2");
	assert(peekFront(stew) == "1");
	leaveBack(stew);
	assert(peekBack(stew) == "1");
	assert(peekFront(stew) == "1");
	leaveFront(stew);
	assert(isEmpty(stew));

	Stew s1;
	initStew(s1);
	addFront(s1, "alpha");
	addFront(s1, "beta");
	addFront(s1, "gamma");
	addBack(s1, "delta");
	leaveFront(s1);
	leaveBack(s1);
	assert(peekFront(s1) == "beta");
	assert(peekBack(s1) == "alpha");
	nuke(s1);
	assert(isEmpty(s1));

	Stew s2;
	initStew(s2);
	addFront(s2, "Taylor"); //Hi, I'm Taylor
	assert(peekFront(s2) == "Taylor"); //Looking at her
	assert(peekBack(s2) == "Taylor"); //Staring at her rear
	leaveFront(s2); //We are never ever ever getting back together
	addBack(s2, "Swift"); //I got a blank space baby
	assert(peekFront(s2) == "Swift");
	assert(peekBack(s2) == "Swift");
	leaveBack(s2); //We love watching her leave ;)
	assert(isEmpty(s2));

	cout << "----------PRINTING TESTS BEGINS-----------" << endl;
	cout << "Illegal direction should cause error mesg\n";
	print(s1, 'k');
	addFront(s2, "Emma");
	addBack(s2, "Watson");
	cout << "This should print out Emma Watson: " << endl;
	print(s2, 'f');
	leaveBack(s2); //Because watching her leave is fun ;)
	assert(peekFront(s2) == "Emma");
	addFront(s2, "Hermione"); //Throwback Thursday
	assert(peekBack(s2) == "Emma");
	cout << "This should print out Emma Hermione: " << endl;
	print(s2, 'r');
	cout << "This should not crash." << endl;
	nuke(s2); //Get out Emma
	cout << "----- TESTING FINISHED; ALL ASSERTIONS PASSED -----" << endl;
	cout << "Verify print statements are what were expected" << endl;
	return 0;
}

