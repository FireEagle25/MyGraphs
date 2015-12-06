#pragma once
#include <iostream>
#include <list>
#include <queue>
#include "Vertex.h"
#include "Graph.h"
using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::add(int vertexId, int relatedVertexes[], int size) {
	for(int i = 0; i < size; i++) {
		Vertex currSearchVertex = this->findById(relatedVertexes[i]);
		if (currSearchVertex.GetId() == currSearchVertex.GetEmptyIndexValue()) {
			int* emptyArr = new int[0];
			Vertex newVertex(relatedVertexes[i], emptyArr, 0);
			graf.push_back(newVertex);
		}
	}

	std::list<Vertex>::iterator it = graf.begin();

	while (it!=graf.end())
	{
		if ( (*it).GetId() == vertexId) {
			(*it).AddRelatedVertexes(relatedVertexes, size);
			return;
		}
		it++;
	}

	Vertex newVertex(vertexId, relatedVertexes, size);
	graf.push_back(newVertex);

	return;
}

Vertex Graph::findById(int vertexId) {
	list<Vertex>::iterator it = graf.begin();
	while (it!=graf.end())
	{
		if ( (*it).GetId() == vertexId) 
			return *it;
		it++;
	}
	Vertex * nullVertex = new Vertex();
	return *nullVertex;
}

bool Graph::remove(int vertexId) {
	bool result = false;
	list<Vertex>::iterator it = graf.begin();
	while (it!=graf.end())
	{
		if ( (*it).GetId() == vertexId) {
			list<Vertex>::iterator it2 = it;
			it2++;
			it = graf.erase(it);
			result = true;
			it = it2;
			continue;
		}
		else
			it->RemoveRelatedId(vertexId);
		it++;
	}
	return result;
}

void Graph::BypassWide(int id) {
	list<int> used;
	used.push_back(id);

	queue<int> q;
	cout << id << " ";
	q.push(id);

	while (!q.empty()) {
		int id = q.front();
		q.pop();
		list<int> currRelatedIds = (findById(id)).GetRelatedIds();
		list<int>::iterator it = currRelatedIds.begin();
		while (it!=currRelatedIds.end())
		{
			int v = *it;
			if (!(find(begin(used), end(used), v) != end(used))) {
				used.push_back(v);
				cout << v << " ";
				q.push(v);
			}
			it++;
		}
	}
	cout << endl;
	return;
}