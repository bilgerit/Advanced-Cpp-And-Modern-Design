// Simple helper file containing utility needed for this exercise.
// Specifically, we define a simple class hierarchy, and functions to print out type properties.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>

class Shape { 
public: 
	virtual void draw() = 0; 
};
					
class Base {					
private: 
	int y; 
public:
	Base() {} 
	void draw() {} 
};

class Point : public Shape { 
public: 
	Point() {} 
	virtual void draw() override {} 
};


template <typename T>
void type_properties_a(const T& t) {
	// Which classes/types are empty, polymorphic or abstract?
	std::cout << "object type: " << typeid(t).name() << std::endl;
	std::cout << "is_empty: " << std::is_empty<T>::value << std::endl;
	std::cout << "is_polymorphic: " << std::is_polymorphic<T>::value << std::endl;
	std::cout << "is_abstract: " << std::is_abstract<T>::value << std::endl;
}

template <typename T, typename U>
void type_same_class_b() {
	std::cout << "class names: " << typeid(T).name() << ", " << typeid(U).name() << ". ";
	std::cout << "classes are the same: " << std::is_same<T, U>::value << std::endl;
}

template <typename T, typename U>
void types_have_gen_spec_relationship_c() {
	std::cout << "class names: " << typeid(T).name() << ", " << typeid(U).name() << ". ";
	std::cout << "classes have gen/sepc (base/derived) relationship: " << std::is_base_of<T, U>::value << std::endl;
}

template <typename T, typename U>
void types_are_convertible_d() {
	std::cout << "class names: " << typeid(T).name() << ", " << typeid(U).name() << ". ";
	std::cout << "classes are convertible: " << std::is_convertible<T, U>::value << std::endl;
}
