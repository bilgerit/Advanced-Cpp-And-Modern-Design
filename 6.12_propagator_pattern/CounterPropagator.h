// CounterPropagator: Impl Propagator
// Contains a simple counting mechanism.
// Tobias Bilgeri, 12.02.2024
#pragma once
#include "Propagator.h"
#include <string>

class CounterPropagator : public Propagator
{
private:
	int cnt_ = 0;
	std::string label_ = "default";

public:
	~CounterPropagator() override = default;
	void Update() override;

	int GetCounter() const;
	void SetLabel(const std::string& s);
};