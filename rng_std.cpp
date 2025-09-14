#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <thread>


int generate_number_random(long size) {
    std::vector<int> data(size);

    std::vector<std::thread> threads;
    int num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = size / num_threads;

    for (int t = 0; t < num_threads; t++) {
        size_t begin = t * chunk_size;
        size_t end = (t == num_threads - 1) ? size : begin + chunk_size;

        threads.emplace_back([begin, end, t, &data]() {
            std::random_device rd;
            std::mt19937 eng(rd() + t); // Semilla distinta por hilo
            std::uniform_int_distribution<> distr(1, 100000000);

            for (size_t i = begin; i < end; ++i) {
                data[i] = distr(eng);
            }
        });
    }

    for (auto& th : threads) th.join();

    // Ejemplo: imprime los primeros 5 números
    for (int i = 0; i < 10 && i < size; ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;

    return 0;
}


int main(){
    long int number_size = 100000000;
    generate_number_random(number_size);
    return 0;
}
