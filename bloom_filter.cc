#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

// This code defines a Bloom filter, which is a probabilistic data structure
// used for efficient membership testing. The constructor initializes the Bloom
// filter with the expected number of elements and the desired false positive
// rate. It calculates the number of hash functions and the size of the filter
// based on these parameters. It then resizes the filter and generates the hash
// functions using lambda expressions.
class BloomFilter {
private:
  std::vector<bool> filter_;
  std::vector<std::function<size_t(const std::string &)>> hash_functions_;
  size_t num_hash_functions_;
  size_t filter_size_;
  size_t num_elements_;

public:
  BloomFilter(size_t expected_num_elements, double false_positive_rate) {
    num_elements_ = 0;
    num_hash_functions_ = static_cast<size_t>(
        std::ceil(-(std::log(false_positive_rate) / std::log(2))));
    filter_size_ = static_cast<size_t>(
        std::ceil(-(expected_num_elements * std::log(false_positive_rate)) /
                  (std::log(2) * std::log(2))));

    filter_.resize(filter_size_, false);

    // Generate hash functions
    for (size_t i = 0; i < num_hash_functions_; i++) {
      hash_functions_.push_back([=](const std::string &key) {
        std::hash<std::string> hash_function;
        size_t hash = hash_function(key);
        return (hash + i) % filter_size_;
      });
    }
  }

  void insert(const std::string &key) {
    for (const auto &hash_function : hash_functions_) {
      size_t index = hash_function(key);
      filter_[index] = true;
    }
    num_elements_++;
  }

  bool contains(const std::string &key) {
    for (const auto &hash_function : hash_functions_) {
      size_t index = hash_function(key);
      if (!filter_[index]) {
        return false;
      }
    }
    return true;
  }

  double false_positive_rate() {
    return std::pow(
        1 - std::exp(-static_cast<double>(num_hash_functions_ * num_elements_) /
                     filter_size_),
        num_hash_functions_);
  }
};

int main() {
  BloomFilter bloomFilter(1000, 0.01);

  // Insert some elements into the filter
  bloomFilter.insert("apple");
  bloomFilter.insert("banana");
  bloomFilter.insert("cherry");

  // Check if some elements are present in the filter
  std::cout << "Contains 'apple': " << bloomFilter.contains("apple")
            << std::endl; // Should be 1 (true)
  std::cout << "Contains 'banana': " << bloomFilter.contains("banana")
            << std::endl; // Should be 1 (true)
  std::cout << "Contains 'cherry': " << bloomFilter.contains("cherry")
            << std::endl; // Should be 1 (true)
  std::cout << "Contains 'durian': " << bloomFilter.contains("durian")
            << std::endl; // Should be 0 (false)

  // Calculate the false positive rate
  std::cout << "False positive rate: " << bloomFilter.false_positive_rate()
            << std::endl;

  return 0;
}
