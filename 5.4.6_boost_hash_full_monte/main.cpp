// Create a custom type with custom hashing and equality operations and
// create a Bucket (unordered set) from these.
// The print bucket information using function created in the previous exercise.
// 
// Tobias Bilgeri, 27.1.2024
#pragma once
#include <iostream>
#include <unordered_set>
#include <string>
#include <boost/functional/hash.hpp>

// struct given in the exercise.
struct S {
    std::string f;
    std::string s;
    S(const std::string& s1, const std::string& s2) : f(s1), s(s2) {}
};

// given hash for the given struct S.
class SHash {
public:
    std::size_t operator() (const S& s) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, s.f);
        boost::hash_combine(seed, s.s);
        return seed;
    }
};

// given equality for the given struct S.
class SEqual {
public:
    bool operator ()(const S& lhs, const S& rhs) const {
        return (rhs.f == lhs.f && rhs.s == lhs.s);
    }
};

// BucketInformation function from previous exercise.
template <typename Key, typename Hash, typename EqPred>
void BucketInformation(const std::unordered_set<Key, Hash, EqPred>& c) {
    // Print information related to an unordered set ("Bucket").

    std::cout << "Number of buckets: " << c.bucket_count() << "\n";
    std::cout << "Max number of buckets: " << c.max_bucket_count() << "\n";

    std::cout << "Load factor: " << c.load_factor() << "\n";
    std::cout << "Max load factor: " << c.max_load_factor() << "\n";

    for (std::size_t i = 0; i < c.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " size: " << c.bucket_size(i) << "\n";
    }
}

int main() {
    std::unordered_set<S, SHash, SEqual> mySet;

    // ex. a. Add elements to this unordered set.
    mySet.insert(S("a", "b"));
    mySet.insert(S("1", "2"));
    mySet.insert(S("hello", "world"));

    // ex. b. Examine the bucket information for this unordered set.
    // Interestingly, it again created 8 buckets by default, despite only having
    // 3 members.
    BucketInformation(mySet);

    return 0;
}