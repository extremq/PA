#include "BTree.h"
int main() {
    BTree<3> my_tree;

    int numbers[] = {3, 1, 6, 9, 7, 2, 10, 4, 5, 8};

    for (int i = 0; i < 10; ++i) {
        std::cout << "inserting " << numbers[i] << '\n';
        my_tree.insert(numbers[i]);
        my_tree.print(my_tree.root);
    }

    return 0;
}
