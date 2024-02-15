// Collection types with Bimap
// 
// In this exercise, we use Bimap with a variety of different Domain & Range ('left' and 'right') types:
//   set, unordered set, multiset, list
// We also explore using custom comperators for set and multiset.
// 
// Tobias Bilgeri, 28.1.2024
#include <iostream>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>

// ex. a. Bimap types where:
//    Domain is:   Set, Multiset, Unordered Set
//    Range is:    List, Set, Unordered Set
using BimapSetList = boost::bimap<boost::bimaps::set_of<int>, boost::bimaps::list_of<std::string>>;
using BimapSetSet = boost::bimap<boost::bimaps::set_of<int>, boost::bimaps::set_of<std::string>>;
using BimapSetUSet = boost::bimap<boost::bimaps::set_of<int>, boost::bimaps::unordered_set_of<std::string>>;

using BimapMSetList = boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::list_of<std::string>>;
using BimapMSetSet = boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::set_of<std::string>>;
using BimapMSetUSet = boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::unordered_set_of<std::string>>;

using BimapUSetList = boost::bimap<boost::bimaps::unordered_set_of<int>, boost::bimaps::list_of<std::string>>;
using BimapUSetSet = boost::bimap<boost::bimaps::unordered_set_of<int>, boost::bimaps::set_of<std::string>>;
using BimapUSetUSet = boost::bimap<boost::bimaps::unordered_set_of<int>, boost::bimaps::unordered_set_of<std::string>>;

// ex. c. support different kinds of comparitors (for example, std::greater<>).
//        Note: alternative comparitors are not supported for unordered_set and list.
using BimapSetSetGreater = boost::bimap<boost::bimaps::set_of<int, std::greater<>>, boost::bimaps::set_of<std::string>>;
using BimapMSetSetGreater = boost::bimap<boost::bimaps::multiset_of<int, std::greater<>>, boost::bimaps::set_of<std::string>>;

int main() {
    // create instances of the bimaps
    BimapSetList bimapSetList;
    BimapSetSet bimapSetSet;
    BimapSetUSet bimapSetUSet;

    BimapMSetList bimapMSetList;
    BimapMSetSet bimapMSetSet;
    BimapMSetUSet bimapMSetUSet;

    BimapUSetList bimapUSetList;
    BimapUSetSet bimapUSetSet;
    BimapUSetUSet bimapUSetUSet;

    BimapSetSetGreater bimapSetSetGreater;
    BimapMSetSetGreater bimapMSetSetGreater;

    // insert values
    for (int i = 1; i <= 3; ++i) {
        bimapSetList.insert(BimapSetList::value_type(i, "value" + std::to_string(i)));
        bimapSetSet.insert(BimapSetSet::value_type(i, "value" + std::to_string(i)));
        bimapSetUSet.insert(BimapSetUSet::value_type(i, "value" + std::to_string(i)));

        bimapMSetList.insert(BimapMSetList::value_type(i, "value" + std::to_string(i)));
        bimapMSetSet.insert(BimapMSetSet::value_type(i, "value" + std::to_string(i)));
        bimapMSetUSet.insert(BimapMSetUSet::value_type(i, "value" + std::to_string(i)));

        bimapUSetList.insert(BimapUSetList::value_type(i, "value" + std::to_string(i)));
        bimapUSetSet.insert(BimapUSetSet::value_type(i, "value" + std::to_string(i)));
        bimapUSetUSet.insert(BimapUSetUSet::value_type(i, "value" + std::to_string(i)));

        bimapSetSetGreater.insert(BimapSetSetGreater::value_type(i, "value" + std::to_string(i)));
        bimapMSetSetGreater.insert(BimapMSetSetGreater::value_type(i, "value" + std::to_string(i)));
    }

    // print values (I choose one exemplary bimap; others behave the same)
    std::cout << "BimapSetSet:\n";
    for (const auto& [left, right] : bimapSetSet) {
        std::cout << "\t" << left << " <=> " << right << "\n";
    }

    // now with alternative comperator
    std::cout << "BimapSetSetGreater:\n";
    for (const auto& [left, right] : bimapSetSetGreater) {
        std::cout << "\t" << left << " <=> " << right << "\n";
    }

    return 0;
}