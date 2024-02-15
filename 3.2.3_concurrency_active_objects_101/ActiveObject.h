// Active Object class (see class discription below).
// Tobias Bilgeri, 6. Dec. 2023
#pragma once
#include <thread>
#include <stdexcept>

class ActiveObject {
	// Active object. Executs its own thread of control. 
	// Allows for a one-to-one correspondence between an object and a thread.
	// Only allows for explicit construction with joinable thread as argument.
	// Destructor will attempt to join thread if not already joined.
private:
	std::jthread& t;
public:
	// Rule of 0
	ActiveObject() = delete;
	ActiveObject(const ActiveObject& other) = delete;
	ActiveObject(ActiveObject&& other) = delete;
	ActiveObject& operator = (const ActiveObject& other) = delete;
	ActiveObject& operator = (ActiveObject&& other) = delete;

	explicit ActiveObject(std::jthread& other);
	~ActiveObject();
};
