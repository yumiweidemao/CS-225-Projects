#pragma once

#include <algorithm>
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <queue>
#include <climits>
#include "PNG.h"
#include "dsets.h"

using sys_clock = std::chrono::system_clock;
using us = std::chrono::microseconds;
using std::chrono::duration_cast;
using cs225::PNG;
using cs225::HSLAPixel;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
        int idx(int x, int y) const;

        class Square {
            public:
                Square() {wall_r = 1; wall_d = 1; visited_ = 0; dist_ = INT_MAX; pos_ = -1;}
                Square(int pos) : Square() {pos_ = pos;}
                void set(bool b, int dir) {(dir ? wall_d : wall_r) = b;}
                bool get(int dir) const {return dir ? wall_d : wall_r;}
                void setVisited(bool b) {visited_ = b;}
                bool getVisited() const {return visited_;}
                void setDist(int dist) {dist_ = dist;}
                int getDist() const {return dist_;}
                void setPos(int pos) {pos_ = pos;}
                int getPos() const {return pos_;}
            private:
                bool wall_r;
                bool wall_d;
                bool visited_;
                int dist_;
                int pos_;
        };

    private:
        int width_;
        int height_;
        DisjointSets dset_;
        vector<Square> squares_;
};
