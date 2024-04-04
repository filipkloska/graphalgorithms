#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>
#include "graph.hpp"

class AdjacencyMatrixGraph : public Graph
{
  private:
  std::vector<Vertex*> vertices; //lista wszystkich wierzchołków
  public:
    std::vector<std::vector<Edge*>> adjacencyMatrix;  //macierz sąsiedztwa dwuwymiarowa, gdzie są wskaźniki na edge
    AdjacencyMatrixGraph(std::size_t numberOfVertices, std::size_t numberOfEdges); //konstruktor
    void addEdge(Vertex* source, Vertex* destination, int weight) override; //dodanie edgów
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    void printGraph() override;
    ~AdjacencyMatrixGraph();
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
