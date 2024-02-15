// Combining Slot Return Values
// 
// We implement a custom combiner.
// Combiners are callable objects that handle return values of slots.
// They should be designed around a specific return type (the return type
// of the slots we work with).
// 
// Note the flow of data:
//   signal calls slots
//   slots return values to signal (!!!)
//   signal returns val = combiner(slot_return_values...)
// Hence:
//   signal -> {slots} -> signal/combiner -> return_value
// 
// 
// Tobias Bilgeri, 29.1.2024.
#include <iostream>
#include <boost/signals2.hpp>


struct BootstrapCheck {
    // Combiner Function Object for boost::signals2.
    // 
    // Combiners are used to iteratore through returns of slots to perform some operation
    // on the return values of slots.
    // 
    // In this specific case:
    // returns false if *it returns false for iterator it in [first, last(
    // (the InputIterator herein iterates through slots and represents a slot pointer).
    // Applicable to slots which return booleans.

    using result_type = bool;

    template <typename InputIterator>
    bool operator()(InputIterator first, InputIterator last) const {
        while (first != last) {
            if (!*first) {
                return false;
            }
            ++first;
        }
        return true;
    }
};


// create three slots returning booleans (2x true, 1x false)
bool slot1() {
    return true;
}

bool slot2() {
    return false;
}

bool slot3() {
    return true;
}


// convenience fn
void println(const auto& inp) {
    std::cout << std::boolalpha << inp << "\n";
}

int main() {
    
    // Create signal: maps void to bool.
    //                uses BootstrapCheck combiner (returns true if all slots return true).
    boost::signals2::signal<bool(), BootstrapCheck> signal;

    auto connection1 = signal.connect(slot1);
    auto connection2 = signal.connect(slot2);
    auto connection3 = signal.connect(slot3);

    println("Calling signal with all slots connected. Returned value is: ");
    auto ret = signal();
    println(ret);

    // disconnect signal 2 and call again
    connection2.disconnect();
    println("Calling signal after removing slot2: ");
    println(signal());

    return 0;
}