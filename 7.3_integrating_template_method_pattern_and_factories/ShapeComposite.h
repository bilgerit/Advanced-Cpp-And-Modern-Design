// ShapeComposite class
//
// Holds a list of pointers to Shape-types.
// Template parameters: (1) Shape-type stored in the container
//                      (2) Container: can be std::list, std::vector, etc.
//
// Tobias Bilgeri, 7.2.2024
#pragma once
#include "Shape.h"
#include <sstream>

template<typename _SHAPE, template<typename...> class Container>
class ShapeComposite : public Shape {
public:
    using container = Container<_SHAPE*>;
    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;

    ShapeComposite() = default;

    std::string str() const override {
        std::stringstream ss;
        ss << "ShapeComposite: " << typeid(*this).name() << ": ";
        for (const_iterator it = this->begin(); it != this->end(); ++it) {
            ss << (*it)->str() << "; ";
        }
        return ss.str();
    }

    ~ShapeComposite() override = default;

    void AddShape(_SHAPE* s) {
        shapes.push_back(s);
    }

    const container& GetShapes() const {
        return shapes;
    }

    iterator begin() {
        return shapes.begin();
    }

    const_iterator begin() const {
        return shapes.begin();
    }

    iterator end() {
        return shapes.end();
    }

    const_iterator end() const {
        return shapes.end();
    }

    size_t count() const {
        return shapes.size();
    }

private:
    container shapes;
};