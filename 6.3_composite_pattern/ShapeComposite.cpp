#include "ShapeComposite.h"
#include <sstream>

void ShapeComposite::AddShape(Shape* s) {
    shapes.push_back(s);
}

std::string ShapeComposite::to_string() const {
	std::stringstream ss;
	for (ShapeComposite::const_iterator it = this->begin(); it != this->end(); ++it) {
		ss << (*it)->to_string() << ";";
	}
	return ss.str();
}


ShapeComposite::iterator ShapeComposite::begin() {
	return shapes.begin();
}

ShapeComposite::iterator ShapeComposite::end() {
	return shapes.end();
}

ShapeComposite::const_iterator ShapeComposite::begin() const {
	return shapes.begin();
}

ShapeComposite::const_iterator ShapeComposite::end() const {
	return shapes.end();
}

size_t ShapeComposite::count() const {
	return shapes.size();
}
