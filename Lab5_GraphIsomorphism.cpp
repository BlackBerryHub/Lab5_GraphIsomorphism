#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<vector>
#include<fstream>
#include <fstream>
#include <vector>
#include <algorithm>


class Graph
{
public:
	std::vector<int>* verteces;
	int e;
	int v;

	Graph(const char *NameOfFile)
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
	char *NameOfFile;
};

class Isomorphism
{

	typedef int value_type;
public:
	static int* permutationTab;

	Graph firstGraph;
	Graph secondGraph;
	Isomorphism(const char *f, const char *s) : firstGraph(f), secondGraph(s)
	{

	}

	~Isomorphism()
	{

	}

	bool isTheSameDegreeList()
	{
		int degsFirstGraph[5];
		int degsSecondGraph[5];

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

int* Isomorphism::permutationTab = NULL;

int main()
{
	const char *file1 = "gr1.txt";
	const char* file2 = "gr2.txt";
    Graph firstGraph(file1);
    Graph secondGraph(file2);
    Isomorphism iso(file1,file2);

    Isomorphism::permutationTab = new int[firstGraph.v];
    for (int i = 0; i < firstGraph.v; i++)
        Isomorphism::permutationTab[i] = i;



    if (iso.isItIsomorphic())
    {
        std::cout << "Is Isomorf\n";
        for (int i = 0; i < iso.firstGraph.v; i++)
            std::cout << i << " --> " << Isomorphism::permutationTab[i] << "\n";
    }

    else
        std::cout << "Not Isomorf\n";

    delete[] Isomorphism::permutationTab;



    return 0;
}