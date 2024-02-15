// Geometric Brownian Motion
//
// Satisfies the IDriftDiffusion concept.
//
// Note that this is not an architecture I would personally choose to implement
// but I believe that it is concruent with what is asced in the exercise.
//
// Tobias Bilgeri, 15.02.2024
#pragma once
#include <cmath>
#include <random>


template <typename Data>
class GBM
{
	// Geometric Brownian Motion
	// Stochastic process for an underlying.
	// Satisfies the IDriftDiffusion concept.
private:
	// Model Parameters:
	Data vol_;
	Data drift_;

	// Additional & helper variables:
	Data dt_;
	Data sqrt_dt_;
	Data drift_aggregate_;
	Data diffusion_aggregate_;
	std::default_random_engine dre_;
	std::normal_distribution<Data> norm_;
public:
	GBM(const Data& vol, const Data& drift, const Data& dt)
	: vol_(vol), drift_(drift), dt_(dt)
	{
		sqrt_dt_ = sqrt(dt_);
		diffusion_aggregate_ = vol_ * sqrt_dt_;
		drift_aggregate_ = dt_ * drift_;
		std::random_device rd;
		dre_ = std::default_random_engine(rd());
		norm_ = std::normal_distribution<Data>(0., 1.);
	}

	void reset() {};

	Data diffusion(Data t, Data x)
	{
		return diffusion_aggregate_ * x * norm_(dre_);
	}

	Data drift(Data t, Data x)
	{
		return drift_aggregate_ * x;
	}
};
