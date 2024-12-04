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
			mark[i] = 0;

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

	void read() {
		std::fstream input("matrix.txt");
		std::string line;
		int r = 0, c = 0;
		numEdge = 0; // Reset edge count
		while (getline(input, line)) {
			c = 0; // Reset column index for each new row
			for (char ch : line) {
				if (ch != ' ') {
					int weight = ch - '0';
					matrix[r][c] = weight;
					if (weight != 0) {
						numEdge++;
					}
					c++;
				}
			}
			r++;
		}
		input.close();
		numEdge /= 2; // Every edge is counted twice in an undirected graph
	}

	void setWeight(int v1, int v2, int weight) {
		if (weight <= 0) {
			throw std::invalid_argument("Illegal weight value");
		}
		if (matrix[v1][v2] == 0 && weight != 0) {
			numEdge++;
		}
		else if (matrix[v1][v2] != 0 && weight == 0) {
			numEdge--;
		}
		matrix[v1][v2] = weight;
	}

	void deleteEdge(int v1, int v2) {
		if (matrix[v1][v2] != 0) {
			numEdge--;
		}
		matrix[v1][v2] = 0;
	}

	void AddEdgetoMST(int V, int v) {
		std::cout << "Add edge: " << V << " to " << v << std::endl;
		setWeight(V, v, matrix[V][v]);
		numEdge++;
	}


    void write(std::string file) {
        // Open file
        std::fstream output;
        output.open(file);

        for (int i = 0; i < numVertex; i++) {
            for (int j = 0; j < numVertex; j++) {
				if (matrix[i][j] == 9999)
				{
					matrix[i][j] = 0;
				}
					output << matrix[i][j];
					output << ' ';
            }

            output << std::endl;
        }

        // Close file
        output.close();
    }

    void Print() {
        std::cout << std::endl;

        for (int row = 0; row < numVertex; row++) {
            for (int col = 0; col < numVertex; col++) {
                std::cout << matrix[row][col];
                std::cout << " ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
};