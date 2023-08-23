#include "bst.h"

int main() {
    bst<int, int> tree;

    tree.insert({1, 3});
    tree.insert({3, 5});
    tree.insert({2, 4});

    return 0;
}