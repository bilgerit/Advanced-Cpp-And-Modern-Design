// TB: The below code is given.
//     I added it here for completeness.
//     As stated in the exercise, the code is inflexible.
//     Our work is providing more flexible implementations, etc.
//     A few comments:
//         There is an OptionData file which provides a set of parameters
//         for a BS-model which is then used to run a MC simulation.
//         There is no way to specify alternative models, alternative engines, etc.

// TestMC.cpp
//
// C++ code to price an option, essential algorithms.
// We take Geometric Brownian Motion (GBM) model and the Euler method.
// We compute option price.
// 2012-2-26 Update using std::vector<double> as data storage structure.
// 2016-4-3 DD using C++11 syntax, new example.
// 2017-8-2 DD version 1 for book
// (C) Datasim Education BV 2008-2021

/*
#include <random>
#include <memory>
#include <cmath>
#include <iostream>

#include "StopWatch.cpp"
#include "OptionData.hpp" // in local directory

class SDE
{
	// Defines drift + diffusion + data
private:
	std::shared_ptr<OptionData> data; // The data for the option
public:
	SDE(const OptionData& optionData) : data(new OptionData(optionData)) {}
	double drift(double t, double S)
	{
		// Drift term
		return (data->r - data->D)*S; // r - D
	}
	double diffusion(double t, double S)
	{
		// Diffusion term
		return data->sig * S;
	}
};

int main()
{
	std::cout << "1 factor MC with explicit Euler\n";
	OptionData myOption{ 65.0, 0.25, 0.08, 0.3, 0.0, -1 };
	//OptionData myOption{ 100, 1., 0.0, 0.2, 0.0, -1 };

	SDE sde(myOption);

	// Initial value of SDE
	double S_0 = 60;

	// Variables for underlying stock
	double x;
	double VOld = S_0;
	double VNew;
	long NT = 100;
	std::cout << "Number of time steps: ";
	std::cin >> NT;
	// V2 mediator stuff
	long NSIM = 50000;

	std::cout << "Number of simulations: ";
	std::cin >> NSIM;
	double M = static_cast<double>(NSIM);
	double dt = myOption.T / static_cast<double> (NT);
	double sqrdt = std::sqrt(dt);
	// Normal random number
	double dW;
	double price = 0.0;
	// Option price
	double payoffT;
	double avgPayoffT = 0.0;
	double squaredPayoff = 0.0;
	double sumPriceT = 0.0;
	// #include <random>
	// Normal (0,1) rng
	std::default_random_engine dre;
	std::normal_distribution<double> nor(0.0, 1.0);
	// Create a random number
	dW = nor(dre);
	StopWatch<> sw;
	sw.Start();
	for (long i = 1; i <= M; ++i) {
		// Calculate a path at each iteration
		if ((i / 100'000) * 100'000 == i) {
			// Give status after each 10000th iteration
			std::cout << i << ", ";
		}
		VOld = S_0;
		x = 0.0;
		for (long index = 0; index <= NT; ++index) {
			// Create a random number
			dW = nor(dre);
			// The FDM (in this case explicit Euler)
			VNew = VOld + (dt * sde.drift(x, VOld)) + (sqrdt * sde.diffusion(x, VOld) * dW);
			VOld = VNew; x += dt;
		}
		// Assemble quantities (postprocessing)
		payoffT = myOption.myPayOffFunction(VNew);
		sumPriceT += payoffT;
		avgPayoffT += payoffT / M;
		avgPayoffT *= avgPayoffT;
		squaredPayoff += (payoffT * payoffT);
	}
	// Finally, discounting the average price
	price = std::exp(-myOption.r * myOption.T) * sumPriceT / M;
	std::cout << "Price, after discounting: " << price << ", " << std::endl;
	double SD = std::sqrt((squaredPayoff / M) - sumPriceT * sumPriceT / (M * M));
	std::cout << "Standard Deviation: " << SD << ", " << std::endl;
	double SE = SD / std::sqrt(M);
	std::cout << "Standard Error: " << SE << ", " << std::endl;
	sw.Stop(); std::cout << "Elapsed time in seconds: " << sw.GetTime() << '\n';
	return 0;
}
*/