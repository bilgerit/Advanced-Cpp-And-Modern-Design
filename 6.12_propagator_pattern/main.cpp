// Propagator Pattern
//
// Rather than being a 'pure receiver' (Observer), a propagator can 
// also notify other propagators and Observers.
//
// Loosely speaking:
//         Propagator = Observer + Observable
//
// Tobias Bilgeri, 12.02.2024
#include <iostream>
#include "CounterPropagator.h"
#include "CounterObserver.h"

int main() {
    // Below:
    // 1) Create Propagator Counter_1
    // 2) Create Propagator Counter_2. Attach as Observer to Counter_1.
    // 3) Create Observer Counter_3. Attach as Observer to Counter_3.
    // .... and check what happens when we update each Observer.

    // create propagator
    CounterPropagator counter1;
    counter1.SetLabel("Counter_1");

    // update the propagator Counter_1 a few times
    std::cout << "\n --- Updating Propagator Counter_1 --- \n\n";

    counter1.Update();
    counter1.Update();
    counter1.Update();

    // attach a propagator to Counter_1 as an Observer.
    CounterPropagator counter2;
    counter2.SetLabel("Counter_2");

    counter1.AddObserver(&counter2);

    // now update Counter_1 again
    std::cout << "\n --- Updating Propagator Counter_1 after having added Propagator Counter_2 to it's Observers --- \n\n";

    counter1.Update();
    counter1.Update();
    counter1.Update();

    // attach an observer to the Counter_2 propagator.
    CounterObserver counter3;
    counter3.SetLabel("Counter_3");

    counter2.AddObserver(&counter3);

    // now update Counter_1 again
    std::cout << "\n --- Updating Propagator Counter_1 after having added Observer Counter_3 as an Observer to Counter_2 --- \n\n";
    counter1.Update();
    counter1.Update();
    counter1.Update();

    // update Counter_2 directly
    std::cout << "\n --- Updating Propagator Counter_2 --- \n\n";
    counter2.Update();  // Counter_2 has no observers.
    counter2.Update();
    counter2.Update();

    // update Counter_3 directly
    std::cout << "\n --- Updating Propagator Counter_3 --- \n\n";
    counter3.Update();
    counter3.Update();
    counter3.Update();


    return 0;
}