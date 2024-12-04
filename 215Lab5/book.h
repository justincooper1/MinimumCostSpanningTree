// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// A collection of various macros, constants, and small functions
// used for the software examples.

// First, include all the standard headers that we need
#include <iostream>
#include <cstdlib>
#include <time.h>  // Used by timing functions
#include <string>
#include <memory>

#include "GraphADT.h"
#include "Graph.h"

using namespace std;

#define UNVISITED = 0;
#define VISITED = 1;

// Now all the standard names that we use
using std::cout;
using std::endl;
using std::string;
using std::ostream;

const int defaultSize = 10; // Default size

// Return true iff "x" is even
inline bool EVEN(int x) { return (x % 2) == 0; }

// Return true iff "x" is odd
inline bool ODD(int x) { return (x % 2) != 0; }

// Assert: If "val" is false, print a message and terminate
// the program
void Assert(bool val, string s) {
  if (!val) { // Assertion failed -- close the program
    cout << "Assertion Failed: " << s << endl;
    exit(-1);
  }
}

// Swap two elements in a generic array
template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}
// Random number generator functions

inline void Randomize() // Seed the generator
  { srand(1); }

// Return a random value in range 0 to n-1
inline int Random(int n)
  { return rand() % (n); }


// Swap two integers
inline void swap(int& i, int& j) {
  int temp = i;
  i = j;
  j = temp;
}

// Swap two char*'s
inline void swap(char* i, char* j) {
  char* temp = i;
  i = j;
  j = temp;
}


// Big enough for simple testing
#define INFINITY 9999

// Timing variables and functions
unsigned tstart = 0;  // Time at beginning of timed section

// Initialize the program timer
void Settime() { tstart = (unsigned) clock(); }

// Return the elapsed time since the last call to Settime
double Gettime() {
  unsigned tcurr = (unsigned) clock();
  return (double)(tcurr - tstart)/(double)CLOCKS_PER_SEC;
}

// Your basic int type as an object.
class Int {
private:
  int val;
public:
  Int(int input=0) { val = input; }
  // The following is for those times when we actually
  //   need to get a value, rather than compare objects.
  int key() const { return val; }
  // Overload = to support Int foo = 5 syntax
  Int operator= (int input) { val = input; return val; }
};

// Let us print out Ints easily
ostream& operator<<(ostream& s, const Int& i)
  { return s << i.key(); }
ostream& operator<<(ostream& s, const Int* i)
  { return s << i->key(); }

// Find min cost vertex
int minVertex(GraphADT* G, int* D)
{
    int i, v = -1;

    for (i = 0; i < G->numVertices(); i++)
    {
        if (G->getMark(i) == UNVISITED)
        {
            v = i; break;
        }
    }

    for (i++; i < G->numVertices(); i++)
    {
        if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
            v = i;
    }

    return v;
}

void setMatrix(GraphADT* graph, int start, int* weights, int* vertices)
{
    int less = INFINITY;
    int index = 0;

    // increment through each row
    for (int row = 0; row < graph->numVertices(); row++)
    {
        if (row != start)
        {
            // go to each item in the row
            for (int col = row + 1; col < graph->numVertices(); col++)
            {
                if (vertices[row] == col && vertices[row] > 0)
                    graph->setWeight(row, col, weights[row]);
                else
                {
                    graph->deleteEdge(row, col);
                    graph->deleteEdge(col, row);
                }
            }
        }

        else
        {
            for (int col = row; col < graph->numVertices(); col++)
            {
                // if least needs to be updated
                if (less > graph->weight(row, col) &&
                    graph->weight(row, col) != 0)
                {
                    less = graph->weight(row, col);
                    index = col;
                }

                // if less is less than current item weight
                else if (less < graph->weight(row, col))
                {
                    graph->deleteEdge(row, col);
                    graph->deleteEdge(col, row);
                }
            }

            // deletes values before less
            for (int p = row; p < index; p++)
            {
                if (less != graph->weight(p, row))
                {
                    graph->deleteEdge(row, p);
                    graph->deleteEdge(p, row);
                }
            }

            // set the edge
            graph->setWeight(row, index, less);
        }
    }

}

void Prim(GraphADT* G, int* D, int s)
{
    unique_ptr<int[]> V(new int[G->numVertices()]);
    int i, w;

    for (int i = 0; i < G->numVertices(); i++)
        D[i] = INFINITY;

    D[s] = 0;

    for (i = 0; i < G->numVertices(); i++)
    {
        int v = minVertex(G, D);

        G->setMark(v, VISITED);


        if (v != s)
            G->AddEdgetoMST(V[v], v);

        if (D[v] == INFINITY)
            return;

        for (w = G->neighbor(v); w < G->numVertices(); w = G->nextNeighbor(v, w))
        {
            if (D[w] > G->weight(v, w))
            {
                D[w] = G->weight(v, w);
                V[w] = v;
            }
        }
    }

    // sets graph matrix
    setMatrix(G, s, D, V.get());
}