#pragma once
#include <iostream>
#include <type_traits>


template<typename T>
void print(const T& t, std::true_type)
{
    std::cout << "Printing pointer:" << *t << std::endl;
}


template<typename T>
void print(const T& t, std::false_type)
{
    std::cout << "Printing value: " << t << std::endl;
}


template<typename T>
void print(const T& t)
{
    print(t, std::is_pointer<T>());
}