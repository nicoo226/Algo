#include <iostream>
#include <random>
#include "Heap.h"
#include "Node.h"

int length = 1000;

void Heap::heapify(Node* a, int i) {
    int max = i;
    int li = 2 * i;
    int re = 2 * i + 1;

    if (li <= length && a[li].key > a[max].key) {
        max = li;
    }
    if (re <= length && a[re].key > a[max].key) {
        max = re;
    }
    if (i != max) {
        swap(a[i], a[max]);
        heapify(a, max);
    }count1 += 3;
}

void Heap::heap_sort(Node* a) {
    build_heap(a);
    for (int i = length; i > 1; i--) {
        swap(a[1], a[i]);
        decrease_heap_size(a);
        heapify(a, 1);
    }
}

void Heap::build_heap(Node* a) {
    for (int i = length / 2; i > 0; i--) {
        heapify(a, i);
    }
}

void Heap::swap(Node& a, Node& b) {
    Node help = a;
    a = b;
    b = help;
}

void Heap::decrease_heap_size(Node* a){
    length--;
}

void Heap::display(Node* a,int size) {
    for (int i = 1; i <= size; i++) {
        cout << a[i].key << "  ";
        if (i % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void Heap::fill(Node* a, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for (int i = 1; i <= size; i++) {
        a[i].key = dis(gen);
    }
}

int Heap::getCount() {
    return count1;
}