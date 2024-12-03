#pragma once

class GraphADT
{
private:
	void operator=(const GraphADT&) {}
	GraphADT(const GraphADT&) {}

public:
	// Constructor and Destructor
	GraphADT() {}
	virtual ~GraphADT() {}

	// Initialize the graph
	virtual void init(int n) = 0;

	// Returns the number of vertices
	virtual int numVertices() = 0;

	// Returns the number of edges
	virtual int numEdges() = 0;

	// Returns the neighbor of v
	virtual int neighbor(int v) = 0;

	// Returns the next neighbor of v
	virtual int nextNeighbor(int v, int w) = 0;

	// Set the weight of an edge
	virtual void setWeight(int v1, int v2, int weight) = 0;

	// Deletes an edge
	virtual void deleteEdge(int v1, int v2) = 0;

	// Checks if an edge is in the graph
	virtual bool isEdge(int v1, int v2) = 0;

	// Return the weight of an edge
	virtual int weight(int v1, int v2) = 0;

	// Getters and setters for the mark value of a vertex
	virtual int getMark(int v) = 0;
	virtual int setMark(int v, int value) = 0;

	// From Prim's Algorithm
	virtual void AddEdgetoMST(int v1, int v2) = 0;
};