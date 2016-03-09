#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Animal {
public:
	virtual ~Animal() {

	}
	virtual void speak() const = 0;
protected:
	Animal(string name) {
		this->name = name;
	}
	string getName() const {
		return name;
	}
private:
	string name;
};

class Sheep : public Animal {
public:
	~Sheep() {

	}
	void speak() const {
		cout << "    Sheep " << getName() << " says \"baaa\"." << endl;
	}
	Sheep(string name) : Animal(name) {
		
	}
};

class Dog : public Animal {
public:
	~Dog() {

	}
	void speak() const {
		cout << "    Dog " << getName() << " says \"woof\"." << endl;
	}
	Dog(string name) : Animal(name) {

	}
};

class Flock {
public:
	Flock(string dogName) {
		dog = new Dog(dogName);
	}
	virtual ~Flock() {
		for (int i = 0; i < sheepList.size(); i++) {
			delete sheepList[i];
		}
		delete dog;
	}
	void addSheep(string name) {
		sheepList.push_back(new Sheep(name));
	}
	void soundOff() {
		cout << "The flock of " << sheepList.size() << " sheep speaks!" << endl;
		dog->speak();
		for (int i = 0; i < sheepList.size(); i++) {
			sheepList[i]->speak();
		}
		cout << endl;
	}
private:
	Dog *dog;
	vector<Sheep*> sheepList;
};

int main() {
	Flock *myFlock = new Flock("Spot");
	myFlock->soundOff();
	myFlock->addSheep("Daisy");	myFlock->addSheep("Clover");
	myFlock->addSheep("Estelle");
	myFlock->soundOff();
	delete myFlock;
	myFlock = new Flock("Rover");
	myFlock->addSheep("Butch");
	myFlock->addSheep("Jonno");
	myFlock->soundOff();
	delete myFlock;
}