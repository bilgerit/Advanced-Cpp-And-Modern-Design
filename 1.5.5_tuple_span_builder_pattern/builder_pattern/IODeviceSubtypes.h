// This file (lazily!) contains two different IODevice subtypes.
// Their only difference lies on the text they print to the console.
// The IODevice subtypes interact with different Shape subtypes (Line, Circle).
#pragma once
#include <iostream>
#include "Line.h"
#include "Circle.h"

class IODeviceA : public IODevice
{
	// IODevice subtype A
public:
	using IODevice::operator<<;
	void operator << (const Circle& c) override {
		std::cout << "IODeviceA: Cirle: radius=" << c.radius() << " center=(" << std::get<0>(c.center()) << "," << std::get<1>(c.center()) << ")" << std::endl;
	};

	void operator << (const Line& c) override {
		std::cout << "IODeviceA: Line: coordinates=(" << std::get<0>(c.coordinates()) << "," << std::get<1>(c.coordinates()) << "," << std::get<2>(c.coordinates()) << "," << std::get<3>(c.coordinates()) << ")" << std::endl;
	};
};

class IODeviceB : public IODevice {
	// IODevice subtype B
public:
	void operator << (const Circle& c) override {
		std::cout << "IODeviceB: Circle: center=(" << std::get<0>(c.center()) << "," << std::get<1>(c.center()) << "), radius=" << c.radius() << std::endl;
	}
	void operator << (const Line& c) override {
		std::cout << "IODeviceB: Line: coordinates are (" << std::get<0>(c.coordinates()) << "," << std::get<1>(c.coordinates()) << "," << std::get<2>(c.coordinates()) << "," << std::get<3>(c.coordinates()) << ")" << std::endl;
	}
};