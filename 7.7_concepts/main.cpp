// Concepts and Options Pricing
//
// In this exercise, we apply concepts to options pricing & stochastic process.
//
// TBH I don't like the overall architecture but for an exercise it was fun!
//
// Tobias Bilgeri, 15.02.2024
#pragma once
#include <iostream>
#include "EuropeanMCEngine.h"
#include "Heston.h"
#include "GBM.h"
#include "BlackScholes.cpp"

// exercise 1)
// Check comments at the top of TestMC.cpp

// exercise 2)
// Concepts: give a level of type safety for generics, better error messages,
//           more transparent code and requirements on generics, etc.
// Bridge pattern SDEAbstract:
//    TBH I don't think that this is a very good pattern in this case, but maybe I am
//    missing something.
//    The SDEAbstract class limits the available SDEs to drift-diffusion type SDEs
//    and is hence not suitable for e.g. Jump-Diffusion. Furthermore, this class shouldn't
//    be labelled SDEAbstract, but be more specific. Beyond this, it's also not an abstract class.
//    Beyond this, it acts as a simple wrapper around stochastic drift-diffusion processes.
//    Since the concept ensures that the processes in question must be a drift-diffusion-type,
//    which must implement all the methods that SDEAbstract implements, and the SDEAbstract
//    class does nothing else, what is it useful for? I really don't get this part.
//    We could just have downstream class which actually uses the stochastic process,
//    and ensures that if satisfies an interface via the concept. There is no need for
//    this intermediate class. This is exactly an advantage of concepts.
// But more generally, having a flexible implementation with a good base class and/or
// templates leads to more generic and reusable code, which we can used to implement
// different pricing models.

// exercise 3-5)
// testing a more flexible pricer using BS + Heston
// as already discussed in the EuropeanMCEngine.h file, there are a lot of possible
// improvements and ways to make the code more flexible available, such as:
//    - Implement payoff as template (then we can also do binary options, etc.)
//    - Allow for more than just Drift/Diffusion models (can do e.g. with template
//      specialization, since I need to call an additional method when using Jump-Diff
//      models, which is currently not possible; I already implemented some Concepts
//      for this purpose but didn't go any further)
//    - different RNGs for speed improvement; different initialization schemes
//    - Support Americans
//    - Better hierarchy with different engines (MC, PDE, Tree)
//    - Optimizations: more efficient RNGs, compile-time policy patterns, etc.
//      specific payoff classes, pre-allocations, pre-computations,
//      multi-treading (after rewriting the code in a thread-safe manner), etc.
//    - ....
// Note on Variadics for stochastic processes:
//		I pass a stochastic processes as already-initialized objects to
//      engines, hence there is no need to support complicated methods of
//      instantiation within the engine itself. I only need to be able to
//      have the stochastic process object fit the concept.
//           


using HestonProcess = Heston<double>;
using HestonPricer = EuropeanMCEngine<HestonProcess, double>;

using BSProcess = GBM<double>;
using BSPricer = EuropeanMCEngine<GBM<double>, double>;

int main()
{
	// Run Analyic BS, BS-MC, and Heston-MC with same parameters.
	// Results must match.

	// MC parameters
	const int num_paths = 10'000;
	const double dt = 1. / 365. / 2; // 2 steps per day
	const int num_steps = 365 * 2; // equals 1 year
	const double t = dt * num_steps;

	// some shared model parameters:
	const double underlying_price_init = 100.;
	const double drift = 0;

	// Payoff Parameters
	const double discount_factor = std::exp(-drift * t);
	const bool is_call = true;
	const double strike = 100;

	// MODEL: BLACK-SCHOLES MC
	const double vol = 0.2;
	BSProcess bs_process(vol, drift, dt);
	BSPricer bs_pricer(num_paths, num_steps, dt, strike, underlying_price_init, is_call, discount_factor, bs_process);
	double bs_exp_payoff = bs_pricer.compute_payoff();

	// MODEL: HESTON MC
	const double var_init = 0.2 * 0.2;
	const double var_long = var_init;
	const double var_reversion_speed = 10. / 365.;
	const double vol_of_var = 0.; // set to zero to have a GBM process => price should be same as BS; else: should be higher
	const double spot_var_corr = 0.5;

	HestonProcess heston_process(var_init, var_long, var_reversion_speed, vol_of_var, spot_var_corr, drift, dt);
	HestonPricer heston_pricer(num_paths, num_steps, dt, strike, underlying_price_init, is_call, discount_factor, heston_process);
	double heston_exp_payoff = heston_pricer.compute_payoff();

	// MODE: BLACK-SCHOLES analytic
	double bs_analytic_payoff = black_scholes_price(is_call, strike, underlying_price_init, vol, drift, t);

	std::cout << "Analytic BS price: " << bs_analytic_payoff << "\n";
	std::cout << "BS MC price: " << bs_exp_payoff << "\n";
	std::cout << "Heston MC price: " << heston_exp_payoff << "\n";
	return 0;
}