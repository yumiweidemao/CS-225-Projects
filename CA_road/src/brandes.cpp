#include "../include/brandes.h"

std::mutex mu; // for thread synchronization
int progress = 0; // record progress

vector<double> brandes(const Graph & g, unsigned int num_of_threads) {
    // limit number of threads to cpu cores
    if (num_of_threads > std::thread::hardware_concurrency()) {
        num_of_threads = std::thread::hardware_concurrency();
    }

    int size = g.getSize();

    vector<double> BC(size, 0); // Betweenness centrality

    int interval = size / num_of_threads;
    if (interval == 0) {
        std::cout << "Graph is too small for multithreading. Abort." << std::endl;
        return {};
    }

    vector<std::thread> threads;
    for (size_t i = 0; i < num_of_threads - 1; i++) {
        threads.push_back(std::thread(brandes_single_thread, std::ref(g), std::ref(BC), i*interval, (i+1)*interval, size));
    }

    threads.push_back(std::thread(brandes_single_thread, std::ref(g), std::ref(BC), (num_of_threads-1)*interval, size, size));

    for (std::thread & t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Normalize final result
    double BC_max = *std::max_element(BC.begin(), BC.end());
    double BC_min = *std::min_element(BC.begin(), BC.end());

    for (unsigned i = 0; i < BC.size(); i++) {
        BC[i] = (BC[i] - BC_min) / (BC_max - BC_min);
    }

    std::cout << std::endl;

    return BC;
}

void brandes_single_thread(const Graph & g, vector<double> & BC, int start, int end, int size) {
    // iterate through each vertex
    for (int s = start; s < end; s++) {
        // print progress bar
        {
        std::lock_guard<std::mutex> locker(mu);
        progress++;
        printProgress((double)progress / g.getSize());
        }

        vector<vector<int> > pred(size); // predecessor
        vector<double> delta(size, 0); // one-sided dependency
        vector<double> d(size, INF); // shortest distance, initialized to INF
        vector<int> sigma(size, 0);  // number of shortest distance

        sigma[s] = 1; // number of shortest path from s to s is 1
        d[s] = 0; // distance from s to s is 0

        std::set<std::pair<double, int> > q; // priority queue for Dijkstra
        std::stack<int> st; // for calculating delta
        q.insert(std::make_pair(0, s)); // enqueue the starting point

        /* Dijkstra SSSP algorithm */
        while (!q.empty()) {
            auto front = q.begin();
            int v = front->second; // current vertex
            q.erase(front); // pop
            st.push(v);
            for (int w : g.adjacentVertices(v)) {
                double weight = g.getWeight(v, w);
                if (d[w] > d[v] + weight) {
                    // enqueue and update w
                    q.erase(std::make_pair(d[w], w));
                    q.insert(std::make_pair(d[v] + weight, w));
                    d[w] = d[v] + weight;
                    pred[w].clear();
                    sigma[w] = 0;
                }
                // update sigma if d[w] is equal to d[v] + weight(v, w)
                if (d[w] == d[v] + weight) {
                    sigma[w] = sigma[w] + sigma[v];
                    pred[w].push_back(v);
                }
            }
        }
        /* End of Dijkstra SSSP algorithm */

        while (!st.empty()) {
            int w = st.top();            
            st.pop();
            for (int v : pred[w]) {
                delta[v] = delta[v] + (double)sigma[v] / (double)sigma[w] * (1.0 + delta[w]);
                
            }
            if (w != s) {
                std::lock_guard<std::mutex> locker(mu);
                BC[w] = BC[w] + delta[w];
            }
        }
    }
}
