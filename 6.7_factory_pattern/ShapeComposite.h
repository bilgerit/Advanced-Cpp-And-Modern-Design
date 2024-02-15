// ShapeComposite class
// Holds a list of pointers to Shape-types.
// Tobias Bilgeri, 7.2.2024
#pragma once
#include <list>
#include <iostream>
#include "Shape.h"

class ShapeComposite : public Shape {
private:
    std::list<Shape*> shapes;

    // Copy constructor and assignment operator are private and not implemented
    ShapeComposite(const ShapeComposite&);
    ShapeComposite& operator=(const ShapeComposite&);

public:
    typedef std::list<Shape*>::iterator iterator;
    typedef std::list<Shape*>::const_iterator const_iterator;

    ShapeComposite() = default;

    void AddShape(Shape* s);

    std::string to_string() const;
    ShapeComposite* Clone() const override;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    size_t count() const;
};


inline void Print(const ShapeComposite& sc) {
    // print shape composite objects
    std::cout << "ShapeComposite: [";
    for (ShapeComposite::const_iterator it = sc.begin(); it != sc.end(); ++it) {
        std::cout << (*it)->to_string() << ", ";
    }
    std::cout << "]\n";
}