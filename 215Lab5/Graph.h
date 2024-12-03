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
		for (int i = w + 1; i < numVertex; i++)
		{
			if (matrix[v][i] != 0)
			{
				return i;
			}
		}
		return numVertex;
	}

	void setWeight(int v1, int v2, int weight)
	{
		// Not sure if this works correctly yet
		if (weight <= 0)
		{
			throw std::invalid_argument("Illegal weight value");
		}

		if (matrix[v1][v2] == 0)
			numEdge++;

		matrix[v1][v2] = weight;
	}

	void deleteEdge(int v1, int v2)
	{
		if (matrix[v1][v2] != 0)
		{
			numEdge--;
		}
		matrix[v1][v2] = 0;
	}

	bool isEdge(int v1, int v2)
	{
		return matrix[v1][v2] != 0;
	}

	int weight(int v1, int v2)
	{
		return matrix[v1][v2];
	}

	int getMark(int v)
	{
		return mark[v];
	}

	void setMark(int v, int value)
	{
		mark[v] = value;
	}


};