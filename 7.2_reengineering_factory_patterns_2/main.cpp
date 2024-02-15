// Novel ShapeFactory
//
// We implement a factory using a runtime-policy based approach, whereby the
// 'Create' methods can be defined and swapped out at runtime.
//
// We also create a lambda-fct based wrapper around the factory, which allows
// creating additional dynamic behaviour.
//
// Compared to the traditional GOF pattern, this means that we don't have to
// define complex inheritance patterns which might be hard to maintain.
// Instead, we can just create function objects, which can flexibly be
// changed and swapped out at runtime.
//
// Tobias Bilgeri, 13.02.2024
#include <iostream>
#include "ShapeFactory.h"


// Exercise a. Create some function objects for the runtime-policy based factory pattern.
auto CreatePoint1 = []()
{
	// create default point
	return std::make_unique<Point>(Point());
};

auto CreatePoint2 = []()
{
	// create point with coordinates (100, 100)
	return std::make_unique<Point>(Point(100., 100.));
};

auto CreateLine = []()
{
	// create default line
	return std::make_unique<Line>(Line());
};

struct CreateCircle
{
	// functor to create default circles
	circle_ptr operator () () const
	{
		return std::make_unique<Circle>(Circle());
	}
};

int main() {
	// create factory object, then assign creation-methods to it (=lambda fcts and functors here), and create some shapes.
	ShapeFactory sf{};

	sf.SetPointCreator(CreatePoint1);
	sf.SetLineCreator(CreateLine);
	sf.SetCircleCreator(CreateCircle());

	point_ptr p1 = sf.PointCreator();
	line_ptr l = sf.LineCreator();
	circle_ptr c = sf.CircleCreator();

	std::cout << "Print the created objects: \n";
	l->print();
	c->print();
	p1->print();

	// now set a different point_creator method.
	//  ... hallmark of a runtime-policy pattern: can change the behaviour at runtime.
	std::cout << "\n\nPrint the created Point after having reset the Point-Creation method within the factory: \n";
	sf.SetPointCreator(CreatePoint2);
	point_ptr p2 = sf.PointCreator();
	p2->print();

	// c)
	// Strategy-pattern: This is basically an example of a runtime-strategy pattern,
	//                   which within C++ is often referred to as runtime-policy pattern.
	// Command-pattern: We can use std::function to dynamically change behaviour within the
	//                  command pattern.
	// For high-performance applications, a compile-time pattern is usually preferable (but
	// this requires the possible behaviours to be known at compile time).

	// d)
	// We can use lambda-function wrappers to create 'factory-clone-like' procedures which
	// implement alternative dynamic behaviour.

	double radius = 3;
	auto alternateCircleFactory = [&radius, &sf]()
	{
		// lambda-fct based factory wrapper.
		// allows to dynamically change it's behaviour since radius and factory are
		// captured by reference.

		// use the regular factory behaviour:
		circle_ptr c = sf.CircleCreator();
		// use setter to change the object:
		c->setRadius(radius);
		return c;
	};

	circle_ptr c2 = alternateCircleFactory();

	// change the radius (captured-by-ref within the lambda):
	radius = 4;
	circle_ptr c3 = alternateCircleFactory();
	std::cout << "\n\nCreate a few circles with the lambda-function-based factory pattern & it's dynamic behaviour: \n";
	c2->print();
	c3->print();
	return 0;
}