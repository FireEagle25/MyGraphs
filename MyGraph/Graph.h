#include <list>
#include <set>

class Graph
{
	public:
		Graph();
		~Graph();
		void Add(int, int[], int);
		Vertex FindById(int );
		bool Remove(int);
		void BypassWide(int);
		void PrintMaxIndependentSet();
	private:
		bool isNotNotContainNoOneVertexRelatedWithEveryVertexInCandidates(set<int> candidates, set<int> not);
		void Extend(set<int> candidates, set<int> not, set<int> compsub);
		list<Vertex> graph;
};