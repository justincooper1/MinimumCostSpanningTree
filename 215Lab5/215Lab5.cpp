#include "Graph.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int v = 0;
    int temp = 0;

    fstream input;
    input.open("matrix.txt");

    while (input >> temp)
        v++;

    input.close();

    Graph* graph = new Graph((int)sqrt(v));
    int* mark = new int[(int)sqrt(v)];

    //Initial graph
    cout << "Number of vertices is " << graph->numVertices() << endl;
    cout << "Number of edges is " << graph->numEdges() << endl;

    // Read matrix from file
    graph->read();
    graph->Print();

    //MST 1
    int start = 0;
    cout << "Begin MST 1 starting at Vertex 0" << endl << endl;

    graph->read();
    Prim(graph, mark, start);
    graph->write("matrixoutput.txt");
    cout << "Number of vertices is " << graph->numVertices() << endl;
    cout << "Number of edges is " << graph->numEdges();
    graph->Print();

    //MST 2  
    graph->init(sqrt(v));
    for (int i = 0; i < sqrt(v); i++)
        mark[i] = INFINITY;

    start = 3;
    mark[start] = 0;
    cout << "Begin MST 2 starting at Vertex 3" << endl << endl;

    graph->read();
    Prim(graph, mark, start);
    graph->write("matrixoutput2.txt");
    cout << "Number of vertices is " << graph->numVertices() << endl;
    cout << "Number of edges is " << graph->numEdges();
    graph->Print();

    //MST 3
    graph->init(sqrt(v));
    for (int i = 0; i < sqrt(v); i++)
        mark[i] = INFINITY;

    start = 5;
    mark[start] = 0;
    cout << "Begin MST 3 starting at Vertex 5" << endl << endl;

    graph->read();
    Prim(graph, mark, start);
    graph->write("matrixoutput3.txt");
    cout << "Number of vertices is " << graph->numVertices() << endl;
    cout << "Number of edges is " << graph->numEdges();
    graph->Print();


    delete graph;
    delete[] mark;

    system("pause");
    return 0;
}
