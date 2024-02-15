// CounterObserver: Impl Observer
// Contains a simple counting mechanism.
// Tobias Bilgeri, 12.02.2024
#pragma once
#include "Observer.h"
#include <string>

class CounterObserver: public Observer
{
private:
	int cnt_ = 0;
	std::string label_ = "default";
public:
	~CounterObserver() override = default;
	void Update() override;
	void SetLabel(const std::string& s);
};