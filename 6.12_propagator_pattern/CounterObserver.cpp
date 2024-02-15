// Tobias Bilgeri, 12.02.2024
#include "CounterObserver.h"
#include <iostream>

void CounterObserver::Update()
{
	cnt_ += 1;
	std::cout << "CounterObserver '" << label_ << "' has been updated to " << cnt_ << ".\n";
}

void CounterObserver::SetLabel(const std::string& s)
{
	label_ = s;
}