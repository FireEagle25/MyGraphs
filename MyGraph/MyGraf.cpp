#include <iostream>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

int main() {
	Graph *newGraf = new Graph();
	int a[3] = {1,2,3};
	newGraf->add(1,a,3);
	int b[8] = {1,2,3,6,7,99,32,56};
	newGraf->add(3,b,8);
	newGraf->remove(2);

	Vertex a1 = newGraf->findById(1);

	newGraf->BypassWide(3);
	system("pause");
	return 0;
}