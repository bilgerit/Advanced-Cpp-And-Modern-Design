// Signals 101
// 
// We define a bunch of basic slots via lambdas, functors, and free functions.
// These slots may have states that get altered when a signal gets called.
// 
// We connect and disconnect these slots from signals.
// 
// We also experiment with connecting multiple slots to signals, and signals to 
// slots.
// Furthermore, we show that signals can also be connected to signals.
// Given multiple connections, the connections (Slots, Signals) get called
// in the order in which they were added, it seems.
// 
// Tobias Bilgeri, 28.1.2024
#include <iostream>
#include <boost/signals2.hpp>


void printl(const auto& s) { 
    std::cout << s << "\n"; 
}

// ex. a. Free fn
void fnFree() {
    printl("Free function called!");
}


int main() {

    // ex. a. Free fn, Lambda fn and Functor as Slots
    printl("Exercise a.\n");

    boost::signals2::signal<void()> signal;

    auto fnLambda = []() -> void {
        printl("Lambda function called!");
        };

    struct Functor {
        void operator () () const {
            printl("Callable object called!");
        }
    };

    const Functor fnObject{};

    // connect the slots
    signal.connect(fnFree);
    signal.connect(fnObject);
    signal.connect(
        []() -> void {
            printl("Lambda function called!");
        }
    );

    printl("All 3 slots connected. Now calling the signal.");
    signal();


    // ex. b. alter state of a slot using signal.
    printl("\nExercise b. \n");
    
    struct MyStruct {
        double val;
        explicit MyStruct(double v) : val(v) {}
        void modify(double newValue) {
            val = newValue;
            std::cout << "A third slot " << val << "\n";
        }
    };

    MyStruct myStruct(1.);

    // connect slot and store connection variable for later disconnecting.
    boost::signals2::connection c = signal.connect(
        [&myStruct]() -> void {
            myStruct.modify(myStruct.val + 1.);
        }
    );
 
    printl("Hooked up a new Slot. Calling Signal now.");
    signal();

    printl("\nCalling Signal again. Must see a change in state of the new Slot.");
    signal();

    // ex. c. disconnecting slots
    printl("\nExercise c.\n");

    printl("Disconnecting the last-added slot and calling Signal again.");
    c.disconnect();
    signal();

    printl("Disconnecting all slots and calling Signal now yields nothing:");
    signal.disconnect_all_slots();

    // ex. d.
    printl("\nExercise d.\n");
    
    // potential emitters
    boost::signals2::signal<void()> signalA; 
    boost::signals2::signal<void()> signalB; 
    boost::signals2::signal<void()> signalC; 
    boost::signals2::signal<void()> signalD;

    // slots
    auto slotB = []() {std::cout << "Slot B called by B\n " << std::endl; }; 
    auto slotC = []() {std::cout << "Slot C called by C\n " << std::endl; };
    auto slotD1 = []() {std::cout << "Slot D1 called by D\n " << std::endl; }; 
    auto slotD2 = []() {std::cout << "Slot D2 called by D\n " << std::endl; };

    // setting up connections following the requirements of the exercise
    signalA.connect(signalB);
    auto CtoB = signalB.connect(signalC);
    signalC.connect(signalD);

    signalB.connect(slotB);
    signalC.connect(slotC);
    signalD.connect(slotD1);
    signalD.connect(slotD2);

    printl("Emitting signal A:");
    signalA(); // calls signalB, which calls slotB and signalC, which calls 
               // slotC and signalD, which calls slotD1 and slotD2
               // (i.e., we end up calling everything).
               // The Slots/Signals get called in the order in which they were
               // connected to a Signal.
    printl("Emitting signal B:");
    signalB(); // similiar to above
    printl("Emitting signal C:");
    signalC(); 
    printl("Emitting signal D:");
    signalD();

    printl("Disconnecting Signal C from Signal B");
    CtoB.disconnect();
    printl("Calling signal B. This now only calls slotB.");
    signalB();

    return 0;
}