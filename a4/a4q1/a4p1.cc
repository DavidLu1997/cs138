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
		return;
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
			enterQ(temp->q, val);
		}

		//Does not exist, between current and next
		else if(priority > temp->priority) {
			PQ t = new PQnode;
			t->priority = priority;
			t->next = temp->next;
			temp->next = t;
			initQ(t->q);
			enterQ(t->q, val);
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
		}
	}
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
	}
}

int sizePQ(const PQ& pq) {
	if (pq == NULL)
		return 0;
	PQ temp = pq;
	int size = 0;
	while (temp != NULL) {
		size += temp->q.size;
		temp = temp->next;
	}
	return size;
}

int sizeByPriority(const PQ& pq, int priority) {

	PQ temp = pq;

	while (temp != NULL && temp->priority != priority) {
		temp = temp->next;
	}

	return temp == NULL ? 0 : temp->q.size;
}

int numPriorities(const PQ& pq) {
	if (pq == NULL)
		return 0;
	PQ temp = pq;
	int size = 0;
	while (temp != NULL) {
		size++;
		temp = temp->next;
	}
	return size;
}

int main() {
	PQ pq;
	initPQ(pq);
	{
		assert(sizePQ(pq) == 0);
		assert(isEmptyPQ(pq));
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 0);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 0);
	}
	enterPQ(pq, "onething", 3);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "onething");
		assert(sizePQ(pq) == 1);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 1);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 1);
	}
	leavePQ(pq);
	{
		assert(sizePQ(pq) == 0);
		assert(isEmptyPQ(pq));
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 0);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 0);
	}
	enterPQ(pq, "p3e0", 3);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p3e0");
		assert(sizePQ(pq) == 1);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 1);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 1);
	}
	enterPQ(pq, "p3e1", 3);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p3e0");
		assert(sizePQ(pq) == 2);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 1);
	}
	enterPQ(pq, "p2e0", 2);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e0");
		assert(sizePQ(pq) == 3);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 1);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 2);
	}
	enterPQ(pq, "p5e0", 5);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e0");
		assert(sizePQ(pq) == 4);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 1);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	enterPQ(pq, "p2e1", 2);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e0");
		assert(sizePQ(pq) == 5);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 2);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	enterPQ(pq, "p2e2", 2);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e0");
		assert(sizePQ(pq) == 6);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	enterPQ(pq, "p1e0", 1);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p1e0");
		assert(sizePQ(pq) == 7);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 1);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 4);
	}
	enterPQ(pq, "p1e1", 1);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p1e0");
		assert(sizePQ(pq) == 8);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 2);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 4);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p1e1");
		assert(sizePQ(pq) == 7);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 1);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 4);
	}
	enterPQ(pq, "p0e0", 0);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p0e0");
		assert(sizePQ(pq) == 8);
		assert(sizeByPriority(pq, 0) == 1);
		assert(sizeByPriority(pq, 1) == 1);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 5);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p1e1");
		assert(sizePQ(pq) == 7);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 1);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 4);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e0");
		assert(sizePQ(pq) == 6);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 3);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e1");
		assert(sizePQ(pq) == 5);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 2);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p2e2");
		assert(sizePQ(pq) == 4);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 1);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 3);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p3e0");
		assert(sizePQ(pq) == 3);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 2);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 2);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p3e1");
		assert(sizePQ(pq) == 2);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 1);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 2);
	}
	leavePQ(pq);
	{
		assert(!isEmptyPQ(pq));
		assert(firstPQ(pq) == "p5e0");
		assert(sizePQ(pq) == 1);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 0);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 1);
		assert(numPriorities(pq) == 1);
	}
	leavePQ(pq);
	{
		assert(isEmptyPQ(pq));
		assert(sizePQ(pq) == 0);
		assert(sizeByPriority(pq, 0) == 0);
		assert(sizeByPriority(pq, 1) == 0);
		assert(sizeByPriority(pq, 2) == 0);
		assert(sizeByPriority(pq, 3) == 0);
		assert(sizeByPriority(pq, 4) == 0);
		assert(sizeByPriority(pq, 5) == 0);
		assert(numPriorities(pq) == 0);
	}
	std::cout << "shit worked, yo" << std::endl;
	return 0;
}