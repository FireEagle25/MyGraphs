#include <list>

class Graph
{
	public:
		Graph();
		~Graph();
		void Add(int, int[], int);
		Vertex FindById(int );
		bool Remove(int);
		void BypassWide(int);
		void PrintIndependentSets();
	private:
		list<Vertex> graph;
};