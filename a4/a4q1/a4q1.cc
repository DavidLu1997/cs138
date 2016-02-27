#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct Qnode {
	string val;
	Qnode *next;
};

struct Queue {
	Qnode *first;
	Qnode *last;
};

void initQ(Queue &q) {
	q.first = NULL;
	q.last = NULL;
}

bool isEmptyQ(const Queue &q) {
	return q.first == q.last && q.first == NULL;
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
}

void printQ(const Queue &q) {
	Qnode *t = q.first;

	while (t != NULL) {
		cout << t->val << endl;
		t = t->next;
	}
}

struct PQnode {
	int priority;
	Queue q;
	PQnode *next;
};

typedef PQnode* PQ;

void initPQ(PQ& pq) {
	pq = NULL;
}

bool isEmptyPQ(const PQ& pq) {
	return pq == NULL;
}

void enterPQ(PQ& pq, string val, int priority) {
	//Empty
	if (isEmptyPQ(pq)) {
		pq = new PQnode;
		pq->priority = priority;
		pq->next = NULL;
		initQ(pq->q);
		enterQ(pq->q, val);
	}

	//Priority exists
	PQ temp = pq;
	while (temp->next != NULL) {
		if (temp->priority == priority) {
			enterQ(temp->q, val);
			return;
		}
		temp = temp->next;
	}

	//Priority does not exist, first one
	if (priority < pq->priority) {
		PQ t = new PQnode;
		t->priority = priority;
		t->next = pq;
		initQ(t->q);
		enterQ(t->q, val);
		pq = t;
		return;
	}

	//Priority does not exist, not first one
	temp = pq;
	while (temp->next != NULL && temp->next->priority < priority) {
		temp = temp->next;
	}
	PQ t = new PQnode;
	t->priority = priority;
	t->next = temp->next;
	temp->next = t;
	initQ(t->q);
	enterQ(t->q, val);
}

string firstPQ(const PQ& pq) {

}

void leavePQ(PQ& pq) {

}

int sizePQ(const PQ& pq) {

}

int sizeByPriority(const PQ& pq, int priority) {

}

int numPriorities(const PQ& pq) {

}