#include <iostream>
#include "Node.h"
#include "Heap.h"

using namespace std;

int main() {

	const int size = 1000;

	Node a[size+1];
	Heap b;

	b.fill(a, size);
	b.display(a, size);
	b.heap_sort(a);
	b.display(a, size);
	cout << endl;
	int count = b.getCount();
	cout <<"Anzahl Vergleiche: "<< count;

	return 0;
}