#include "../include/dsets.h"

/* Add {num} unconnected elements to the end of the array. */
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        this->vec_.push_back(-1);
    }
}

/* Given an int elem, return the root of the up-tree. */
int DisjointSets::find(int elem) {
    while (vec_[elem] >= 0) {
        elem = vec_[elem];
    }
    return elem;
}

/* Union the two uptrees containing elements a & b. */
void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    int size_a = vec_[root_a] * -1;
    int size_b = vec_[root_b] * -1;
    if (size_b <= size_a) {
        // point root of b to root of a
        vec_[root_b] = root_a;
        vec_[root_a] -= size_b;
    } else {
        // point root of a to root of b
        vec_[root_a] = root_b;
        vec_[root_b] -= size_a;
    }
}

/* Given an element, return the size of its uptree */
int DisjointSets::size(int elem) {
    return -1 * vec_[find(elem)];
}
