#include <iostream>
#include <vector>
#include <thread>
#include <random>


// Generate random numbers using multiple threads with private engines
std::vector<int> generate_number_random_private(long size, int min_val, int max_val, int seed, int user_input);

