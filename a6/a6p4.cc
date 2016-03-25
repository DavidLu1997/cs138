#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Ancillary function for powerset.  It adds a character onto the beginning
// of each string in a vector.
vector<string> addChar (const vector<string>& v, char c) {
    vector<string> ans;
    for (int i=0; i<(int)v.size() ; i++) {
	ans.push_back(c + v.at(i));
    }
    return ans;
}

// Note that I wrote this in scheme first!  Programming "shell game"
// recursion puzzles is easier with weak typing.
// This takes a string and returns the power(multi)set of its characters
// as a vector.  For example, powerset of "aab" would be the vector with
// elements (in no particular order): "aab" "ab" "aa" "a" "ab" "a" "b".
// Assume we don't care about eliminating duplicates for now.
vector<string> powerset (string s) {
    vector<string> ans;
    if (s.size() == 0) {
	ans.push_back("");
    } else {
	char c = s.at(0);
	string rest = s.substr(1);
	vector<string> psetRest = powerset (rest);
	ans = addChar (psetRest, c);
	ans.insert(ans.end(), psetRest.begin(), psetRest.end());
    }
    return ans;
}

// Passive data node for hash tables.
struct Node {
	string word;
	Node* next;
};

class HashTable {
public:
	HashTable();
	HashTable(int K);
	virtual ~HashTable();
	void insert(string word);
	void remove(string word);	    // You implement this!
	bool lookup(string word) const;
	void print() const;
	void report() const;
	static const int DefaultSize;
protected:
	int getTableSize() const;
private:
	vector<Node*> table;
	// The "hash" function will be defined by each child class, 
	// each one using a different strategy.  But it needs to be
	// abstract (aka "pure virtual") in the abstract parent class.
	virtual int hash(string key) const = 0;

};

// Note that insert/lookup are completely defined here (and call hash) even
// tho hash is not defined here.  This is called the Template Method design
// pattern.  The hash function is private, meaning the children can't call
// it.  However, they can *define* it.  In fact, that's the only difference
// between the children classes: they each provide a difference
// implementation of hash!

const int HashTable::DefaultSize = 1000;
HashTable::HashTable() : table(DefaultSize) {}
HashTable::HashTable(int K) : table(K) {}

// The destructor has lots of garbage to clean up!  For each bucket with an
// overflow list, we delete the nodes.
HashTable::~HashTable(){
	for (int i = 0; i<getTableSize(); i++) {
		Node* p = table[i];
		while (p != NULL) {
			Node* temp = p;
			p = p->next;
			delete temp;
		}
	}
}

// Simple accessor function that will be used by children classes to
// implement the hash function.  It's protected as children need to use it
// but not public as external clients do not need to know about it.
// This is the only information about the table that the children classes
// need to know, so we can make the table itself private!
int HashTable::getTableSize() const {
	return (int)table.size();
}

// Use open hashing with unsorted linked list for overflow.
void HashTable::insert(string key) {
	const int slot = hash(key);
	Node* newNode = new Node;
	newNode->word = key;
	newNode->next = table[slot];
	table[slot] = newNode;
}

bool HashTable::lookup(string key) const {
	const int slot = hash(key);
	Node* curNode = table[slot];
	while (curNode != NULL) {
		if (curNode->word == key) {
			return true;
		}
		curNode = curNode->next;
	}
	return false;
}

// You implement this!
void HashTable::remove(string key) {
	int slot = hash(key);
	Node* temp = table[slot];
	Node* prev = NULL;
	while (temp != NULL && temp->word != key) {
		prev = temp;
		temp = temp->next;
	}

	//Deleting first
	if (prev == NULL && temp != NULL) {
		table[slot] = temp->next;
		delete temp;
	}
	//Any other element, connect next
	else if (temp != NULL) {
		prev->next = temp->next;
		delete temp;
	}
}

// To help you debug, if you find it useful.
void HashTable::print() const {
	for (int i = 0; i<getTableSize(); i++) {
		if (table[i] != NULL) {
			Node* p = table[i];
			while (p != NULL) {
				cout << i << "    " << p->word << endl;
				p = p->next;
			}
		}
	}
}

