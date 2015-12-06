#pragma once
#include <algorithm>
#include "Vertex.h"
using namespace std;

int Vertex::GetEmptyIndexValue() {
	return EMPTY_INDEX;
}

Vertex::Vertex(int inpId, int inpRelatedIds[], int size) {
	id = inpId;
	for(int i = 0; i < size; i++)
		relatedIds.push_back(inpRelatedIds[i]);
}

Vertex::Vertex() {
	id = EMPTY_INDEX;
}

Vertex::Vertex(int inpId) {
	id = inpId;
}

int Vertex::GetId() {
	return id;
}

void Vertex::AddRelatedVertexes(int inpRelatedIds[], int size) {
	for(int i = 0; i < size; i++)
		AddRelatedVertex(inpRelatedIds[i]);
}

bool Vertex::RemoveRelatedId(int relatedId) {
	if (find(begin(relatedIds), end(relatedIds), relatedId) != end(relatedIds)) {
		relatedIds.remove(relatedId);
		return true;
	}
	return false;
}

bool Vertex::AddRelatedVertex(int newVertexId) {
	bool isContainSameVertex = false;
	list<int>::iterator it = relatedIds.begin();
	while (it!=relatedIds.end())
	{
		if ( (int)*it == newVertexId) {
			isContainSameVertex = true;
			return false;
		}
		it++;
	}
	relatedIds.push_back(newVertexId);
	return true;
}