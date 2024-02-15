// Slot Group
// 
// Same code as in the previous exercise, except that
// we place each slot into a group.
// The group defines the ordering of slot calls (lower numbers 
// have higher priority). In the previous exercise, the ordering
// was defined by the order of assignment.
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
    
    // COMPARED TO PREV EXERCISE: NOTE THE PRECEEDING INTEGER
    // The signals still get called in the same order as in the last exercise
    // due to the increasing group number (lowest numbers get called first).

    signal.connect(1, fnFree); 
    signal.connect(2, fnObject);
    signal.connect(
        3, 
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
        4,
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
    signalA.connect(7, signalB);
    auto CtoB = signalB.connect(6, signalC);
    signalC.connect(5, signalD);

    signalB.connect(4, slotB);
    signalC.connect(3, slotC);
    signalD.connect(2, slotD1);
    signalD.connect(1, slotD2);

    // COMPARED TO PREV EXERCISE:
    // Due to the way I have chosen to assign group numbers, 
    // the signals & slots now get called in reverse order 
    // (lowest number gets priority, hence signalB will call slot B before
    //  it calls signalC).
    printl("Emitting signal A:");
    signalA(); 
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