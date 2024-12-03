#pragma once

#include "book.h"
#include "GraphADT.h"
#include <fstream>
#include <string>
#include <memory>
#include <vector>

class Graph : public GraphADT
{
private:
	int numVertex;
	int numEdge;
	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;
	std::unique_ptr<int[]> mark;

public:
	Graph(int vertices)
	{
		init(vertices);
	}
	~Graph() = default;

	void init(int n)
	{
		numVertex = n;
		numEdge = 0;
		mark = std::make_unique<int[]>(numVertex);

		for (int i = 0; i < numVertex; i++)
			mark[i] = UNVISITED;

		matrix = std::make_unique<std::unique_ptr<int[]>[]>(numVertex);

		for (int i = 0; i < numVertex; i++)
			matrix[i] = std::make_unique<int[]>(numVertex);

		for (int i = 0; i < numVertex; i++)
			for (int j = 0; j < numVertex; j++)
				matrix[i][j] = 0;
	}

	int numVertices()
	{
		return numVertex;
	}

	int numEdges()
	{
		return numEdge;
	}

	int neighbor(int v)
	{
		for (int i = 0; i < numVertex; i++)
		{
			if (matrix[v][i] != 0)
			{
				return i;
			}
		}
		return numVertex;
	}

	int nextNeighbor(int v, int w)
	{

	}
};