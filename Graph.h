#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <vector>
#include <algorithm>


class Graph
{
public:
	std::vector<int>* verteces;
	int e;
	int v;

	Graph(char* NameOfFile)
	{
		v = e = 0;

		file.open(NameOfFile, std::ios::in);
		file >> v;
		verteces = new std::vector<int>[v];
		int a, b;
		while (file >> a >> b)
		{
			if (a > v || b > v)
			{
				std::cout << "ignoruje krawedz " << a << " " << b << std::endl;
				continue;
			}
			verteces[a].push_back(b);
			if (a != b)
				verteces[b].push_back(a);
			++e;
		}
		file.close();
	}
	Graph(const Graph& other)
	{
		v = other.v;
		e = other.e;
		verteces = new std::vector<int>[v];
		verteces = other.verteces;
	}
	~Graph()
	{
		delete[] verteces;
	}


private:
	std::fstream file;
	//char *NameOfFile;
};

class Isomorphism
{

	typedef int value_type;
	/*struct Compare {
		Compare(const Isomorphism& c) : Isomorphism(c) {}
		bool operator () ( int a, int b )
		{
			return permutationTab[a] < permutationTab[b];
		 }
		Isomorphism& Isomorphism;
	};*/
public:
	static int* permutationTab;

	Graph firstGraph;
	Graph secondGraph;
	Isomorphism(char* f, char* s) : firstGraph(f), secondGraph(s)
	{

	}

	~Isomorphism()
	{

	}

	bool isTheSameDegreeList()
	{
		int degsFirstGraph[firstGraph.v];
		int degsSecondGraph[secondGraph.v];

		for (int i = 0; i < firstGraph.v; i++)
		{
			degsFirstGraph[i] = firstGraph.verteces[i].size();
			degsSecondGraph[i] = secondGraph.verteces[i].size();
		}
		std::sort(degsFirstGraph, degsFirstGraph + firstGraph.v);
		std::sort(degsSecondGraph, degsSecondGraph + secondGraph.v);

		for (int i = 0; i < firstGraph.v; i++)
			if (degsFirstGraph[i] != degsSecondGraph[i])
				return false;

		return true;
	}

	static bool permutationTabOrder(int a, int b)
	{
		return permutationTab[a] < permutationTab[b];
	}

	bool checkPermutation()
	{
		for (int i = 0; i < firstGraph.v; i++)
		{
			if (firstGraph.verteces[i].size() != secondGraph.verteces[permutationTab[i]].size())
				return false;

			std::sort(firstGraph.verteces[i].begin(), firstGraph.verteces[i].end(), permutationTabOrder);
			//std::sort(firstGraph.verteces[i][0], firstGraph.verteces[i][firstGraph.v], Compare(*this));
			for (size_t j = 0; j < firstGraph.verteces[i].size(); j++)
				if (permutationTab[firstGraph.verteces[i][j]] != secondGraph.verteces[permutationTab[i]][j])
					return false;
		}
		return true;
	}

	bool isItIsomorphic()
	{
		//checks if there is the same number of vertices and edges
		if (firstGraph.v != secondGraph.v || firstGraph.e != secondGraph.e)
			return false;

		//checks if the lists of degrees of vertices of both graphs are the same
		if (!isTheSameDegreeList())
			return false;

		for (int i = 0; i < secondGraph.v; i++)
			std::sort(secondGraph.verteces[i].begin(), secondGraph.verteces[i].end());

		do
		{
			if (checkPermutation())
				return true;
		} while (std::next_permutation(permutationTab, permutationTab + firstGraph.v));


		return false;

	}
};




#endif //GRAPH_H