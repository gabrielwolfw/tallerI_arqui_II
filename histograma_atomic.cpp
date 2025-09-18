#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <atomic>
#include <chrono>
#include "generator.h"

// Histograma global utilizando variables atómicas
std::vector<int> parallel_histogram_atomic(
    const std::vector<int>& data,
    int min_val,
    int max_val,
    int num_threads)
{
    if (num_threads < 1) num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    size_t chunk_size = data.size() / num_threads;
    int num_bins = max_val - min_val + 1;

    std::vector<std::atomic<int>> global_histogram(num_bins);  // Histograma global con atómicos
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? data.size() : begin + chunk_size;

        threads.emplace_back([begin, end, min_val, &data, &global_histogram]() {
            for (size_t i = begin; i < end; ++i) {
                int bin = data[i] - min_val;
                global_histogram[bin]++;  // Incrementa de forma atómica
            }
        });
    }
    for (auto& th : threads) th.join();
    // Convertir los valores atómicos a enteros regulares para el histograma final
    std::vector<int> final_histogram(global_histogram.size());
    for (int i = 0; i < num_bins; ++i) {
        final_histogram[i] = global_histogram[i];
    }
    return final_histogram;
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

    // Generación de datos aleatorios
    auto data = generate_number_random_private(number_size, min_val, max_val, seed, num_threads);

    // Medición del tiempo de ejecución
    auto start = std::chrono::high_resolution_clock::now();
    auto histogram = parallel_histogram_atomic(data, min_val, max_val, num_threads);
    auto end = std::chrono::high_resolution_clock::now();

    // Imprimir los primeros 10 resultados del histograma
    for (int i = 0; i < 10 && i < histogram.size(); ++i)
        std::cout << "Bin " << i + min_val << ": " << histogram[i] << "\n";

    // Verificación de la cantidad total de elementos en el histograma
    long total = 0;
    for (int bin : histogram) total += bin;
    std::cout << "Total elementos en el histograma: " << total << std::endl;

    // Mostrar el tiempo de ejecución
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos." << std::endl;

    return 0;
}
