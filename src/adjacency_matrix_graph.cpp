#include "../include/graphs/adjacency_matrix_graph.hpp"
#include <iostream>
AdjacencyMatrixGraph::AdjacencyMatrixGraph(std::size_t numOfVertices,std::size_t numOfEdges)
{
    numberOfVertices = numOfVertices;   //przyjmowanie parametrów grafu
    numberOfEdges = numOfEdges;
    
    vertices.resize(numberOfVertices, nullptr); //odpowiednia ilość listy vertices i wypełnienie nullptrami
    adjacencyMatrix.resize(numberOfVertices,std::vector<Edge*>(numberOfVertices,nullptr)); //dwuwymiarowa macierz wypełniona nullptrami z wielkością numberOfVertices x numberOfVertices
}

void AdjacencyMatrixGraph::addEdge(Vertex* source, Vertex* destination, int w)
{
    Edge* connection = new Edge(source,destination,w);
    adjacencyMatrix[source->index][destination->index] = connection; // wpisanie do macierzy wskaźnika na krawędź łączącą
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    std::size_t numOfVertices, numOfEdges;
    is >> numOfVertices >> numOfEdges;

    auto graph = std::make_unique<AdjacencyMatrixGraph>(numOfVertices, numOfEdges);

    for (std::size_t i = 0; i < numOfEdges; i++)
    {
        int source, destination, weight;
        is >> source >> destination >> weight;
        
        if (source < 0 || destination < 0 || source >= numOfVertices ||  destination >= numOfVertices) {  //sprawdzanie czy indexy są większe od 0, i czy nie wychodzą poza zadaną ilość wierzchołków
            std::cout << "Invalid vertex index!" << std::endl;
            return nullptr;
        }

        if (graph->vertices[source] == nullptr) {
            graph->vertices[source] = new Vertex(source);  //wpisz do listy wierzchołków nowy początek edge
        }

        if (graph->vertices[destination] == nullptr) {
            graph->vertices[destination] = new Vertex(destination); //wpisz do listy wierzchołków nowy koniec edge
        }

        graph->addEdge(graph->vertices[source], graph->vertices[destination], weight); //dodaj do macierzy sąsiedztwa nasze krawędzie
    }
    return graph;
}

void AdjacencyMatrixGraph::printGraph(){
    std::cout << "Adjacency Matrix:\n";
    for (std::size_t i = 0; i <= numberOfVertices-1; i++) {
        for (std::size_t j = 0; j <= numberOfVertices-1; j++) {
            if(adjacencyMatrix[i][j]!=nullptr){
                    std::cout << adjacencyMatrix[i][j]->weight << " ";
            }
            else{
                std::cout <<"0 ";    
            }
        }
        std::cout << "\n";
    }
}


AdjacencyMatrixGraph::~AdjacencyMatrixGraph() {
  for (auto vertex : vertices) {
    delete vertex;                  //usuń wszystkie vertexy z vertices
  }

  for (auto row : adjacencyMatrix) {
    for (auto edge : row) {
      delete edge;                 //usuń wszystkie edge z macierzy        
    }
  }
}