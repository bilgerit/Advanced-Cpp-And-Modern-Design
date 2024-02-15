// Tobias Bilgeri, 11.02.2024
#include "CounterPropagator.h"
#include <iostream>

void CounterPropagator::Update()
{
	// Increase this counter by one.
	// Afterwards, we notify the observers.
	cnt_ += 1;
	std::cout << "CounterPropagator '" << label_ << "' has been updated to " << cnt_ << ". Now notifying the observers.\n";

	this->NotifyObservers();
	std::cout << std::endl;
}

int CounterPropagator::GetCounter() const
{
	return cnt_;
}

void CounterPropagator::SetLabel(const std::string& s)
{
	label_ = s;
}
