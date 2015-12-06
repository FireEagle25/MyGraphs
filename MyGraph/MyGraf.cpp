#include <iostream>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

int main() {
	Graph *newgraph = new Graph();
	int a[3] = {1,2,3};
	newgraph->Add(1,a,3);
	int b[8] = {1,2,3,6,7,99,32,56};
	newgraph->Add(3,b,8);
	int c[2] = {1,2};
	newgraph->Add(134,c,2);

	newgraph->Remove(2);

	Vertex a1 = newgraph->FindById(1);

	newgraph->BypassWide(1);
	system("pause");
	return 0;
}