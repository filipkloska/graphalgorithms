#include <graphs/shortest_path_algorithms.hpp>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    
    int numVertices = graph.numberOfVertices;
    int maxValue = std::numeric_limits<int>::max(); 
    
    auto matrixGraph = dynamic_cast<AdjacencyMatrixGraph*>(&graph);
    auto listGraph = dynamic_cast<AdjacencyListGraph*>(&graph);
    
    std::vector<int> distance(numVertices, maxValue);//ustaw maksymalną wagę
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; /*priority queue, pierwszy argument to para wagi i indexu, drugi zawiera w sobie vector to trzymania,
                                                                                                                        trzeci powoduje że mniejsze wagi mają pierszeństwo*/
    distance[sourceIndex] = 0;                                  //ustaw wagę startowego na 0
    pq.push(std::make_pair(distance[sourceIndex], sourceIndex)); //wstaw do priority q

    result[sourceIndex] = std::make_pair(distance[sourceIndex], std::vector<int>{sourceIndex}); //wstaw do resulta początek 

    while (!pq.empty()) {
        int idx = pq.top().second;      //wyciągnij index 
        int dist = pq.top().first;    //wyciągnij wagę
        pq.pop();

        if (dist > distance[idx]) { //pomiń tą iterację jeśli dystans był zaktualizowany
            continue;   //pomija reszte pętli
        }

        if (matrixGraph) {          //przejdź przez wszystkie komórki macierzy sąsiedztwa
            for (int v = 0; v < numVertices; ++v) {
                if (matrixGraph->adjacencyMatrix[idx][v] != nullptr) {
                    int weight = matrixGraph->adjacencyMatrix[idx][v]->weight;


                    int newDistance = distance[idx] + weight;       //nowy dystans

                    if (newDistance < distance[v]) {                
                        distance[v] = newDistance;
                        result[v].first = newDistance;
                        result[v].second = result[idx].second;
                        result[v].second.push_back(v);
                        pq.push(std::make_pair(newDistance, v));
                    }
                }
            }
        } else if (listGraph) {
            for (const auto& edge : listGraph->incidenceList[idx]) { //przejdź przez całą listę incydencji
                int v = edge.first->index;
                int weight = edge.second;

                int newDistance = distance[idx] + weight; //nowy dystans

                if (newDistance < distance[v]) {        //jeśli nowy dystans mniejszy od starego to zaktualizuj
                    distance[v] = newDistance;
                    result[v].first = newDistance;
                    result[v].second = result[idx].second;
                    result[v].second.push_back(v);
                    pq.push(std::make_pair(newDistance, v));
                }
            }
        } else {
            std::cout << "Something went wrong with the graph type. End program" << std::endl;      
            return;
        }
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    auto matrixGraph = dynamic_cast<AdjacencyMatrixGraph*>(&graph);
    auto listGraph = dynamic_cast<AdjacencyListGraph*>(&graph);

    int numVertices = graph.numberOfVertices;
    int maxValue = std::numeric_limits<int>::max();
    result.clear();

    std::vector<int> distance(numVertices, maxValue);   //ustaw dystanse na nieskończone
    std::vector<int> previous(numVertices, -1);         //inicjuj poprzedniki na -1
    distance[sourceIndex] = 0;                          //początek ustaw na 0

    if (matrixGraph){
        for (int i = 0; i < numVertices - 1; ++i) {
            bool updated = false; //bool czy dystans został zaktualizowany
            for (int u = 0; u < numVertices; ++u) {         //przejdź przez wszystkie komórki macierzy sąsiedztwa
                 for (int v = 0; v < numVertices; ++v) {
                    if (matrixGraph->adjacencyMatrix[u][v] != nullptr) {
                        int weight = matrixGraph->adjacencyMatrix[u][v]->weight;

                        if (distance[u] != maxValue && distance[u] + weight < distance[v]) {    //jeśli nowy dystans mniejszy od starego
                            distance[v] = distance[u] + weight;         //relaksacja krawędzi
                            previous[v] = u;                            //ustaw obecny wektor jako poprzedni do następnych iteracji
                            updated = true;                             //zaznacz true
                        }
                    }
                }
            }
            if (!updated) {                     //jeżeli dystans nie został zaktualizowany to mamy najkrótszą ścieżkę i przerwij
                break;
            }
        }
        for (int u = 0; u < numVertices; ++u) {                     //sprawdzanie ujemnego cyklu
            for (int v = 0; v < numVertices; ++v) {
                if (matrixGraph->adjacencyMatrix[u][v] != nullptr) {
                    int weight = matrixGraph->adjacencyMatrix[u][v]->weight;
                    if (distance[u] != maxValue && distance[u] + weight < distance[v]) {        //jeśli istenieje krótsza ścieżka to koniec działania algorytmu z false
                        std::cout << "Negative-weight cycle detected" << std::endl;
                        return false;
                    }
                }
            }
        }
    }else if(listGraph){
        for (int i = 0; i < numVertices - 1; ++i) {
            bool updated = false;               //bool czy dystans został zaktualizowany
            for (int u = 0; u < numVertices; ++u) {
                for (const auto& edge : listGraph->incidenceList[u]) {  //przejdź przez całą listę incydencji
                    int v = edge.first->index;
                    int weight = edge.second;

                    if (distance[u] != maxValue && distance[u] + weight < distance[v]) {    //jeśli nowy dystans mniejszy od starego
                        distance[v] = distance[u] + weight;                                     //relaksacja krawędzi
                        previous[v] = u;
                        updated = true;                                     //zaznacz true
                    }
                }
            }
            if (!updated) {                                             //jeżeli dystans nie został zaktualizowany to mamy najkrótszą ścieżkę i przerwij
                break;
            }
        }
        for (int u = 0; u < numVertices; ++u) {                     //sprawdzanie ujemnego cyklu
            for (const auto& edge : listGraph->incidenceList[u]) {
                int v = edge.first->index;
                int weight = edge.second;


                if (distance[u] != maxValue && distance[u] + weight < distance[v]) { //jeśli istenieje krótsza ścieżka to koniec działania algorytmu z false
                     std::cout << "Negative-weight cycle detected" << std::endl;
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < numVertices; ++i) { //dodaj do mapy 
        result[i].first = distance[i];
        result[i].second.push_back(i);

        int prev = previous[i];
        while (prev != -1) {
            result[i].second.push_back(prev);
            prev = previous[prev];
        }

        std::reverse(result[i].second.begin(), result[i].second.end());
    }

    return true;
}
