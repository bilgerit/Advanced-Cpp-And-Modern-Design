// In this exercise, we take a look at the [[deprecated]] attribute. 
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include "util.h"


void main() {
	// Everything but one line causes an error due to accessing deprecated stuff -- see commented code below.

	MyClass myClass;  // this line actually works, since we don't call the deprecated member function.

	/*
	* All of these lines fail due to accessing deprecated stuff:
	
	my_free_func();
	
	MyClassDepr myClassDepr;
	
	myClass.my_member_func();
	
	deprecated_var = 0;
	
	MyEnum myEnum = ENUM1;
	
	MyTemplateClass<int> myTemplateClass;
	
	my_lambda();
	*/
}
