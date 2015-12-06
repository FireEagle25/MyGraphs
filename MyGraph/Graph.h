#include <list>

class Graph
{
	public:
		Graph();
		~Graph();
		void add(int, int[], int);
		Vertex findById(int );
		bool remove(int);
		void BypassWide(int);
	private:
		list<Vertex> graf;
};