#include "generator.h"



// Generate random numbers using multiple threads with private engines
std::vector<int> generate_number_random_private(long size, 
    int min_val, 
    int max_val, 
    int seed,
    int user_input) 
    {
    std::vector<int> data(size); //initialize vector 
    std::vector<std::thread> threads; //vector store the threads
    int num_threads = user_input > 0 ? user_input : std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4; // Default to 4 threads if hardware_concurrency cannot determine
    size_t chunk_size = size / num_threads; 

    for (int t = 0; t < num_threads; t++) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? size : begin + chunk_size;

        threads.emplace_back([begin, end,min_val,max_val,seed, t, &data]() {
            std::mt19937 eng(seed + t); // distint seed for each thread
            std::uniform_int_distribution<> distr(min_val, max_val);

            for (size_t i = begin; i < end; ++i) {
                data[i] = distr(eng); // Assign a random number to the vector
            }
        });
    }

    for (auto& th : threads) th.join();
    return data;
}
