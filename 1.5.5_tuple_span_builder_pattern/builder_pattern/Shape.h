// Shape interface 
#pragma once
#include "IODevice.h"

class Shape {
	// Shape interface
public:
    virtual void display(IODevice& ioDevice) const = 0;
	virtual ~Shape() = default;
};
