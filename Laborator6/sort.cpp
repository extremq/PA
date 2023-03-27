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

int interclasare[100000];
void merge_sort(int start, int end, int arr[]) {
    if (start == end) {
        return;
    }

    int mid = (start + end) / 2;

    merge_sort(start, mid, arr);
    merge_sort(mid + 1, end, arr);

    int i = start;
    int j = mid + 1;

    int counter = 0;
    while(i <= mid && j <= end) {
        if (arr[i] < arr[j])
            interclasare[counter++] = arr[i++];

        else
            interclasare[counter++] = arr[j++];
    }

    while (i <= mid)
        interclasare[counter++] = arr[i++];

    while (j <= end)
        interclasare[counter++] = arr[j++];

    for (int k = start; k <= end; ++k) {
        arr[k] = interclasare[k - start];
    }
}

void printarr(int arr[], int l) {
    for (int i = 0; i < l; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

void quicksort(int start, int end, int arr[]) {
    if (start >= end) return;

    int pivot = arr[start];

    int left = start + 1, right = end;

    while (left <= right) {
        while (arr[left] <= pivot && left <= end) left++;
        while (arr[right] >= pivot && right >= start) right--;

        if (left < right && arr[left] > pivot && pivot > arr[right])
            std::swap(arr[left++], arr[right--]);
    }

    int new_pivot = left - 1;
    std::swap(arr[start], arr[new_pivot]);

    quicksort(start, new_pivot - 1, arr);
    quicksort(new_pivot + 1, end, arr);
}

#define N 1000000
int v[N], w[N], u[N], x[N], y[N], z[N];

int main() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,N);

    for (int i = 0; i < N; ++i) {
        v[i] = w[i] = u[i] = x[i] = y[i] = z[i] = dist(rng);
    }

    //////////////////// INSERTION
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(0, 1, v, N);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru insertion\nswaps: " << swaps << "\ncomps: " << comps << "\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END INSERTION

    swaps = 0;
    comps = 0;

    //////////////////// SHELL
    start = std::chrono::high_resolution_clock::now();
    insertion_sort(0, 4, w, N);
    insertion_sort(1, 4, w, N);
    insertion_sort(2, 4, w, N);
    insertion_sort(3, 4, w, N);
    insertion_sort(0, 3, w, N);
    insertion_sort(1, 3, w, N);
    insertion_sort(2, 3, w, N);
    insertion_sort(0, 1, w, N);
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru shell\nswaps: " << swaps << "\ncomps: " << comps << "\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END SHELL

    //////////////////// RADIX
    start = std::chrono::high_resolution_clock::now();
    radix(u, N);
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru radix\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";

    //////////////////// END RADIX

    //////////////////// MERGESORT
    start = std::chrono::high_resolution_clock::now();
    merge_sort(0, N - 1, y);
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru merge\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END MERGESORT

    //////////////////// QUICKSORT
    start = std::chrono::high_resolution_clock::now();
    quicksort(0, N - 1, z);
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru quick\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END QUICKSORT

    //////////////////// SORT ALGORITHM
    start = std::chrono::high_resolution_clock::now();
    std::sort(x, x + N);
    stop = std::chrono::high_resolution_clock::now();

    std::cout << "pentru sort\ntime: "
                << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    //////////////////// END SORT ALGORITHM

}
