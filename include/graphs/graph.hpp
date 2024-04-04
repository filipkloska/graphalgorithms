#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <vector>
class Edge;

class Vertex
{
 public:
  int index;                            //indeks
  Vertex(int i){                        //konstruktor parametryczny
    index = i;
  } 
};

class Edge
{
 public:
  Vertex* source;                       //wskaźnik na element z którego wychodzi krawędź
  Vertex* destination;                  //wskaźnik na element do którego dochodzi krawędź
  int weight;                           //waga krawędzi
  Edge(Vertex* s, Vertex* d, int w)     //konstruktor parametryczny
  {
    source = s;
    destination = d;
    weight = w;
  }
};

class Graph
{
 public:
  std::size_t numberOfVertices;
  std::size_t numberOfEdges;
  virtual void addEdge(Vertex* source, Vertex* destination, int weight) = 0;
  virtual void printGraph() = 0;
  virtual ~Graph() {}
};

#endif /* GRAPH_HPP_ */
