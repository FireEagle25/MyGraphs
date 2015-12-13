#include <iostream>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

int main() {
	Graph *newgraph = new Graph();
	int a[2] = {2,4};
	newgraph->Add(1,a,2);

	int b[2] = {3, 5};
	newgraph->Add(2,b,2);

	int c[1] = {4};
	newgraph->Add(3,c,1);

	int c2[2] = {6, 7};
	newgraph->Add(5,c2,2);

	newgraph->BypassWide(1);

	newgraph->PrintMaxIndependentSet();
	system("pause");
	return 0;
}