#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

class Vertex
{
	public:

		Vertex(int inpId, int inpRelatedIds[], int size) {
			id = inpId;
			for(int i = 0; i < size; i++)
				relatedIds.push_back(inpRelatedIds[i]);
		}

		Vertex() {
			id = -1;
		}

		int getId() {
			return id;
		}

		void addRelatedVertexes(int inpRelatedIds[], int size) {
			for(int i = 0; i < size; i++)
				addRelatedVertex(inpRelatedIds[i]);
		}

	private:

		int id;
		list<int> relatedIds;

		bool addRelatedVertex(int newVertexId) {
			bool isContainSameVertex = false;
			std::list<int>::iterator it = relatedIds.begin();
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
};

class MyGraf
{
	public:

		MyGraf(){}

		~MyGraf(){}

		void add(int vertexId, int relatedVertexes[], int size) {
			std::list<Vertex>::iterator it = graf.begin();

			while (it!=graf.end())
			{
				if ( (*it).getId() == vertexId) {
					(*it).addRelatedVertexes(relatedVertexes, size);
					return;
				}
				it++;
			}

			Vertex newVertex(vertexId, relatedVertexes, size);
			graf.push_back(newVertex);

			return;
		}

		Vertex findById(int vertexId) {
			std::list<Vertex>::iterator it = graf.begin();
			while (it!=graf.end())
			{
				if ( (*it).getId() == vertexId) 
					return *it;
				it++;
			}
			Vertex * nullVertex = new Vertex();
			return *nullVertex;
		}

		bool remove(int vertexId) {
			std::list<Vertex>::iterator it = graf.begin();
			while (it!=graf.end())
			{
				if ( (*it).getId() == vertexId) {
					it = graf.erase(it);
					return true;
				}
				it++;
			}
			return false;
		}

	private:

		list<Vertex> graf;
};

int main() {
	MyGraf *newGraf = new MyGraf();
	int a[3] = {1,2,3};
	newGraf->add(1,a,3);
	newGraf->remove(2);

	Vertex a1 = newGraf->findById(2);
	system("pause");
	return 0;
}