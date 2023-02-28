#include <iostream>
#include <stdlib.h>
#include <time.h>

class CircularList {
    class Node {
    public:
        Node* next;
        int data;

        Node() : next(nullptr), data(0) {};
    };

    Node* start;
    Node* end;

    void create_head(int data) {
        start = new Node;
        start->next = start;
        end = start;
    }
public:
    long long counter;
    CircularList() : start(nullptr), end(nullptr), counter(0) {};

    void ionescu_style_insert(int data) {
        ++counter;
        if (start == nullptr) {
            create_head(data);
            return;
        }
        Node* new_node = new Node;
        new_node->data = data;
        new_node->next = start;
        end->next = new_node;
        end = new_node;
    }

    void popescu_style_insert(int data) {
        ++counter;
        if (start == nullptr) {
            create_head(data);
            return;
        }
        Node* iter = start;
        ++counter;
        while (iter->next != start) {
            iter = iter->next;
            ++counter;
        }

        Node* new_node = new Node;
        new_node->data = data;
        new_node->next = start;
        iter->next = new_node;
    }

    void popescu_new_style_insert(int data) {
        ++counter;
        if (start == nullptr) {
            create_head(data);
            return;
        }

        Node* new_node = new Node;
        new_node->data = data;
        std::swap(new_node->data, start->data);

        new_node->next = start->next;
        start->next = new_node;
        start = new_node;
    }

    void print() {
        Node* iter = start;
        while (iter->next != start) {
            std::cout << iter->data << ' ';
            iter = iter->next;
        }
        std::cout << iter->data << '\n';
    }
};

int main() {
    clock_t start, finish;
    double result, elapsed_time;

    CircularList ionescu, popescu, popescu_mai_bun;
    start = clock();
    for(int i = 0; i < 100000; ++i) {
        ionescu.ionescu_style_insert(i);
    }
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;   
    std::cout << "Ionescu a stat " << elapsed_time << " sec.\n";
    std::cout << "Ionescu a folosit " << ionescu.counter << " operatii.\n";

    start = clock();
    for(int i = 0; i < 100000; ++i) {
        popescu.popescu_style_insert(i);
    }
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;   
    std::cout << "Popescu a stat " << elapsed_time << " sec.\n";
    std::cout << "Popescu a folosit " << popescu.counter << " operatii.\n";

    std::cout << "Popescu acum cere ajutorul colegului Zamfir.\n";

    start = clock();
    for(int i = 0; i < 100000; ++i) {
        popescu_mai_bun.popescu_new_style_insert(i);
    }
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;   
    std::cout << "Popescu a stat " << elapsed_time << " sec.\n";
    std::cout << "Popescu a folosit " << popescu_mai_bun.counter << " operatii.\n";
    
}
