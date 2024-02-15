// Reengineering GOF factory pattern 1
//
// Note: The code for Shape, Point, Line, Circle, ShapeFactory and ConsoleFactory
// was mostly taken from previous exercises.
//
// Among other things, we implement factories which create shape-type objects
// (either from terminal input or default constructed objects) and return
// unique pointers to them. We also implement aggregated object creation (within tuples).
//
// Tobias Bilgeri, 14.02.2024
#include <cassert>
#include "ConsoleFactory.h"
#include "WindowsFactory.h"


int main() {
    WindowsFactory wf{};

    // create a tuple
    std::cout << "Using the factory to create objects (as tuple and individually): \n";
    const auto [tpl_point, tpl_line, tpl_circle] = wf.CreateAllShapes();

    // create individual elements
    const auto point = wf.CreatePoint();
    const auto line = wf.CreateLine();
    const auto circle = wf.CreateCircle();

    // check that the two implementations (individually created and created as tuple) will match:
    std::cout << "\n\nprint the objects: \n";
    tpl_point->print();
    point->print();

    tpl_line->print();
    line->print();

    tpl_circle->print();
    circle->print();

    // c)
    // GOF solution: needs a specific method for each type.
    // Returning tuples: By making the implementation more flexible,
    //                   this might save some time such that you don't
    //                   have to implement a new method for each Object.
    //                   For example, one may simply return two points
    //                   to create a rectangle (maybe use the output of the
    //                   factory as an input to the rectangle constructor
    //                   or similar).
    //                   One could create such functionality using a variadic
    //                   member function.
 
    return 0;
}
