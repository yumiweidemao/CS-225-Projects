#pragma once

#include <ostream>

class Edge {
    public:
        /* Constructor functions */
        Edge() {;}
        Edge(int idx, int start, int end) {idx_ = idx; start_ = start; end_ = end;}
        Edge(int idx, int start, int end, double weight) {
            idx_ = idx;
            start_ = start;
            end_ = end;
            weight_ = weight;
        }

        /* Member variable handling functions */
        void setStart(int start) {start_ = start;}
        void setEnd(int end) {end_ = end;}
        void setWeight(double weight) {weight_ = weight;}
        int getStart() const {return start_;}
        int getEnd() const {return end_;}
        double getWeight() const {return weight_;}
        int getIdx() const{return idx_;}

        /* Operator overload functions */
        bool operator<(const Edge & other) {
            return (weight_ < other.weight_);
        }
        bool operator==(const Edge & other) {
            return (weight_ == other.weight_);
        }
        bool operator>(const Edge & other) {
            return (weight_ > other.weight_);
        }
        friend std::ostream & operator<<(std::ostream & os, const Edge & edge) {
            os << "(" << edge.getStart() << ")--" << edge.getWeight() << "--(" << edge.getEnd() << ")";
            return os;
        }
    private:
        int idx_;
        int start_;
        int end_;
        double weight_;
};
