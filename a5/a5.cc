#include <iostream>
#include <vector>
#include <string>
class Animal {
public:
	virtual ~Animal() { }
	virtual void speak() const = 0;
protected:
	Animal(std::string name) { this->name = name; }
	std::string getName() const { return name; }
private:
	std::string name;
};
class Sheep : public Animal {
public:
	void speak() const { std::cout << "    Sheep " << getName() << " says \"baaa\"." << std::endl; }
	Sheep(std::string name) : Animal(name) { }
};
class Dog : public Animal {
public:
	void speak() const { std::cout << "    Dog " << getName() << " says \"woof\"." << std::endl; }
	Dog(std::string name) : Animal(name) { }
};
class Flock {
public:
	Flock(std::string dogName) { dog = new Dog(dogName); }
	virtual ~Flock() {
		for (int i = 0; i < sheepList.size(); i++) {
			delete sheepList[i];
		}
		delete dog;
	}
	void addSheep(std::string name) { sheepList.push_back(new Sheep(name)); }
	void soundOff() {
		std::cout << "The flock of " << sheepList.size() << " sheep speaks!" << std::endl;
		dog->speak();
		for (int i = 0; i < sheepList.size(); i++) {
			sheepList[i]->speak();
		}
		std::cout << std::endl;
	}
private:
	Dog *dog;
	std::vector<Sheep*> sheepList;
};