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

struct PQnode {
	int priority;
	Queue q;
	PQnode *next;
	int size;
	int numPriority;
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
		pq->numPriority = 1;
		pq->size = 1;
	}

	//Not empty
	else {
		PQ temp = pq;

		//Check for existence
		while (temp->next != NULL && priority >= temp->next->priority) { //This seems sketchy
			temp = temp->next;
		}

		//If priority exists
		if (temp->priority == priority) {
			enterQ(temp->next->q, val);
		}

		//Does not exist, between current and next
		else if(priority > temp->priority) {
			PQ t = new PQnode;
			t->priority = priority;
			t->next = temp->next;
			temp->next = t;
			initQ(t->q);
			enterQ(t->q, val);
			pq->numPriority++;
		}

		//Does not exist, less than current
		//Only occurs if its the first
		else {
			PQ t = new PQnode;
			t->priority = priority;
			t->next = temp;
			pq = t;
			initQ(t->q);
			enterQ(t->q, val);
			pq->numPriority++;
		}
	}

	pq->size++;
}

string firstPQ(const PQ& pq) {
	assert(!isEmptyPQ(pq));
	return pq->q.first->val;
}

void leavePQ(PQ& pq) {
	assert(!isEmptyPQ(pq));

	//Delete first element of q
	leaveQ(pq->q);

	//Check for empty
	if (isEmptyQ(pq->q)) {
		PQ temp = pq;
		pq = pq->next;
		delete temp;
		if (pq == NULL) {
			return;
		}
		pq->numPriority--;
	}

	pq->size--;
}

int sizePQ(const PQ& pq) {
	return pq->size;
}

int sizeByPriority(const PQ& pq, int priority) {

	PQ temp = pq;

	while (temp != NULL && temp->priority != priority) {
		temp = temp->next;
	}

	return temp == NULL ? 0 : temp->q.size;
}

int numPriorities(const PQ& pq) {
	return pq->numPriority;
}

int main() {

	PQ pq1 = new PQnode;
	initPQ(pq1);
	enterPQ(pq1, "derp", 0);
	enterPQ(pq1, "herp", 2);
	enterPQ(pq1, "cerp", 1);
	enterPQ(pq1, "cherp", 1);
	leavePQ(pq1);
	enterPQ(pq1, "nigga", 0);
	leavePQ(pq1);
	leavePQ(pq1);
	leavePQ(pq1);
	leavePQ(pq1);
	cout << isEmptyPQ(pq1) << endl;
}