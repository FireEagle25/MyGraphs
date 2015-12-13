#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include "Vertex.h"
#include "Graph.h"
using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

void Graph::Add(int vertexId, int relatedVertexes1[], int size1) {
	int size = size1 + 1;
	int* relatedVertexes = new int[size];

	for(int i = 0; i < size - 1; i++)
		relatedVertexes[i] = relatedVertexes1[i];
	relatedVertexes[size - 1] = vertexId;

	for (int i = 0; i < size; i++) {
		Vertex currSearchVertex = this->FindById(relatedVertexes[i]);
		if (currSearchVertex.GetId() == currSearchVertex.GetEmptyIndexValue()) {
			if (vertexId != relatedVertexes[i]) {
				int relatedIdForCurrVertex[2] = {vertexId, relatedVertexes[i]};
				Vertex newVertex(relatedVertexes[i], relatedIdForCurrVertex, 2);
				graph.push_back(newVertex);
			}
			else {
				int relatedIdForCurrVertex[1] = {vertexId};
				Vertex newVertex(relatedVertexes[i], relatedIdForCurrVertex, 1);
				graph.push_back(newVertex);
			}
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

/*
ПРОЦЕДУРА extend (candidates, not):
  ПОКА candidates НЕ пусто И not не содержит ни одной вершины, НЕ СОЕДИНЕННОЙ НИ С ОДНОЙ из вершин во множестве candidates, 
  ВЫПОЛНЯТЬ:
  1 Выбираем вершину v из candidates и добавляем ее в compsub
  2 Формируем new_candidates и new_not, удаляя из candidates и not вершины, СОЕДИНЕННЫЕ с v.
  3 ЕСЛИ new_candidates и new_not пусты
  4 ТО compsub – независимое множество
  5 ИНАЧЕ рекурсивно вызываем extend (new_candidates, new_not)
  6 Удаляем v из compsub и candidates, и помещаем в not
  */

void Graph::PrintMaxIndependentSet() {
	set<int> allVertexes = set<int>();
	list<Vertex>::iterator it = graph.begin();
	while (it != graph.end()) {
		allVertexes.insert((*it).GetId());
		it++;
	}
	cout << "-------------------------------------" << endl;
	cout << "Max independent sets: " << endl;
	Extend(allVertexes, set<int>(), set<int>());
	cout << "-------------------------------------" << endl;
}

void Graph::Extend(set<int> candidates, set<int> not, set<int> compsub) {
	while (candidates.size() > 0 && isNotNotContainNoOneVertexRelatedWithEveryVertexInCandidates(candidates, not)) {
		int v = *(candidates.begin());
		candidates.erase(v);
		compsub.insert(v);

		set<int> new_candidates = set<int>();
		set<int> new_not = set<int>();

		list<int> relatedWithVVertexes = FindById(v).GetRelatedIds();

		//Формируем new_candidates
		set<int>::iterator it1 = candidates.begin();
		while (it1 != candidates.end()) {
			list<int>::iterator it2 = relatedWithVVertexes.begin();
			bool isCurrVertexRelatedWithV = false;
			while (it2 != relatedWithVVertexes.end()) {
				if ((*it2) == (*it1)) {
					isCurrVertexRelatedWithV = true;
				}
				it2++;
			}
			if(!isCurrVertexRelatedWithV)
				new_candidates.insert(*it1);
			it1++;
		}

		//Формируем new_not
		set<int>::iterator it = not.begin();
		while (it != not.end()) {
			list<int>::iterator it2 = relatedWithVVertexes.begin();
			bool isCurrVertexRelatedWithV = false;
			while (it2 != relatedWithVVertexes.end()) {
				if ((*it2) == (*it)) {
					isCurrVertexRelatedWithV = true;
				}
				it2++;
			}
			if(!isCurrVertexRelatedWithV)
				new_not.insert(*it);
			it++;
		}

		if (new_candidates.size() == 0 && new_not.size() == 0) {
			set<int>::iterator it3 = compsub.begin();
			while (it3 != compsub.end()) {
				cout << (*it3) << " ";
				it3++;
			}
			cout << endl;
		}
		else
			Extend(new_candidates, new_not, compsub);

		candidates.erase(v);
		compsub.erase(v);
		not.insert(v);

	}
}

bool Graph::isNotNotContainNoOneVertexRelatedWithEveryVertexInCandidates(set<int> candidates, set<int> not) {
	//not не содержит ни одной вершины, НЕ СОЕДИНЕННОЙ НИ С ОДНОЙ из вершин во множестве candidates => true
	set<int> relatedInNotVertexes = set<int>();

	set<int>::iterator it = candidates.begin();
	while (it != candidates.end()) {
		Vertex currVertex = FindById((*it));
		list<int> currRelatedVetexes = currVertex.GetRelatedIds();
		list<int>::iterator it2 = currRelatedVetexes.begin();
		while (it2 != currRelatedVetexes.end()) {
			relatedInNotVertexes.insert(*it2);
			it2++;
		}
		it++;
	}

	set<int>::iterator it2 = relatedInNotVertexes.begin();
	while (it2 != relatedInNotVertexes.end()) {
		if (!not.count(*it2) > 0)
			return true;
		it2++;
	}
	return false;
}