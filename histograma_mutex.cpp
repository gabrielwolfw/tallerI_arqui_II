#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include "generator.h"


// Histograma global protegido con mutex
std::vector<int> parallel_histogram_mutex(
    const std::vector<int>& data,
    int min_val,
    int max_val,
    int user_input)
{
    int num_threads = user_input > 0 ? user_input : std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    size_t chunk_size = data.size() / num_threads;
    int num_bins = max_val - min_val + 1;

    std::vector<int> global_histogram(num_bins, 0);
    std::mutex mtx;
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? data.size() : begin + chunk_size;

        threads.emplace_back([begin, end, min_val, &data, &global_histogram, &mtx]() {
            for (size_t i = begin; i < end; ++i) {
                int bin = data[i] - min_val;
                // Protección con mutex
                std::lock_guard<std::mutex> lock(mtx);
                global_histogram[bin]++;
            }
        });
    }
    for (auto& th : threads) th.join();
    return global_histogram;
}


int main() {
    long int number_size = 100000000; //100 millones
    int min_val = 1;
    int max_val = 1000;
    int seed = 42;

    std::cout << "Cantidad de vectores: " << number_size << std::endl;
    int total_number_threads = std::thread::hardware_concurrency();
    int user_input;

    std::cout << "Numero de hilos: ";
    std::cin >> user_input;
    if (user_input < 1 || user_input > 16) {
        std::cerr << "Número de hilos no válido. Usando el valor por defecto de " << total_number_threads << " hilos." << std::endl;
        user_input = total_number_threads;
    }

    auto data = generate_number_random_private(number_size, min_val, max_val, seed, user_input);

    auto start = std::chrono::high_resolution_clock::now();
    auto histogram = parallel_histogram_mutex(data, min_val, max_val, user_input);
    auto end = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10 && i < histogram.size(); ++i)
        std::cout << "Bin " << i + min_val << ": " << histogram[i] << "\n";

    long total = 0;
    for (int bin : histogram) total += bin;
    std::cout << "Total elementos en el histograma: " << total << std::endl;

    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos." << std::endl;

    return 0;
}