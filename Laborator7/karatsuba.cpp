#include <iostream>
#include <math.h>
#include <chrono>
#include <random>

typedef unsigned long long caine;

caine recursive_multiply(caine x, caine y) {
    caine maximum = std::max(x, y);

    if (maximum <= 10)
        return x * y;

    caine digits = std::floor(std::log10(maximum)) + 1;
    caine power = std::pow(10, digits / 2);

    caine a = x / power;
    caine b = x % power;

    caine c = y / power;
    caine d = y % power;

    return recursive_multiply(a, c) * std::pow(10, digits / 2 * 2)
    + (recursive_multiply(a, d) + recursive_multiply(b, c)) * power
    + recursive_multiply(b, d);
}


caine recursive_multiply_fast(caine x, caine y) {
    caine maximum = std::max(x, y);

    if (maximum <= 10)
        return x * y;

    caine digits = std::floor(std::log10(maximum)) + 1;
    caine power = std::pow(10, digits / 2);

    caine a = x / power;
    caine b = x % power;

    caine c = y / power;
    caine d = y % power;

    caine ac = recursive_multiply(a, c);
    caine bd = recursive_multiply(b, d);
    caine mid = recursive_multiply(a + b, c + d) - ac - bd;

    return ac * std::pow(10, digits / 2 * 2)
    + mid * power
    + bd;
}

constexpr caine MAX_NUMBER = 10e8;
constexpr caine ITERATIONS = 10e5;
caine number_a[ITERATIONS] = {0}, number_b[ITERATIONS] = {0};

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, MAX_NUMBER);

    for (caine i = 0; i < ITERATIONS; ++i) {
        number_a[i] = dist(rng);
        number_b[i] = dist(rng);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (caine i = 0; i < ITERATIONS; ++i) {
        caine c = number_a[i] * number_b[i];
    }
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "no functions time: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";





    start = std::chrono::high_resolution_clock::now();
    for (caine i = 0; i < ITERATIONS; ++i) {
        caine c = recursive_multiply(number_a[i], number_b[i]);
    }
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "clasic time: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";





    start = std::chrono::high_resolution_clock::now();
    for (caine i = 0; i < ITERATIONS; ++i) {
        caine c = recursive_multiply_fast(number_a[i], number_b[i]);
    }
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "optimized time: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
}
