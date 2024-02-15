// Given class to implement Drift-Diffusion processes.
// The stochastic process, implemented as template,
// must satisfy the IDriftDiffusion concept.
// Tobias Bilgeri, 15.02.2024
#pragma once
#include "StochasticProcessConcepts.h"


template <typename Process, typename Data>
requires IDriftDiffusion<Process, Data>
class DriftDiffusionBase
{
private:
	Process p_;
public:
	DriftDiffusionBase(const Process& p) : p_(p) {}

	Data diffusion(Data t, Data x)
	{
		return p_.diffusion(t, x);
	}

	Data drift(Data t, Data x)
	{
		return p_.drift(t, x);
	}
};
