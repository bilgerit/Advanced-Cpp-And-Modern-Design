// Numeric Combiner
// 
// In this case we look at a numeric example.
// 
// The signal takes an input (dbl, dbl), 
//      passes this input to the slots, 
//      the slots return a dbl,
//      the combiner sums up all the slot's return values,
//      and the signal returns the resulting value.
// In short, we use the signal to call a bunch of functions, and then 
// sum up and return the result.
// 
// Tobias Bilgeri, 29.1.2024
#include <iostream>
#include <boost/signals2.hpp>

template<typename T, typename Combiner>
using BinarySignal = boost::signals2::signal<T(T, T), Combiner>;

// exemplary binary slot fn's
double slot1(double x, double y) {
    return x + y;
}

double slot2(double x, double y) {
    return x - y;
}

double slot3(double x, double y) {
    return x * y;
}

double slot4(double x, double y) {
    return x / y;
}

// sum combiner
template <typename T>
struct SumCombiner {
    using result_type = T;

    template <typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        T sum = 0;
        while (first != last) {
            sum += *first;
            ++first;
        }
        return sum;
    }
};

// convenience fn
void println(const auto& s) {
    std::cout << s << "\n";
}

int main() {
    BinarySignal<double, SumCombiner<double>> signal;

    auto c1 = signal.connect(slot1);
    auto c2 = signal.connect(slot2);
    auto c3 = signal.connect(slot3);
    auto c4 = signal.connect(slot4);

    auto ret = signal(2., 2.);
    println("Calling signal w/ inp. (2., 2.):");
    println(ret); // 9 = 2+2 + 2-2 + 2*2 + 2/2;

    return 0;
}