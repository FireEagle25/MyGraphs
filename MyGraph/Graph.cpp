#pragma once
#include <iostream>
#include <list>
#include <queue>
#include "Vertex.h"
#include "Graph.h"
using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::Add(int vertexId, int relatedVertexes[], int size) {
	for (int i = 0; i < size; i++) {
		Vertex currSearchVertex = this->FindById(relatedVertexes[i]);
		if (currSearchVertex.GetId() == currSearchVertex.GetEmptyIndexValue()) {
			int* emptyArr = new int[0];
			int relatedIdForCurrVertex[1] = {vertexId};
			Vertex newVertex(relatedVertexes[i], relatedIdForCurrVertex, 1);
			graph.push_back(newVertex);
		}
	}

	std::list<Vertex>::iterator it = graph.begin();

	bool isVertexInGraph = false;
	while (it!=graph.end())
	{
		if ( (*it).GetId() == vertexId) {
			(*it).AddRelatedVertexes(relatedVertexes, size);
			isVertexInGraph = !isVertexInGraph;
		}
		else
			for (int i = 0; i < size; i++)
				if ((*it).GetId() == relatedVertexes[i] && (*it).GetId() != vertexId) {
					int addingIdToAnotherVertexes[1] = {vertexId};
					(*it).AddRelatedVertexes(addingIdToAnotherVertexes, 1);
				}
		it++;
	}
	if(!isVertexInGraph) {
		Vertex newVertex(vertexId, relatedVertexes, size);
		graph.push_back(newVertex);
	}
}

Vertex Graph::FindById(int vertexId) {
	list<Vertex>::iterator it = graph.begin();
	while (it!=graph.end())
	{
		if ( (*it).GetId() == vertexId) 
			return *it;
		it++;
	}
	Vertex * nullVertex = new Vertex();
	return *nullVertex;
}

bool Graph::Remove(int vertexId) {
	bool result = false;
	list<Vertex>::iterator it = graph.begin();
	while (it!=graph.end())
	{
		if ( (*it).GetId() == vertexId) {
			list<Vertex>::iterator it2 = it;
			it2++;
			it = graph.erase(it);
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
		list<int> currRelatedIds = (FindById(id)).GetRelatedIds();
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

void Graph::PrintIndependentSets() {
}