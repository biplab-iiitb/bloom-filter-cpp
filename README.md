# Bloom Filter

This code defines a Bloom filter, which is a probabilistic data structure used for efficient membership testing. The Bloom filter is initialized with the expected number of elements and the desired false positive rate. It calculates the number of hash functions and the size of the filter based on these parameters. The filter is then resized and the hash functions are generated using lambda expressions.

## Usage

To use the Bloom filter, follow these steps:

1. Create an instance of the `BloomFilter` class by providing the expected number of elements and the false positive rate as parameters in the constructor.

2. Insert elements into the filter using the `insert` method. Pass the element as a parameter.

3. Check if an element is present in the filter using the `contains` method. Pass the element as a parameter.

4. Calculate the false positive rate of the filter using the `false_positive_rate` method.

## Example

Here's an example usage of the Bloom filter:

In this example, a Bloom filter is created with an expected number of elements of 1000 and a false positive rate of 0.01. Three elements, "apple", "banana", and "cherry", are inserted into the filter. The `contains` method is used to check if certain elements are present in the filter. Finally, the `false_positive_rate` method is called to calculate the false positive rate of the filter.

Note: The false positive rate represents the probability that the filter incorrectly reports an element as being present when it is not.