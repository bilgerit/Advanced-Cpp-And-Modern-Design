// This file defines multiple Builder types which tie together IODevice and Shape subtypes.
#pragma once
#include <memory>
#include "IODeviceSubtypes.h"

using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;

class Builder {
	// A Builder interface for tying together Shapes and IODevices.
public:
	virtual std::tuple<ShapePointer, IODevicePointer> getProduct() = 0;
	virtual ShapePointer getShape() = 0;
	virtual IODevicePointer getIODevice() = 0;
	virtual ~Builder() = default;
};

class CircleBuilderA : public Builder {
	// Builder combining IODevice IODeviceA and Shape Circle.
public:
	IODevicePointer getIODevice() override {
		auto p = std::make_unique<IODeviceA>();
		return p;
	}
	ShapePointer getShape() override {
		auto p = std::make_unique<Circle>();
		return p;
	}
	std::tuple<ShapePointer, IODevicePointer> getProduct() override {
		return std::make_tuple(getShape(), getIODevice());
	}
	~CircleBuilderA() override = default;
};

class CircleBuilderB : public Builder {
	// Builder combining IODevice IODeviceB and Shape Circle.
public:
	IODevicePointer getIODevice() override {
		auto p = std::make_unique<IODeviceB>();
		return p;
	}
	ShapePointer getShape() override {
		auto p = std::make_unique<Circle>();
		return p;
	}
	std::tuple<ShapePointer, IODevicePointer> getProduct() override {
		return std::make_tuple(getShape(), getIODevice());
	}
	~CircleBuilderB() override = default;
};

class LineBuilderA : public Builder {
	// Builder combining IODevice IODeviceA and Shape Line.

public:
	IODevicePointer getIODevice() override {
		auto p = std::make_unique<IODeviceA>();
		return p;
	}
	ShapePointer getShape() override {
		auto p = std::make_unique<Line>();
		return p;
	}
	std::tuple<ShapePointer, IODevicePointer> getProduct() override {
		return std::make_tuple(getShape(), getIODevice());
	}
	~LineBuilderA() override = default;
};

class LineBuilderB : public Builder {
	// Builder combining IODevice IODeviceB and Shape Line.
public:
	IODevicePointer getIODevice() override {
		auto p = std::make_unique<IODeviceB>();
		return p;
	}
	ShapePointer getShape() override {
		auto p = std::make_unique<Line>();
		return p;
	}
	std::tuple<ShapePointer, IODevicePointer> getProduct() override {
		return std::make_tuple(getShape(), getIODevice());
	}
	~LineBuilderB() override = default;
};
