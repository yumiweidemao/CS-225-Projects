#pragma once

#include <vector>
#include <iostream>
#include "edge.h"

using std::vector;

class Graph {
    public:
        /***** Constructor functions *****/
        Graph() {list_ = NULL; size_ = 0;}
        Graph(int size) {list_ = NULL; size_ = size;}
        Graph(int size, const vector<Edge> & edges) {
            size_ = size;
            list_ = NULL;
            _load(size_, edges);
        }
        Graph(const Graph & other) {_copy(other);}
        ~Graph() {_destroy();}

        /***** Utility functions *****/
        /* Return a vector of incident edges of the given vertex id. */
        const vector<Edge> incidentEdges(int id) const {
            if (id >= size_ || list_ == NULL || id < 0) {return {};}
            return this->list_[id];
        }

        /* Return a vector of vertex ids adjacent to the given vertex id. */
        vector<int> adjacentVertices(int id) const {
            if (id >= size_) {return {};}
            vector<int> adj;
            for (Edge e : incidentEdges(id)) {
                if (e.getStart() == id) {
                    adj.push_back(e.getEnd());
                } else {
                    adj.push_back(e.getStart());
                }
            }
            return adj;
        }

        /* Return the degree of the given vertex id. Return -1 if vertex DNE. */
        int getDegree(int id) const {
            if (id >= size_) {return -1;}
            return incidentEdges(id).size();
        }

        /* Return the weight of the edge connecting v1 and v2. If edge does not
           exist, return -1. */
        double getWeight(int v1, int v2) const {
            if (v1 >= size_ || v2 >= size_) {return -1;}
            for (Edge e : incidentEdges(v1)) {
                if (e.getStart() == v1 && e.getEnd() == v2) {
                    return e.getWeight();
                }
                if (e.getEnd() == v1 && e.getStart() == v2) {
                    return e.getWeight();
                }
            }
            return -1;
        }

        /* Return the total weight of the given path represented by a vector of vertex ids. */
        double getTotalWeight(const vector<int> & path) {
            if (path.empty()) {
                return 0;
            }
            double totalWeight = 0;
            for (unsigned i = 0; i < path.size() - 1; i++) {
                totalWeight += getWeight(path[i], path[i+1]);
            }
            return totalWeight;
        }

        vector<double> getAccumulateWeight(const vector<int> & path) {
            if (path.empty()) {
                return {};
            }
            vector<double> weightVector;
            for (unsigned i = 0; i < path.size() - 1; i++) {
                if(i == 0){
                    weightVector.push_back(getWeight(path[i], path[i+1]));
                }else{
                    weightVector.push_back(weightVector[i-1] + getWeight(path[i], path[i+1]));
                }                
            }
            return weightVector;
        }


        /* Loads a vector of edges to the graph. */
        void loadEdges(int size, const vector<Edge> & edges) {
            size_ = size;
            _load(size_, edges);
        }

        /* Return the number of vertices in the graph. */
        int getSize() const {
            return size_;
        }

        /* Get the adjacency list pointer of the graph. */
        vector<Edge> * getList() const {
            return list_;
        }

        /***** Operator overload functions *****/
        /* Assignment operator overload */
        Graph & operator=(const Graph & other) {
            if (&other == this) {
                return *this;
            }
            _destroy();
            _copy(other);
            return *this;
        }

        /* Returns a vector of incident edges of a given vertex id. */
        const vector<Edge> operator[](int idx) {
            if (idx >= size_) {return {};}
            return this->list_[idx];
        }

        /***** Helper functions *****/
        void _copy(const Graph & other) {
            size_ = other.getSize();
            list_ = new vector<Edge>[size_];
            for (int i = 0; i < size_; i++) {
                list_[i] = vector<Edge>(other.getList()[i].begin(), other.getList()[i].end());
            }    
        }

        void _destroy() {
            if (list_ != NULL) {
                delete[] list_;
            }
            list_ = NULL;
        }

        void _load(int size, const vector<Edge> & edges) {
            if (list_ != NULL) {
                _destroy();
                size_ = size;
            }
            if (size <= 0) {
                list_ = NULL;
                return;
            }
            list_ = new vector<Edge>[size_];
            for (Edge edge : edges) {
                list_[edge.getStart()].push_back(edge);
                list_[edge.getEnd()].push_back(edge);
            }
        }

    private:
        vector<Edge> * list_; // adjacency list
        int size_; // number of vertices in the graph
};
