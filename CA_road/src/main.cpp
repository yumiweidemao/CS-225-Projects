#include "../include/datareader.h"
#include "../include/graph.h"
#include "../include/dijkstra.h"
#include "../include/brandes.h"
#include "../include/drawBC.h"
#include <iostream>
#include <limits>

using cs225::PNG;
using cs225::HSLAPixel;

const int NUM_VERTICES = 21048; // number of vertices


int main(int argc, char ** argv) {

    vector<Edge> edges = readEdges("dataset/caledge_modified.txt");      // load edges
    Graph G(NUM_VERTICES, edges);                               // create a graph

    int start, end;
    // Read start vertex
    std::cout << "Enter a start point (integer from 0-21047): ";
    while (!(std::cin >> start) || !(0 <= start && 21047 >= start)) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "Invalid start point, please enter a new point\n";
        std::cout << "Enter an start point (integer from 0-21047): ";
    }
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Read end vertex
    std::cout << "Enter an end point (integer from 0-21047): ";
    while (!(std::cin >> end) || !(0 <= end && 21047 >= end)) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "Invalid end point, please enter a new point\n";
        std::cout << "Enter an end point (integer from 0-21047): ";
    }
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Run Dijkstra
    Dijkstra d(NUM_VERTICES);
    for (Edge e : edges) {
        d.addEdge(e.getStart(), e.getEnd(), e.getWeight());
    }
    d.shortestPath(start);//generate shortest path to any given position and store in private variable
    vector<int> d_path = d.getPathTo(end);
    vector<double> d_weightVector = G.getAccumulateWeight(d_path);
    double d_totalWeight = G.getTotalWeight(d_path);
    std::cout << "The length of the path is " << d_totalWeight << "km." << std::endl;
    string d_filename = std::to_string(start) + "_to_" + std::to_string(end) + ".txt";
    writeVertices(d_filename, d_path, d_weightVector);
    std::cout << "\n";

    // Choose whether to run Brandes
    char key = '\0';
    while (std::cout << "Run Brandes? [y/n] : " && (!(std::cin >> key) || (key != 'y' && key != 'n'))) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Run Brandes
    if (key == 'y') {
        std::cout << "\nYour CPU has " << std::thread::hardware_concurrency() << " cores." << std::endl;
        std::cout << "Number of cores you'd like to use:  ";
        int n_threads;
        while (!(std::cin >> n_threads) || !(n_threads >= 0 && n_threads <= std::thread::hardware_concurrency())) {
            std::cout << "Invalid, enter again! Number of cores you'd like to use:  ";
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        std::cout << "Running Brandes algorithm on the whole dataset...\n" << std::endl;
        vector<double> BC = brandes(G, n_threads);
        ofstream ofs("brandes_results.txt");

        auto largest = std::max_element(BC.begin(), BC.end());
        ofs << "Largest betweenness centrality at vertex " << std::distance(BC.begin(), largest) << std::endl << std::endl;

        ofs << "Vertex" << "\t" << "Betweenness Centrality" << std::endl;
        for (int i = 0; i < NUM_VERTICES; i++) {
            ofs << i << "\t" << BC[i] << std::endl;
        }

        std::cout << "\nBrandes results saved to brandes_results.txt.\n" << std::endl;

        vector<vector<double> > vertices = readVertices("dataset/calnode.txt");

        drawBC(vertices, BC, G, edges.size());
        std::cout << "Betweenness centrality graph saved to BC_graph.png.\n" << std::endl;
    }
    
    return 0;
}
