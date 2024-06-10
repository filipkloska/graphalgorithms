#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "adjacency_matrix_graph.cpp"
#include "adjacency_list_graph.cpp"
#include "minimum_spanning_tree_algorithms.cpp"
#include "shortest_path_algorithms.cpp"


void testLISTGRAPH(){
    std::ifstream inputFile("../mst_data/graph/graphV10D0.5.txt");
    if (!inputFile) {
        std::cout << "Failed to open the input file." << std::endl;
        return;
    }

    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(inputFile);
    inputFile.close();

    if (graph) {
        graph->printGraph();
    } else {
        std::cout << "Failed to create the graph." << std::endl;
        return;
    }

    return;
}
void testMATRIXGRAPH(){
    std::ifstream inputFile("../mst_data/graph/graphV10D0.5.txt");
    if (!inputFile) {
        std::cout << "Failed to open the input file." << std::endl;
        return;
    }

    std::unique_ptr<Graph> graph = AdjacencyMatrixGraph::createGraph(inputFile);
    inputFile.close();

    if (graph) {
        graph->printGraph();
    } else {
        std::cout << "Failed to create the graph." << std::endl;
        return;
    }

    return;
}

void createRandomGraph(std::ofstream& ograph, int nVertex, float density){
    //density = numberOfEdges/(nVertex*(nVertex-1)) wzór
    int numberOfEdges = density*(nVertex*(nVertex-1));
    ograph << nVertex << " " << numberOfEdges << std::endl;
    int counter = numberOfEdges;
    int losowaliczba;
    int randomx;
    int randomy;
    int maxDepth = 10;

    bool bul[nVertex][nVertex];
    for(int x = 0; x < nVertex; ++x){
        for(int y = 0; y <nVertex; ++y){
            bul[x][y] = false;
        }
    }
    for(int i = 0; i < nVertex; ++i){
        bul[i][i] = true;
    }

    

    while(counter > 0){
        if(maxDepth <= 0){

            for(int x = 0; x < nVertex; ++x){
                for(int y = 0; y < nVertex; ++y){
                    if(x!=y && bul[x][y] != true){
                        bul[x][y] = true;
                        losowaliczba = rand() % nVertex;
                        ograph << x << " " << y << " " << losowaliczba << std::endl;
                        counter--;
                        maxDepth = 10;
                        goto breakLoop;
                    }
                }
            }

        }

        randomx = rand()%nVertex;
        randomy = rand()%nVertex;
        if(bul[randomx][randomy] != true){
            bul[randomx][randomy] = true;
            losowaliczba = rand() % (2*nVertex);
            ograph << randomx << " " << randomy << " " << losowaliczba << std::endl;
            counter--;
            maxDepth = 10;
        }
        --maxDepth;
        breakLoop:{}
    }
}

void EfficiencyTestSP(){
float density_array[] = {0.25, 0.5, 0.75, 1};
    int nVerters_array[] = {10, 50, 100, 250, 500, 1000};
    std::ifstream igraph;
    std::ofstream ograph;
    std::ofstream timegraph;
    srand(time(NULL));
    timegraph.open("czastrwaniaSP.txt");
    for(int nVerters : nVerters_array){
        timegraph << "rozmiar: " << nVerters << std::endl;
        for(float density : density_array){
            timegraph << "density: " << density << std::endl;
            for(int i = 0; i < 10; ++i){
                ograph.open("losowygrafSP.txt");
                createRandomGraph(ograph, nVerters, density);
                ograph.close();
                igraph.open("losowygrafSP.txt");
                auto graphbase = AdjacencyMatrixGraph::createGraph(igraph);
                auto &graph = dynamic_cast<AdjacencyMatrixGraph&>(*graphbase);
                ShortestPathResult wynik;
                auto start_time = std::chrono::high_resolution_clock::now();
                int sourceIndex = rand() % nVerters;
                dijkstra(graph, sourceIndex,wynik);
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                timegraph << duration << std::endl;
                igraph.close();
            }
        }
    }
    timegraph.close();
}



int main(int argc, char* argv[])
{
    EfficiencyTestSP();
    return 0;
}
