// Black Scholes: Analytic Price for a European Option.
// Quick & dirty textbook implementation.
// Tobias Bilgeri, 15.02.2024
#pragma once
#include <cmath>
#include <boost/math/distributions/normal.hpp>

double black_scholes_price(bool is_call, double strike, double underlying_price_init, double vol, double drift, double t) {
    boost::math::normal_distribution<> d(0, 1);
    double d1 = (std::log(underlying_price_init / strike) + (drift + 0.5 * vol * vol) * t) / (vol * std::sqrt(t));
    double d2 = d1 - vol * std::sqrt(t);

    if (is_call) {
        return underlying_price_init * boost::math::cdf(d, d1) - strike * std::exp(-drift * t) * boost::math::cdf(d, d2);
    }
    else {
        return strike * std::exp(-drift * t) * boost::math::cdf(d, -d2) - underlying_price_init * boost::math::cdf(d, -d1);
    }
}