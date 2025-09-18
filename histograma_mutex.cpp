#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include <fstream>
#include "generator.h"



// Histograma global protegido con mutex
std::vector<int> parallel_histogram_mutex(
    const std::vector<int>& data,
    int min_val,
    int max_val,
    int num_threads)
{
    if (num_threads < 1) num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    size_t chunk_size = data.size() / num_threads;
    int num_bins = max_val - min_val + 1;

    // Histograma global
    std::vector<int> global_histogram(num_bins, 0);
    std::mutex mtx;
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? data.size() : begin + chunk_size;
        // Cada hilo procesa su segmento de datos
        threads.emplace_back([begin, end, min_val, &data, &global_histogram, &mtx]() {
            for (size_t i = begin; i < end; ++i) {
                int bin = data[i] - min_val;
                // Sección crítica protegida con mutex
                std::lock_guard<std::mutex> lock(mtx);
                global_histogram[bin]++;
            }
        });
    }
    // Esperar a que todos los hilos terminen
    for (auto& th : threads) th.join();
    return global_histogram;
}


int main(int argc, char* argv[]) {
    // Configuración
    long int number_size = 100000000; // 100 millones
    int min_val = 1;
    int max_val = 1000;
    int seed = 42;

    std::cout << "Cantidad de vectores: " << number_size << std::endl;
    

    int num_threads = std::thread::hardware_concurrency();
    int user_input = num_threads; // valor por defecto

    // Si se pasa argumento, úsalo como número de hilos
    if (argc > 1) {
        int arg_threads = std::atoi(argv[1]);
        if (arg_threads >= 1 && arg_threads <= num_threads) {
            user_input = arg_threads;
        } else {
            std::cerr << "Número de hilos no válido. Usando el valor por defecto de " << num_threads << " hilos." << std::endl;
        }
    }

    std::cout << "Numero de hilos disponibles en el sistema: " << num_threads << std::endl;
    std::cout << "Numero de hilos utilizados: " << user_input << std::endl;

    auto data = generate_number_random_private(number_size, min_val, max_val, seed, user_input);

    // Medición del tiempo de ejecución
    auto start = std::chrono::high_resolution_clock::now();
    auto histogram = parallel_histogram_mutex(data, min_val, max_val, user_input);
    auto end = std::chrono::high_resolution_clock::now();

    // Mostrar algunos resultados del histograma
    for (int i = 0; i < 10 && i < histogram.size(); ++i)
        std::cout << "Bin " << i + min_val << ": " << histogram[i] << "\n";


    // Calcular el total de elementos en el histograma
    long total = 0;
    for (int bin : histogram) total += bin;
    std::cout << "Total elementos en el histograma: " << total << std::endl;

    // Mostrar el tiempo de ejecución
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos." << std::endl;
    return 0;
}