#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <fstream>
#include "generator.h"

std::vector<int> histogram_reduction(
    const std::vector<int>& data,
    int min_val,
    int max_val,
    int num_threads) 
{
    if (num_threads < 1) num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    size_t chunk_size = data.size() / num_threads;
    int num_bins = max_val - min_val + 1;

    // Every thread has a private histogram
    std::vector<std::vector<int>> private_histograms(num_threads, std::vector<int>(num_bins, 0));
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? data.size() : begin + chunk_size;

        threads.emplace_back([begin, end, min_val, &data, &private_histograms, t]() {
            for (size_t i = begin; i < end; ++i) {
                int bin = data[i] - min_val;
                private_histograms[t][bin]++;
            }
        });
    }
    for (auto& th : threads) th.join();

    // Final reduction
    std::vector<int> global_histogram(num_bins, 0);
    for (int t = 0; t < num_threads; ++t) {
        for (int bin = 0; bin < num_bins; ++bin) {
            global_histogram[bin] += private_histograms[t][bin];
        }
    }
    return global_histogram;
}

int main(int argc, char* argv[]) {
    // Configuración
    long int number_size = 100000000;
    int min_val = 1;
    int max_val = 1000;
    int seed = 42;

    // Información del sistema
    std::cout << "Cantidad de vectores: " << number_size << std::endl;
    int max_threads = std::thread::hardware_concurrency();
    int num_threads = max_threads; // Valor por defecto

    // Lee el número de hilos del argumento de línea de comandos
    if (argc > 1) {
        int arg_threads = std::atoi(argv[1]);
        if (arg_threads >= 1 && arg_threads <= max_threads) {
            num_threads = arg_threads;
        } else {
            std::cerr << "Número de hilos no válido. Usando el valor por defecto de " << max_threads << " hilos." << std::endl;
        }
    }

    std::cout << "Numero de hilos disponibles en el sistema: " << max_threads << std::endl;
    std::cout << "Numero de hilos utilizados: " << num_threads << std::endl;

    auto data = generate_number_random_private(number_size, min_val, max_val, seed, num_threads);
    auto start = std::chrono::high_resolution_clock::now();
    auto histogram = histogram_reduction(data, min_val, max_val, num_threads);
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