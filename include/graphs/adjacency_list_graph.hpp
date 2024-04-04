#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>
#include <list>
#include <vector>
#include "graph.hpp"

class AdjacencyListGraph : public Graph
{
 public:
    std::vector<std::vector<std::pair<Vertex*, int>>> incidenceList;            //wektor dwuwymiarowy gdzie pierwszym elementem jest destination, a drugim waga wierzchołka
    AdjacencyListGraph(std::size_t numberOfVertices, std::size_t numberOfEdges);  //konstruktor
    void addEdge(Vertex* source, Vertex* destination, int weight) override;   //dodanie krawędzi
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    void printGraph() override;
    ~AdjacencyListGraph();
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
