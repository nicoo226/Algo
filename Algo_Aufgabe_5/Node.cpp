#include <iostream>
#include <random>
#include "Node.h"

void Node::fill(Node*a) {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 1000);

	for (int i = 1; i <= size; i++) {
		a[i].key = dis(gen);
	}
}