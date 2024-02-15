// In this exercise, we fix a class hierarchy, and demonstrated 'sealing' of classes and member functions.
// Fixes revolve around proper usages of keywords such as final, virtual & const.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <memory>
#include "util.h"

int main() {
	std::shared_ptr<Base> base_ptr = std::make_unique<Base>();
	std::shared_ptr<Derived> derived_ptr = std::make_unique<Derived>();

	std::cout << "Base Class Pointer Behaviour: " << std::endl;
	base_ptr->draw();
	base_ptr->print();
	base_ptr.reset();

	std::cout << std::endl << "Derived Class Pointer Behaviour: " << std::endl;
	derived_ptr->draw();
	derived_ptr->print();
	derived_ptr.reset();

	return 0;
}