// IODevice interface
#pragma once
class Circle;
class Line;

class IODevice
{
	// Interface for displaying CAD objects
public:
	virtual void operator << (const Circle& c) = 0;
	virtual void operator << (const Line& c) = 0;
	virtual ~IODevice() = default;
};