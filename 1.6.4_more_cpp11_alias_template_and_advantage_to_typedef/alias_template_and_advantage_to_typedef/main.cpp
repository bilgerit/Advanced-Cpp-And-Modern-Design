// In this exercise, we demonstrate C++98 to create flexible templated types, and lateron C++ style alias templating.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"
#include <cassert>


int main() {
	// Client of storage using typedef (C++ 98) 
	int n = 10;
	int val = 2;
	Client<int> myClient(n, val);  // uniform initializer.
	myClient.print();
	auto myClientData = myClient.getData();

	AliasTemplateClient<int> myAliasTemplateClient(n, val);
	myAliasTemplateClient.print();
	auto myAliasTemplateClientData = myAliasTemplateClient.getData();

	bool is_equal = (myClientData == myAliasTemplateClientData);
	std::cout << "member variable <data> in both cases are equal: " << std::boolalpha << is_equal << std::endl;
	return 0;
}