#include <iostream>
#include <vector>

class List {
    class Node {
    public:
        Node* prev;
        Node* next;
        int data;

    public:
        Node() : prev(nullptr), next(nullptr), data(0) {};
    };
    Node* head;
    int length;
public:
    List() : head(nullptr), length(0) {};
    void insert(int value, int position = 0) {
        if (position > length) {
            return;
        }

        if (position < -1) {
            return;
        }

        Node* new_node = new Node;
        new_node->data = value;

        if (position == 0) {
            new_node->next = head;
            
            if (head != nullptr) {
                head->prev = new_node;
            }

            head = new_node;
        }
        else {
            Node* iter = head;
            for(int i = 0; i < position - 1; ++i, iter = iter->next);

            if (iter->next)
                iter->next->prev = new_node;
            new_node->next = iter->next;

            iter->next = new_node;
            new_node->prev = iter;
        }

        ++length;
        return;
    }

    void print() {
        Node* iter = head;

        while (iter != nullptr) {
            std::cout << iter->data << ' ';
            iter = iter->next;
        }

        std::cout << '\n';
        return;
    }
};

void rotate_trigonometrically(std::vector<std::vector<int>> &mat, int n) {
    // Transpose
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(mat[i][j], mat[j][i]);
        }
    }

    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n; ++j) {
            std::swap(mat[i][j], mat[n - i - 1][j]);
        }
    }
}

int main() {
    List shobi;
    shobi.insert(1);
    shobi.insert(2);
    shobi.insert(3, 1);
    shobi.insert(4, 3);
    shobi.print();


    std::vector<std::vector<int>> mat(3, std::vector<int>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat[i][j] = i * 3 + j + 1;
        }
    }
    rotate_trigonometrically(mat, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
