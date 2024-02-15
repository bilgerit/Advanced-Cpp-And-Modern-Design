// Monte-Carlo Engine for Vanilla European Options
// and drift-diffusion models.
//
// There are various ways to make this more flexible:
//    - Implement payoff as template (then we can also do binaries, etc.)
//    - Allow for more than just Drift/Diffusion models (can do e.g. with specialization
//      using templates)
//    - American payoffs, etc.
//
// Tobias Bilgeri, 15.02.2024
#pragma once
#include <numeric>
#include <vector>
#include "StochasticProcessConcepts.h"
#include <functional>

template<typename Process, typename Data>
requires IDriftDiffusion<Process, Data>
class EuropeanMCEngine
{
public:
	EuropeanMCEngine(const int num_paths, const int num_steps, const Data dt, 
		const Data strike, const Data init_price, const bool is_call, 
		const Data discount_factor, const Process& p) :
	num_paths_(num_paths), num_steps_(num_steps), dt_(dt), strike_(strike),
	init_price_(init_price), is_call_(is_call), discount_factor_(discount_factor),
	process_(p)
	{
		// initialize array for terminal states of the MC simulation
		terminal_states_ = std::vector<Data>(num_paths_);

		// initialize the payoff fn depending on whether this is call or put
		if (is_call_) {
			payoff_fn = [this](const Data price)
				{
					return std::max(price - strike_, 0.);
				};
		}
		else
		{
			payoff_fn = [this](const Data price)
				{
					return std::max(strike_ - price, 0.);
				};

		}
	}

	Data compute_payoff()
	{
		Data St;
		Data t;
		// loop through all paths
		for (int i = 0; i != num_paths_; ++i)
		{
			St = init_price_;
			t = 0;
			process_.reset();
			// loop through all steps
			for (int j = 0; j != num_steps_; ++j)
			{
 				St += process_.drift(t, St) + process_.diffusion(t, St);
				t += dt_;
			}
			// add result to payoff
			terminal_states_[i] = St;
		}

		// compute payoff
		expected_payoff_ = 0;
		for (const Data& el: terminal_states_)
		{
			expected_payoff_ += payoff_fn(el);
		}
		expected_payoff_ /= static_cast<Data>(terminal_states_.size());
		return expected_payoff_;
	}

private:
	int num_paths_;
	int num_steps_;
	Data dt_;
	Data strike_;
	Data init_price_;
	bool is_call_;
	Data discount_factor_;
	Process process_;
	Data expected_payoff_;
	std::vector<Data> terminal_states_;
	std::function<Data(const Data)> payoff_fn;
};