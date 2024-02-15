// Layered Communication
// 
// Simplified GOF Layers pattern: data is published from one layer to the layer
// above it.
// 
// Layers are: Exterior (data initialization)
//             Hardware (data checks)
//             Data (data modification)
//             Communication (data formatting and printing)
// 
// Logic implemented herein is: 
//   Exterior(inp; state) => Hardware(inp) => Data(inp) => Communcation(inp)
// 
// Each layer is a signal, which within its slot MUST call the subsequent layer.
// 
// 
// Tobias Bilgeri, 30.01.2024
#include <iostream>
#include <boost/signals2.hpp>


// using namespace to separate these things from the hypothetical rest of code.
namespace MyCommunicationLayer {

    // Typedefs: Signals and Slots
    // Signal: double -> None
    // Slots:  double -> None
    using SignalType = boost::signals2::signal<void(double& d)>;
    using SlotType = SignalType::slot_type;

    // convenience fn: variadic printing.
    template<typename T>
    void inline println(const T& inp) {
        std::cout << inp << "\n";
    }

    template<typename T, typename ...Types>
    void inline println(const T& inp, const Types& ...args) {
        std::cout << inp;
        println(args...);
    }

    // define layers as signals
    // each signal will receive an input (double), do something, and then
    // call the next layer by passing at a double.
    SignalType exteriorSignal;
    SignalType hardwareSignal;
    SignalType dataSignal;
    SignalType communicationSignal;

    // define slots via lambdas
    auto exteriorSlot = [](double d) -> void {
        // add state variable to input.
        // call hardware layer.
        static double state = 0.0;
        d += state;
        state += 0.2;
        hardwareSignal(d);
        };

    auto hardwareSlot = [](double d) -> void {
        // if input outside of [2, 4]: set to 3.
        // call data layer.
        if (!(2 <= d && d <= 4)) d = 3;
        dataSignal(d);
        };

    auto dataSlot = [](double d) -> void {
        // manipulate the input (here: idendity function for simplicity).
        // call the communication layer.
        double d_manipulated = d;
        communicationSignal(d_manipulated);
        };

    auto communcationSlot = [](double d) -> void {
        println("Communication slot called: ", d);
        };
};

int main() {

    using namespace MyCommunicationLayer;

    // Build up the "Layer Stack"
    //   Exterior -> Hardware -> Data -> Communication
    // (Ideally I would have this in a builder or something)
    exteriorSignal.connect(exteriorSlot);
    hardwareSignal.connect(hardwareSlot);
    dataSignal.connect(dataSlot);
    communicationSignal.connect(communcationSlot);

    // Pass some data through the stack.
    // The hardware slot will 'upscale' the initial few values to 3,
    // and later-on 'downscale' the values to 3, with a linear transition region.
    double k = 1.;
    for (int i = 0; i != 20; i++) {
        exteriorSignal(k);
    }

    return 0;
}