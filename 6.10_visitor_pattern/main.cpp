// Visitor Pattern
// 
// The Visitor allows adding additional shared behaviour without altering
// the class structure (apart from each class having to implement an
// .Accept(BaseVisitor& v) method).
// We then can create a Visitor hierarchy with BaseVisitor (here: 'ShapeVisitor')
// being derived to different ImplVisitor classes with specific behaviour.
//
// In this exercise, we create a simple PrintVisitor.
// But in general, the Visitors can also modify the objects they are visiting.
// 
// Tobias Bilgeri, 10.02.2024
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeComposite.h"
#include "PrintVisitor.h"

int main() {
    // create some shapes
    Point point(1., 1.);
    Line line(Point(1., 1.), Point(1., 1.));
    Circle circle(Point(1., 1.), 1.);
	ShapeComposite composite;
    composite.AddShape(&point);
    composite.AddShape(&line);
    composite.AddShape(&circle);

    // visitor
    PrintVisitor printVisitor;

    point.Accept(printVisitor);
    line.Accept(printVisitor);
    circle.Accept(printVisitor);
    composite.Accept(printVisitor);

    return 0;
}