#pragma once

#define INF 99999999

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<double, int> iPair; // first is distance, second is vertex id

class Dijkstra{
    private:
        int V;
        int source_;
        list <iPair> * adj;
        vector<double> distance_;
        vector<int> predecessor_;
        //initialize a vector for recording path
        vector<int>* pathRecording_;
    public:
        Dijkstra(int V){
            // handle invalid input
            if (V <= 0) {
                this->V = 0;
                this->adj = NULL;
                this->pathRecording_ = NULL;
                return;
            }

            this->V = V;
            this->adj = new list<iPair> [V];
            this->pathRecording_ = NULL;
        }

        ~Dijkstra() {
            if (adj != NULL) {
                delete[] adj;
            }
            if (pathRecording_ != NULL) {
                delete[] pathRecording_;
            }
            adj = NULL;
            pathRecording_ = NULL;
        }

        void addEdge(int u, int v, double w){
            if (u >= V || v >= V || u < 0 || v < 0) {
                return;
            }
            adj[u].push_back(make_pair(w, v));
            adj[v].push_back(make_pair(w, u));
        }


        void shortestPath(int source){
            if (source >= V || source < 0) {
                return;
            }
            source_ = source;
            //declare the priQ
            priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
            //initialize all distances as infinite
            vector<double> distance(V, INF);
            //initialize a vector for Predecessor
            vector<int> predecessor(V, -1);
            //insert source in priority queue
            //initialize its distance as 0
            pq.push(make_pair(0, source));
            distance[source] = 0;
            predecessor[source] = source;

            while(!pq.empty()){
                //vertex label is sotred in the second of the pair
                int u = pq.top().second;
                pq.pop();
                list<iPair>::iterator itr;
                for(itr = adj[u].begin(); itr != adj[u].end(); itr++){
                    //get vertex label and weight
                    int v = itr->second;
                    double weight = itr->first;
                    //check if there is shorter path from u to v
                    if(distance[v] > distance[u] + weight){
                        distance[v] = distance[u] + weight;
                        pq.push(make_pair(distance[v], v));
                        predecessor[v] = u;
                    }
                }
            }
            //copy the result to class variables
            predecessor_ = predecessor;
            distance_ = distance;         
            //declare an array of vector for recording paths of each vertex to the source
            vector<int>* pathRecording = new vector<int>[V];    
            //looping all vertices
            for(int i = 0; i < V; i ++){
                int v = i;
                pathRecording[i].push_back(v);
                while(true){
                    int pred = predecessor_[v];
                    pathRecording[i].push_back(pred);
                    if(pred == source_) break;
                    v = pred;
                }
                std::reverse(pathRecording[i].begin(),pathRecording[i].end());
            }
            pathRecording_ = pathRecording;
        }


        vector<int> getPathTo(int e){
            if (e >= V || e < 0) {
                return {};
            }
            return pathRecording_[e];
        }


};
