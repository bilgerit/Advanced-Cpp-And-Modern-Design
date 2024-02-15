// Shape ABC
// Tobias Bilgeri, 13.02.2024
#pragma once
#include <string>
#include <iostream>

class Shape
{
private:
public:
	virtual ~Shape() = 0;
	virtual std::string str() const = 0;
	void print() const
	{
		std::cout << this->str() << "\n";
	}
};

