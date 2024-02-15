// Bucket Interface
// A bucket herein refers to an unordered set.
// We'll inspect the hashing of the unordered set and trigger rehashings with
// varying bucket numbers.
// 
// Bucket interface properties (= members of std::unordered_set):
//    bucket_count, max_bucket_count, load_factor, max_load_factor, bucket_size, ..
// 
// Tobias Bilgeri, 27. Dec. 2023
#pragma once
#include <iostream>
#include <unordered_set>

template <typename Key, typename Hash, typename EqPred>
void BucketInformation(const std::unordered_set<Key, Hash, EqPred>& c) {
    // Print information related to an unordered set ("Bucket").
    
    // ex. a. 
    // Show the number of buckets and the maximum number of possible buckets.
    std::cout << "Number of buckets: " << c.bucket_count() << "\n";
    std::cout << "Max number of buckets: " << c.max_bucket_count() << "\n";

    // ex. b. 
    // Show current load factor and the current maximum load factor.
    std::cout << "Load factor: " << c.load_factor() << "\n";
    std::cout << "Max load factor: " << c.max_load_factor() << "\n";

    // ex. c. 
    // Show the size of each bucket.
    for (std::size_t i = 0; i < c.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " size: " << c.bucket_size(i) << "\n";
    }
}

int main() {
    // Create unordered set ("Bucket") with 8 elements.
    // By default, it will create hashing 8 buckets (corresponding to the number of elements).
    std::unordered_set<int> example_set = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // Print information.
    // Note: the compiler will infere a default Hash and EqPred, which in this
    //       case is trivial since the bucket is made up of primitives (integers).
    BucketInformation(example_set);

    // ex. d.
    // Rehash the container so that it has a bucket size of at least some given size.
    example_set.rehash(10);  // will create 16 buckets.
    std::cout << "\n\nAfter rehashing w/ size_t Buckets = 10:\n";
    BucketInformation(example_set);

    example_set.rehash(5);   // will create 16 buckets.
    std::cout << "\n\nAfter rehashing w/ size_t Buckets = 5:\n";
    BucketInformation(example_set);

    example_set.rehash(60);  // will create 64 buckets.
    std::cout << "\n\nAfter rehashing w/ size_t Buckets = 60:\n";
    BucketInformation(example_set);

    return 0;
}