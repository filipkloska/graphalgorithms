#include "../include/graphs/adjacency_list_graph.hpp"
#include <iostream>
AdjacencyListGraph::AdjacencyListGraph(std::size_t numOfVertices, std::size_t numOfEdges)
{
    numberOfVertices = numOfVertices;   //przypisywanie do parametrów grafu
    numberOfEdges = numOfEdges;
    incidenceList.resize(numberOfVertices); //zmiana wielkości listy incydencji
}
void AdjacencyListGraph::addEdge(Vertex* source, Vertex* destination, int w)
{
   incidenceList[source->index].emplace_back(destination, w);               //utwórz i wstaw do listy incydencji poprawny vertex końcowy
   delete source;                                                           // WAŻNE BO BEZ TEGO WYCIEKI DUŻE BYŁY
}
std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is) {
    
    std::size_t numOfVertices, numOfEdges;
    is >> numOfVertices >> numOfEdges;

    auto graph = std::make_unique<AdjacencyListGraph>(numOfVertices, numOfEdges);

    for (std::size_t i = 0; i < numOfEdges; i++) 
    {
        int source, destination, weight;
        is >> source >> destination >> weight;

        if (source < 0 || destination < 0 || source >= numOfVertices ||  destination >= numOfVertices) {  //sprawdzanie czy indexy są większe od 0, i czy nie wychodzą poza zadaną ilość wierzchołków
            std::cout << "Invalid vertex index!" << std::endl;
            return nullptr;
        }

        if (source == destination) {                                        //sprawdzanie czy to nie jest ten sam wierzchołek, jeśli jest to daj mu wagę 0
            graph->addEdge(new Vertex(source), new Vertex(destination), 0);
        } else {
            graph->addEdge(new Vertex(source), new Vertex(destination), weight); // dodaj krawędź o początku source, końcu destination i wyczytanej wagi
        }
    }

    return graph;
}
void AdjacencyListGraph::printGraph()
{
    std::cout << "Incidence List:\n";
    for (std::size_t i = 0; i < incidenceList.size(); i++) {
        std::cout << "Vertex " << i << ": ";
        for (auto edge : incidenceList[i]) {
            std::cout << edge.first->index << "(" << edge.second << ") ";
        }
        std::cout << "\n";
    }
}

AdjacencyListGraph::~AdjacencyListGraph() {
  // Deallocate memory for vertices in the incidence list
  for (auto& vertexEdges : incidenceList) {
    for (auto& edge : vertexEdges) {
      delete edge.first;
    }
    vertexEdges.clear(); // Usuń krawędzie z listy
  }
  incidenceList.clear(); // Zwolnij pamięć dla listy incydencji
}