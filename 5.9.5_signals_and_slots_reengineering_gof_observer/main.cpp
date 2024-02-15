// Observer Pattern
// 
// GOF Observer Pattern: 1-N dependency where 1 object changes
//                       the state and updates N other objects.
// 
// Can be implemented using: OOP
//                           Collections (given here)
//                           Signals2 (todo here)
//                           ....
// 
// Tobias Bilgeri, 30.1.2024
#include <iostream>
#include <list>
#include <boost/signals2.hpp>


// Given Observer Pattern using a Collection
class SubjectCollection {
    // The notifier (Observable) in Publisher-Subscriber pattern 
public:
    using FunctionType = boost::function<void(double)>;

    SubjectCollection() {
        attentionList = std::list<FunctionType>();
    }
    void AddObserver(const FunctionType& ft) {
        // Add a callable.
        attentionList.push_back(ft);
    }

    void ChangeEvent(double x) {
        // Call all Functions
        for (auto it = attentionList.begin(); it != attentionList.end(); ++it) {
            (*it)(x);
        }
    }

private:
    // List of functions to call:
    std::list<FunctionType> attentionList;

};


// Reimplementation of the above Observer pattern using Signals + Slots.
class SubjectSignals {
    // Observer Pattern using Signals/Slots instead of Collections.
    //
    // Rather than storing functions in a list and calling them sequentially
    // when receiving an update, we store a single signal.
    // We then can add multiple slots to a signal.
public:
    using SignalType = boost::signals2::signal<void(double)>;
    using SlotType = SignalType::slot_type;

    void AddObserver(const SlotType& slot) {
        // Add a slot (must be a callable of type SlotType performing
        // the following mapping: double -> void.
        signal.connect(slot);
    }
    void ChangeEvent(double x) {
        // Call the signal and update all slots.
        signal(x);
    }
private:
    SignalType signal;
};

// Given Slots:
void CPrint(double x) { 
    std::cout << "C function: " << x << std::endl; 
}

struct Print { 
    void operator() (double x) const { 
        std::cout << "I am a printer " << x << std::endl; 
    } 
};

// Some more Slots:
struct MathsWhiz {
    double state = 0;
    MathsWhiz(double v) : state(v) {}
    void operator() (double x) {
        state *= x;
        std::cout << "MathsWhiz called with value: " << x << "; state is now: " << state << "\n";
    }
};

struct Database {
    double state = 0;
    void operator() (double x) {
        state += x;
        std::cout << "Database called with value: " << x << "; state is now: " << state << "\n";
    }
};

int main() {

    // create notifiers
    SubjectCollection subjectCollection;
    SubjectSignals subjectSignals;

    // create the attention list / slots
    Print myPrint;
    MathsWhiz myMaths(10.0);
    Database myDatabase;

    // attention list
    subjectCollection.AddObserver(myPrint);
    subjectCollection.AddObserver(myMaths);
    subjectCollection.AddObserver(myDatabase);
    subjectCollection.AddObserver(&CPrint);

    // slots
    subjectSignals.AddObserver(myPrint);
    subjectSignals.AddObserver(myMaths);
    subjectSignals.AddObserver(myDatabase);
    subjectSignals.AddObserver(&CPrint);

    // trigger event
    std::cout << "Give the value: ";
    double val;
    std::cin >> val;

    std::cout << "\n\nPass value as event to List-based Subject object: \n";
    subjectCollection.ChangeEvent(val);

    std::cout << "\n\nPass value as event to Signals-based Subject object: \n";
    subjectSignals.ChangeEvent(val);

    std::cout << "\n\nPass value as event to List-based Subject object: \n";
    subjectCollection.ChangeEvent(val);

    std::cout << "\n\nPass value as event to Signals-based Subject object: \n";
    subjectSignals.ChangeEvent(val);

    return 0;
}
