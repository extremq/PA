#include <iostream>
#include <random>
#include <queue>
#include <vector>
#include <chrono>
#include <algorithm>

long long swaps = 0;
long long comps = 0;

void insertion_sort(int start, int gap, int arr[], int length) {
    for (int i = start; i < length; i += gap) {
        int temp = arr[i];
        int k = i;

        while (k - gap >= start && arr[k] < arr[k - gap]) {
            ++comps;
            ++swaps;
            std::swap(arr[k], arr[k - gap]);
            k -= gap;
        }
    }
}

void radix(int arr[], int length) {
    std::vector<std::queue<int>> queues(10);

    int max = 0;
    // First pass also determines word size
    for (int i = 0; i < length; ++i) {
        max = std::max(arr[i], max);

        int digit = arr[i] % 10;
        queues[digit].push(arr[i]);
    }

    int k = 0;
    for(int i = 0; i < 10; ++i) {
        // Empty each queue and reconstruct vector
        while (!queues[i].empty()) {
            int top = queues[i].front();
            queues[i].pop();

            arr[k++] = top;
        }
    }
    // First pass ended, know the word size is known

    // yes i am subtracting 1 after adding for clarity
    // since we already did a pass, it is no longer necessary
    int word_size = floor(log10(max)) + 1 - 1;
    int remainder = 100;
    while(word_size--) {
        // Now just get each digit from each number
        for (int i = 0; i < length; ++i) {
            int digit = arr[i] % remainder / (remainder / 10);
            queues[digit].push(arr[i]);
        }

        int k = 0;
        for(int i = 0; i < 10; ++i) {
            // Empty each queue and reconstruct vector
            while (!queues[i].empty()) {
                int top = queues[i].front();
                queues[i].pop();

                arr[k++] = top;
            }
        }

        remainder *= 10;
    }
}

int main() {
    int n = 100000;
    int v[100000], w[100000], u[100000], x[100000];

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,n);

    // worst case insertion 4999950000 = n * (n-1) / 2
    // worst case shell     1250000000 = unsure

    for (int i = 0; i < n; ++i) {
        v[i] = w[i] = u[i] = x[i] = dist(rng);
        // v[i] = w[i] = n - i;
    }

    //////////////////// INSERTION
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(0, 1, v, n);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru insertion\nswaps: " << swaps << "\ncomps: " << comps << "\ntime: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END INSERTION

    swaps = 0;
    comps = 0;

    //////////////////// SHELL
    start = std::chrono::high_resolution_clock::now();
    insertion_sort(0, 4, w, n);
    insertion_sort(1, 4, w, n);
    insertion_sort(2, 4, w, n);
    insertion_sort(3, 4, w, n);
    insertion_sort(0, 3, w, n);
    insertion_sort(1, 3, w, n);
    insertion_sort(2, 3, w, n);
    insertion_sort(0, 1, w, n);
    stop = std::chrono::high_resolution_clock::now();  

    std::cout << "pentru shell\nswaps: " << swaps << "\ncomps: " << comps << "\ntime: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END SHELL

    //////////////////// RADIX
    start = std::chrono::high_resolution_clock::now();
    radix(u, n);
    stop = std::chrono::high_resolution_clock::now(); 

    std::cout << "pentru radix\ntime: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n"; 

    //////////////////// END RADIX

    //////////////////// SORT ALGORITHM
    start = std::chrono::high_resolution_clock::now();
    std::sort(x, x + n);
    stop = std::chrono::high_resolution_clock::now(); 

    std::cout << "pentru sort\ntime: " 
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END SORT ALGORITHM

}
