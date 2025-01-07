#pragma once
#include "Node.h"


class Heap {

private:
	int count1 = 0;

	void heapify(Node*, int i);
	void swap(Node&, Node&);
	void decrease_heap_size(Node*);
	void build_heap(Node*);

public:
	void heap_sort(Node*);
	void display(Node*, int size);
	int getCount();
	void fill(Node*, int);

};