// So we can tell how good your hash function is ...
// Do NOT override this function in the version you submit.  We will check!
void HashTable::report() const {
	// K is number of buckets
	const int K = getTableSize();
	// How many overflow elements in each bucket?
	vector<int> stats(K);
	int totalNumEntries = 0;
	int numNonZeros = 0;
	int maxOverflowSize = 0;
	for (int i = 0; i<K; i++) {
		if (table[i] != NULL) {
			numNonZeros++;
			int numEntriesInThisBucket = 0;
			Node* p = table[i];
			while (p != NULL) {
				p = p->next;
				numEntriesInThisBucket++;
			}
			totalNumEntries += numEntriesInThisBucket;
			if (numEntriesInThisBucket > maxOverflowSize) {
				maxOverflowSize = numEntriesInThisBucket;
			}
			stats[i] = numEntriesInThisBucket;
		}
	}
	// This part added 28 March 2014:
	// Compute average # of probes required to establish that an element 
	// is not present by summing the squares of the bucket list lengths, 
	// then dividing by totalNumEntries
	int sumOfSquaresOfBucketListLengths = 0;
	for (int i = 0; i<stats.size(); i++) {
		sumOfSquaresOfBucketListLengths += stats.at(i) * stats.at(i);
	}
	const double avgNumberOfProbes = (double)sumOfSquaresOfBucketListLengths
		/ (double)totalNumEntries;
	cout << "Average # of probes to establish an element is not present: "
		<< setprecision(3) << fixed << avgNumberOfProbes << endl;

	// If we sort, it's trivial to find the median.
	sort(stats.begin(), stats.end());
	const int numEmptyBuckets = K - numNonZeros;
	const int firstNonZeroBucketIndex = numEmptyBuckets;
	cout << "Number of entries in table: " << totalNumEntries << endl;
	cout << "Total # buckets: " << K << " of which " << numEmptyBuckets
		<< " (" << 100 * numEmptyBuckets / K << "%)" << " were empty." <<
		endl;
	// We want the avg and median # of elements, but ignoring the empty
	// buckets, on the grounds that if we're looking for a valid word, it
	// doesn't matter how many empty buckets there are, as we'll be hashing
	// to a non-empty bucket and traversing that list.
	// To compute the median, find the index that is half-way between
	// firstNonZeroBucketIndex and K.
	const int median = stats[firstNonZeroBucketIndex + numNonZeros / 2];
	const int average = totalNumEntries / numNonZeros;
	cout << "Overflow list length:  Max = " << maxOverflowSize
		<< "  Median = " << median << "  Average = " << average << endl;
}
//SimpleHashTable
class SimpleHashTable : public HashTable {
public:
	SimpleHashTable() : HashTable() {};
	SimpleHashTable(int K) : HashTable(K) {};
	~SimpleHashTable() {}
private:
	int hash(string key) const {
		int h = 0;
		for (size_t i = 0; i < key.length(); i++) {
			h += key[i];
		}
		return h % getTableSize();
	}
};

//SmartHashTable
class SmartHashTable : public HashTable {
public:
	SmartHashTable() : HashTable() {};
	SmartHashTable(int K) : HashTable(K) {};
	~SmartHashTable() {}
private:
	int hash(string key) const {
		unsigned long long h = 0;
		for (size_t i = 0; i < key.length(); i++) {
			//Taylor hashing, 1989 constant
			h = h * 1989 + key[i];
		}
		return h % getTableSize();
	}
};

const int val[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

int scrabbleValue(string s) {
	int v = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z') {
			v += val[s[i] - 'a'];
		}
	}
	return v;
}

int scrabbleValue(char c) {
	if (tolower(c) >= 'a' && tolower(c) <= 'z') {
		return val[c - 'a'];
	}
	return 0;
}

int main(int argc, char* argv[]) {
	//Process input
	if (argc < 2) {
		cerr << "Error, no word list file name provided." << endl;
		return 0;
	}
	fstream file(argv[1], ios::in);
	if (!file.is_open()) {
		cerr << "Error, couldn't open word list file." << endl;
		return 0;
	}

	//Read word list into hash table
	SmartHashTable hash(100000);
	string t;
	while (file >> t) {
		hash.insert(t);
	}
	file.close();

	//Read words from file
	//Process each word
	vector<string> ps;
	int max = -1;
	int tem = 0;
	string temp;
	while (cin >> t) {
		//Call powerset
		ps = powerset(t);
		max = 0;
		for (size_t i = 0; i < ps.size(); i++) {
			//Sort
			tem = scrabbleValue(ps[i]);
			sort(ps[i].begin(), ps[i].end());
			do {
				//Check for existence in hashtable
				if (hash.lookup(ps[i]) && tem > max) {
					max = tem;
					temp = ps[i];
				}
			} while (next_permutation(ps[i].begin(), ps[i].end()));
		}
		if (max > 0) {
			cout << t << ": " << temp << " has score of " << max << endl;
		}
		else {
			cout << t << ": no matches" << endl;
		}
	}
}