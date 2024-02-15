// Observer Pattern using Universal Function Wrappers
//
// We create a Subject class containing a templated container of std::function
// objects. The latter can be added and removed at runtime.
//
// Additionally, the Subject class can accept slots via a boost::signals2
// signal.
//
// The advantage of using function wrappers over a traditional inheritance-based
// observer pattern is the small amount of code needed, and the transparency of
// the implementation.
//
// An advantage of the traditional observer pattern is that if we use only a
// very small Observer ABC with a single notify method, it is very easy to turn
// any arbitrary object into an observer (potentially via multiple inheritance).
//
// An advantage of boost::signals2 is the thread-safety when handling connections.
// Further discussion on boost::signals2 and why it represents more than just
// an array of callables:
// stackoverflow.com/questions/18663490/how-and-why-one-would-use-boost-signals2
//
// Tobias Bilgeri, 15.02.2024
#include <iostream>
#include <list>
#include <deque>

#include "Subject.h"


int main() {
	// create some observers:
    // in this exercise, observers are std::function objects, rather than
    // derived types of some Observer ABC.
    using observer_t = Subject<std::list>::observer_t;

	auto longFormatObserver = std::make_unique<observer_t> (
        [](int value) -> void
        {
			std::cout << "longFormatObserver notified: " << static_cast<long>(value) << "\n";
		}
    );

    auto doubleFormatObserver = std::make_unique<observer_t> (
        [](int value) -> void
		{
		    std::cout << "doubleFormatObserver notified: " << static_cast<double>(value) << "\n";
		}
    );

    // list and deque based subject sets
    Subject<std::list> subject_list;
    Subject<std::deque> subject_deque;

    // attach observer lambdas
    subject_list.attach(longFormatObserver.get());
    subject_deque.attach(longFormatObserver.get());

    subject_list.attach(doubleFormatObserver.get());
    subject_deque.attach(doubleFormatObserver.get());

    // ex. c: attach some slots to subject_list
    subject_list.signal().connect(*doubleFormatObserver);

    // trigger subject event and notify observers
    subject_list.increaseCounter();
    subject_deque.increaseCounter();

    subject_list.decreaseCounter();
    subject_deque.decreaseCounter();

    // remove observers and slots
    subject_list.detach(longFormatObserver.get());
    subject_list.detach(doubleFormatObserver.get());
    subject_list.signal().disconnect_all_slots();
    subject_deque.detach(longFormatObserver.get());
    subject_deque.detach(doubleFormatObserver.get());

    // this shouldn't notify anyone now
    subject_list.increaseCounter();
    subject_deque.increaseCounter();

    return 0;
}
