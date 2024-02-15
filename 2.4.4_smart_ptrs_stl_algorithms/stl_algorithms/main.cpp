// In this exercise, we explore a difference in shared_ptr<T> and unique_ptr<T>. Specifically, if T is an abstract base class, it needs
// a public deleter in order to be used with the unique_ptr<T> template. This is not the case for shared_ptr<T>. We also explore the
// automatic destruction of elements in a list of shared_ptr<T> types.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include "util.h"
#include <list>
#include <memory>

int ex_a() {
	// Can't use unique_ptr<Base> here, as it can't access the protected destructor of Base.
	// unique_ptr<Base> expectes a public deleter!
	// We could make the destructor public instead. Then we could equally use unique and shared ptr lists with template argument Base.

	//std::list<std::unique_ptr<Base>> bu;
	std::list<std::shared_ptr<Base>> bs;

	for (int i = 0; i != 3; i++) 
	{
		//bu.push_back(std::make_unique<Derived>());	
		bs.push_back(std::make_shared<Derived>());
	}


	return 0;
};


int ex_b() {
	// Creating a list of shared_ptr<Base> types, and then assigning shared_ptr<Derived> type elements.
	std::list<std::shared_ptr<Base>> bs;

	for (int i = 0; i != 3; i++)
	{
		bs.push_back(factory_shared_derived());
	}
	return 0;
};


int ex_c() {
	// We can see in exercise a and b that the destructor is called automatically for each element once the list goes out of scope.
	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};