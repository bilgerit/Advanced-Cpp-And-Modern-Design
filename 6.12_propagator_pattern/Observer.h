// Observer ABC
// Tobias Bilgeri, 11.02.2024
#pragma once

class Observer
{
public:
	virtual ~Observer() {}
	virtual void Update() = 0;
};