// Propagator ABC
// A Propagator is both an Observer and an Observable.
// Note: I introduced this ABC for convenience / generalization, even though
//       not strictly required by the UML diagram.
// Tobias Bilgeri, 12.02.2024
#pragma once
#include "Observable.h"
#include "Observer.h"

class Propagator: public Observer, public Observable
{
private:
public:
	virtual ~Propagator() override {}
};