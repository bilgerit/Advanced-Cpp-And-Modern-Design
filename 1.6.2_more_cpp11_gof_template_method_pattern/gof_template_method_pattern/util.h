// Simple helper file containing utility needed for this exercise, mainly the TMPClass class.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

using InputFunction = std::function<double()>; 
using OutputFunction = std::function<void(const std::vector<double>&)>;

class TMPClass {
	// Use this class to create a uniformly initialized vector (size _n w/ value _startValue), multiply every element by a constant (via the InputFunction object),
	// and send the result to some output device (via the OutputFunction object).
private:
	const std::size_t _n;
	const double _startValue;
	const InputFunction _iFunction;
	const OutputFunction _oFunction;
	std::vector<double> _v;

public:
	TMPClass() = delete;
	TMPClass(std::size_t n, double startValue, InputFunction iFunction, OutputFunction oFunction);
	virtual ~TMPClass() = default;
	virtual void run() final;  // we want this function to do the same in any subclass.
	virtual const double preprocessor ();
	virtual void computation ();
	virtual void postprocessor ();
};

TMPClass::TMPClass(std::size_t n, double startValue, InputFunction iFunction, OutputFunction oFunction) :
	_n(n), _startValue(startValue), _iFunction(std::move(iFunction)), _oFunction(std::move(oFunction)), _v(n, startValue) {}

void TMPClass::run() {
	TMPClass::preprocessor();
	TMPClass::computation();
	TMPClass::postprocessor();
}

const double TMPClass::preprocessor() {
	return _iFunction();
}

void TMPClass::computation() {
	std::ranges::transform(
		_v.begin(),
		_v.end(),
		_v.begin(),
		[&](const double& el) -> double {return TMPClass::preprocessor() * el; }
	);
}

void TMPClass::postprocessor(){
	_oFunction(_v);
}