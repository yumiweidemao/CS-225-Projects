#include "bfs.h"

/* 
   Given a set of edges, a start point and an end point, calculate one possible
   path between the two points.
   Parameters       edges: a vector containing Edge objects
                    size: the number of vertices
                    start: starting point id
                    end: end point id

   Return value     a vector of vertex ids representing the path from start to end 
*/
vector<int> bfs(const Graph & G, int start, int end) {
    queue<int> q;         // create a queue for BFS

    int size = G.getSize();
    if (size == 0) {
        return {};
    } else if (start < 0 || start >= size) {
        return {};
    } else if (end < 0 || end >= size) {
        return {};
    }

    /*
    4/19 update: since initialize a array with certain size can't be compiled in this version, I declared
    these following as vector
    */
    vector<bool> visited(size, false);   // visited[v] records if v has been visited
    vector<int> parent(size, -99);     // parent[v] records the vertex from which v is reached

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()) {
        // dequeue from queue
        int curr = q.front();
        q.pop();
        // check if the end point is reached, return path if reached
        if (curr == end) {
            vector<int> vec;
            while (curr != -1) {
                vec.push_back(curr);
                curr = parent[curr];
            }
            std::reverse(vec.begin(), vec.end());
            return vec;
        }
        // push all unvisited adjacent vertices of current vertex to queue
        for (int v : G.adjacentVertices(curr)) {
            if (visited[v] == 0) {
                visited[v] = 1;
                parent[v] = curr;
                q.push(v);
            }
        }
    }

    return {}; // endpoint not found, return an empty vector
}
