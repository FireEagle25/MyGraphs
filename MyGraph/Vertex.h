#pragma once
#include <list>
using namespace std;

class Vertex
{
	public:
		int GetEmptyIndexValue();

		Vertex(int inpId, int inpRelatedIds[], int size);

		Vertex();

		Vertex(int inpId);

		int GetId();

		void AddRelatedVertexes(int inpRelatedIds[], int size);

		bool RemoveRelatedId(int relatedId);

		list<int> GetRelatedIds() {
			return relatedIds;
		}
	private:
		const static int EMPTY_INDEX = -1;
		int id;
		list<int> relatedIds;

		bool AddRelatedVertex(int newVertexId);
};