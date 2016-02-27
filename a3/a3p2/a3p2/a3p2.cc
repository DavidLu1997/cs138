#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
using namespace std;

struct NodeChunk {
	string *val;
	int top;
	NodeChunk *next;
};

struct Stack {
	int chunkSize;
	int topElt;
	int size;
	NodeChunk *firstChunk;
};

NodeChunk * createNewNodeChunk(int N) {
	NodeChunk *n = new NodeChunk;
	n->val = new string[N];
	n->top = -1;
	n->next = NULL;
	return n;
}

void initStack(int chunkSize, Stack& s) {
	assert(chunkSize > 0);
	s.chunkSize = chunkSize;
	s.size = 0;
	s.topElt = -1;
	s.firstChunk = NULL;
}

bool isEmpty(const Stack& s) {
	return  s.size == 0;
}

void push(string val, Stack& s) {
	s.size++;
	if (s.topElt == -1 && s.firstChunk == NULL) {
		s.firstChunk = createNewNodeChunk(s.chunkSize);
		s.firstChunk->val[0] = val;
		s.firstChunk->next = NULL;
		s.topElt = 0;
		s.firstChunk->top = s.topElt;
	}
	else if (s.topElt < s.chunkSize - 1) {
		s.topElt++;
		s.firstChunk->val[s.topElt] = val;
		s.firstChunk->top = s.topElt;
	}
	else {
		NodeChunk *n = createNewNodeChunk(s.chunkSize);
		n->val[0] = val;
		n->next = s.firstChunk;
		s.firstChunk = n;
		s.topElt = 0;
		s.firstChunk->top = s.topElt;
	}
}

void pop(Stack &s) {
	assert(!isEmpty(s));
	if (s.topElt == 0 && s.firstChunk->next != NULL) {
		s.size--;
		NodeChunk *n = s.firstChunk->next;
		delete[] s.firstChunk->val;
		delete s.firstChunk;
		s.firstChunk = n;
		s.topElt = s.firstChunk->top;
	}
	else if (s.topElt == 0 && s.firstChunk->next == NULL) {
		delete[] s.firstChunk->val;
		delete s.firstChunk;
		s.topElt = -1;
		s.size = 0;
		s.firstChunk = NULL;
	}
	else {
		s.topElt--;
		s.size--;
		s.firstChunk->top--;
	}
}

string top(const Stack& s) {
	assert(!isEmpty(s));
	return s.firstChunk->val[s.topElt];
}

void swap(Stack&s) {
	assert(s.size > 1);

	if (s.firstChunk->top > 0) {
		string temp = s.firstChunk->val[s.topElt];
		s.firstChunk->val[s.topElt] = s.firstChunk->val[s.topElt - 1];
		s.firstChunk->val[s.topElt - 1] = temp;
	}
	else {
		string temp = s.firstChunk->val[s.topElt];
		s.firstChunk->val[s.topElt] = s.firstChunk->next->val[s.chunkSize-1];
		s.firstChunk->next->val[s.chunkSize - 1] = temp;
	}
}

int size(const Stack & s) {
	return s.size;
}

int main() {


	Stack s;
	initStack(3, s);

	assert(isEmpty(s));
	assert(size(s) == 0);

	push("a", s);

	assert(!isEmpty(s));
	assert(size(s) == 1);

	push("b", s);
	push("c", s);

	assert(size(s) == 3);
	assert(top(s) == "c");
	assert(s.topElt == 2);

	push("d", s);
	assert(size(s) == 4);
	assert(top(s) == "d");
	assert(s.topElt == 0);

	push("e", s);

	assert(size(s) == 5);

	pop(s);

	assert(size(s) == 4);
	assert(s.topElt == 0);

	pop(s);
	assert(size(s) == 3);
	assert(s.topElt == 2);

	pop(s);
	pop(s);
	pop(s);

	assert(isEmpty(s));


	Stack s2;
	initStack(1, s2);

	assert(isEmpty(s2));

	push("a", s2);

	assert(size(s2) == 1);
	assert(top(s2) == "a");
	assert(s2.topElt == 0);

	push("b", s2);

	assert(size(s2) == 2);
	assert(top(s2) == "b");
	assert(s2.topElt == 0);

	pop(s2);
	assert(size(s2) == 1);
	assert(top(s2) == "a");
	assert(s2.topElt == 0);

	pop(s2);

	assert(isEmpty(s2));

	Stack a;
	for (int i = 1; i < 100; i++) {
		initStack(i, a);
		assert(isEmpty(a));
		assert(size(a) == 0);
		push("test", a);
		assert(!isEmpty(a));
		assert(size(a) == 1);
		assert(top(a) == "test");
		pop(a);
		assert(isEmpty(a));
		assert(size(a) == 0);
		push("1", a);
		assert(!isEmpty(a));
		assert(size(a) == 1);
		assert(top(a) == "1");
		push("2", a);
		assert(!isEmpty(a));
		assert(size(a) == 2);
		assert(top(a) == "2");
		push("3", a);
		assert(!isEmpty(a));
		assert(size(a) == 3);
		assert(top(a) == "3");
		push("4", a);
		assert(!isEmpty(a));
		assert(size(a) == 4);
		assert(top(a) == "4");
		push("5", a);
		assert(!isEmpty(a));
		assert(size(a) == 5);
		assert(top(a) == "5");
		push("6", a);
		assert(!isEmpty(a));
		assert(size(a) == 6);
		assert(top(a) == "6");
		push("7", a);
		assert(!isEmpty(a));
		assert(size(a) == 7);
		assert(top(a) == "7");
		push("8", a);
		assert(!isEmpty(a));
		assert(size(a) == 8);
		assert(top(a) == "8");
		push("9", a);
		assert(!isEmpty(a));
		assert(size(a) == 9);
		assert(top(a) == "9");
		push("10", a);
		assert(!isEmpty(a));
		assert(size(a) == 10);
		assert(top(a) == "10");
		push("11", a);
		assert(!isEmpty(a));
		assert(size(a) == 11);
		assert(top(a) == "11");
		push("12", a);
		assert(!isEmpty(a));
		assert(size(a) == 12);
		assert(top(a) == "12");
		push("13", a);
		assert(!isEmpty(a));
		assert(size(a) == 13);
		assert(top(a) == "13");
		push("14", a);
		assert(!isEmpty(a));
		assert(size(a) == 14);
		assert(top(a) == "14");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 13);
		assert(top(a) == "13");
		push("lol", a);
		assert(!isEmpty(a));
		assert(size(a) == 14);
		assert(top(a) == "lol");
		swap(a);
		assert(!isEmpty(a));
		assert(size(a) == 14);
		assert(top(a) == "13");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 13);
		assert(top(a) == "lol");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 12);
		assert(top(a) == "12");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 11);
		assert(top(a) == "11");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 10);
		assert(top(a) == "10");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 9);
		assert(top(a) == "9");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 8);
		assert(top(a) == "8");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 7);
		assert(top(a) == "7");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 6);
		assert(top(a) == "6");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 5);
		assert(top(a) == "5");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 4);
		assert(top(a) == "4");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 3);
		assert(top(a) == "3");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 2);
		assert(top(a) == "2");
		pop(a);
		assert(!isEmpty(a));
		assert(size(a) == 1);
		assert(top(a) == "1");
		pop(a);
		assert(isEmpty(a));
		assert(size(a) == 0);
	}
	cout << "It worked" << endl;
}