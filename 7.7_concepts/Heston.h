// Heston Stochastic Process
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
class Heston
{
private:
	// Model Parameters
	Data var_init_;
	Data var_long_;
	Data var_reversion_speed_;
	Data vol_of_var_;
	Data spot_var_corr_;
	Data drift_;

	// Additional & Helper Variables
	Data dt_;
	Data sqrt_dt_;
	Data drift_aggregate_;
	std::default_random_engine dre_;
	std::normal_distribution<Data> norm_;
	Data dW_spot_;
	Data dW_var_;
	Data var_;
	Data vol_;
public:
	Heston(const Data& var_init, const Data& var_long, const Data& var_reversion_speed,
		   const Data& vol_of_var, const Data& spot_var_corr, const Data& drift, const Data& dt)
	     	: var_init_(var_init), var_long_(var_long), var_reversion_speed_(var_reversion_speed),
		      vol_of_var_(vol_of_var), spot_var_corr_(spot_var_corr), drift_(drift), dt_(dt)
	{
		sqrt_dt_ = sqrt(dt_);
		drift_aggregate_ = dt_ * drift_;
		std::random_device rd;
		dre_ = std::default_random_engine(rd());
		norm_ = std::normal_distribution<Data>(0., 1.);
		reset();
	}

	void reset()
	{
		// reset the instantaneous variance to it's initial condition.
		var_ = var_init_;
		vol_ = sqrt(var_);
	}

	void _update_vol()
	{
		// Heston Stochastic Process: Variance part
		dW_var_ = dW_spot_ * spot_var_corr_+ sqrt(1. - pow(spot_var_corr_, 2.)) * norm_(dre_);
		var_ += var_reversion_speed_ * (var_long_ - var_) * dt_ + vol_of_var_ * vol_ * dW_var_;
		var_ = std::max(var_, 0.);
		vol_ = sqrt(var_);
	}

	Data diffusion(Data t, Data x)
	{
		// Heston Stochastic Process: Spot + Variance parts
		dW_spot_ = norm_(dre_);
		_update_vol();
		return x * vol_ * sqrt_dt_ * dW_spot_;
	}

	Data drift(Data t, Data x)
	{
		return drift_aggregate_ * x;
	}
};
