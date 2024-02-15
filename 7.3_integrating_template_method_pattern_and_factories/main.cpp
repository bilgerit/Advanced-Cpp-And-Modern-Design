// Template Method Pattern and Factories
//
// We integrate the Template Method Pattern and Generic Types with
// the factory pattern.
// The factory can create PolyLine<Container> type objects, which itself
// is a ShapeComposite derivative specialized to contain Points.
// ShapeComposoite itself has two generics: the containted shape type, and
// the container, which can be for example std::list or std::vector.
//
// Tobias Bilgeri, 14.02.2024
#include <iostream>
#include <vector>
#include <list>

#include "WindowsFactory.h"

int main() {
	// ex. a.
	// CreateLine() is now implemented in the base class and simply calls CreatePoint() twice.
	std::cout << "CreateLine() is now implemented in the base class and simply calls CreatePoint() twice.\n";
	WindowsFactory wf{};
	line_ptr l = wf.CreateLine();
	l->print();

	// ex. b.
	std::cout << "\nCreate a PolyLine with container std::vector, then create a few points and add them to PolyLine.\n";
	polyline_ptr<std::vector> pl1 = wf.CreatePolyLine<std::vector>();
	point_ptr p1 = wf.CreatePoint();
	point_ptr p2 = wf.CreatePoint();
	point_ptr p3 = wf.CreatePoint();
	pl1->AddShape(p1.get());
	pl1->AddShape(p2.get());
	pl1->AddShape(p3.get());
	pl1->print();

	std::cout << "\nSame but using a std::list.\n";
	polyline_ptr<std::list> pl2 = wf.CreatePolyLine<std::list>();
	pl2->AddShape(p1.get());
	pl2->AddShape(p2.get());
	pl2->AddShape(p3.get());
	pl2->print();

	return 0;
}