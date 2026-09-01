class Animal
{
protected:
	int age;
public:
	Animal() : age{ 10 } {}
	virtual void eat() = 0;
};


class Mammal : public virtual Animal 
{
public:
	Mammal() { this->age = 5; }
	virtual void breathe() = 0;
	void eat() override {}
};

class WingedAnimal : public virtual Animal
{
public:
	WingedAnimal() { this->age = 8; }
	virtual void flap() = 0;
	void eat() override {}
};

class Bat : public Mammal, public WingedAnimal
{
public:
	void breathe() override {}
	void flap() override {}
	void eat() override {}
};

#include <iostream>
#include <Windows.h>

int main()
{
	Bat b{};
	b.eat();
	Animal& a = b;

	system("pause");
}