#include "../include/maze.h"

SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}

/* make a width*height maze */
void SquareMaze::makeMaze(int width, int height) {
    sys_clock clock;  // use a time stamp in nanoseconds
    std::srand(duration_cast<us>(clock.now().time_since_epoch()).count());         // use time as random seed
    width_ = width;
    height_ = height;
    dset_ = DisjointSets();
    dset_.addelements(width*height);
    while (!squares_.empty()) {squares_.pop_back();}
    for (int i = 0; i < width*height; i++) {
        squares_.push_back(Square(i));
    }
    // delete random walls until no more walls can be deleted
    int cycle_count = 0;
    int target = width*height/4; // randomly remove some walls
    while (cycle_count <= target) {
        int dir = std::rand() % 2;
        int i = std::rand() % width;
        int j = std::rand() % height;
        if (squares_[idx(i, j)].get(dir) == false) {
            ++cycle_count;
            continue; // the wall is already removed
        }
        if (dir == 0 && i == width-1) {
            continue; // out of bounds
        }
        if (dir == 1 && j == height-1) {
            continue; // out of bounds
        }
        int index = dir ? idx(i, j+1) : idx(i+1, j);
        if (dset_.find(idx(i, j)) == dset_.find(index)) {
            ++cycle_count; // loop detected
            continue;
        } else {
            dset_.setunion(idx(i, j), index);
            squares_[idx(i, j)].set(false, dir);
        }
        cycle_count = 0;
    }
    // delete the rest that can be deleted
    for (int dir = 0; dir <= 1; dir++) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (squares_[idx(x, y)].get(dir) == false) {
                    continue; // the wall is already removed
                }
                if (dir == 0 && x == width-1) {
                    continue; // out of bounds
                }
                if (dir == 1 && y == height-1) {
                    continue; // out of bounds
                }
                int index = dir ? idx(x, y+1) : idx(x+1, y);
                if (dset_.find(idx(x, y)) != dset_.find(index)) {
                    dset_.setunion(idx(x, y), index);
                    squares_[idx(x, y)].set(false, dir);
                }
            }
        }
    }
}

/* Return true if square(x, y) can travel in dir, false otherwise. */
bool SquareMaze::canTravel(int x, int y, int dir) const {
    int curr = idx(x, y);
    if (dir == 0) {
        if (x == width_ - 1) {return false;}
        return !squares_[curr].get(dir);
    } else if (dir == 1) {
        if (y == height_ - 1) {return false;}
        return !squares_[curr].get(dir);
    } else if (dir == 2) {
        if (x == 0) {return false;}
        return !squares_[curr-1].get(0);
    } else if (dir == 3) {
        if (y == 0) {return false;}
        return !squares_[idx(x, y-1)].get(1);
    }
    return false;
}

/* Set the <dir> wall at (x, y) to <exists> */
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    squares_[idx(x, y)].set(exists, dir);
}

/* Return a vector of directions representing a solution to the maze. */
vector<int> SquareMaze::solveMaze() {
    vector<int> sol;
    std::queue<Square> q;
    squares_[0].setVisited(true); // set root as visited
    squares_[0].setDist(0);       // set root distance = 0
    q.push(squares_[0]);
    while (!q.empty()) {
        Square curr = q.front();
        q.pop();
        int x = curr.getPos() % width_;
        int y = curr.getPos() / width_;
        if (canTravel(x, y, 0) && !squares_[idx(x+1, y)].getVisited()) {
            squares_[idx(x+1, y)].setVisited(true);
            q.push(squares_[idx(x+1, y)]); // travel rightward
        }
        if (canTravel(x, y, 1) && !squares_[idx(x, y+1)].getVisited()) {
            squares_[idx(x, y+1)].setVisited(true);
            q.push(squares_[idx(x, y+1)]); // travel downward
        }
        if (canTravel(x, y, 2) && !squares_[idx(x-1, y)].getVisited()) {
            squares_[idx(x-1, y)].setVisited(true);
            q.push(squares_[idx(x-1, y)]); // travel leftward
        }
        if (canTravel(x, y, 3) && !squares_[idx(x, y-1)].getVisited()) {
            squares_[idx(x, y-1)].setVisited(true);
            q.push(squares_[idx(x, y-1)]); // travel upward
        }
        // assign shortest distance to origin
        int shortest_dist = INT_MAX;
        // check left square
        if (x > 0) {
            if (canTravel(x-1, y, 0)) {
                if (squares_[idx(x-1, y)].getDist() < shortest_dist) {
                    shortest_dist = squares_[idx(x-1, y)].getDist();
                }
            }
        }
        // check right square
        if (x < width_ - 1) {
            if (canTravel(x+1, y, 2)) {
                if (squares_[idx(x+1, y)].getDist() < shortest_dist) {
                    shortest_dist = squares_[idx(x+1, y)].getDist();
                }
            }
        }
        // check up square
        if (y > 0) {
            if (canTravel(x, y-1, 1)) {
                if (squares_[idx(x, y-1)].getDist() < shortest_dist) {
                    shortest_dist = squares_[idx(x, y-1)].getDist();
                }
            }
        }
        // check down square
        if (y < height_ - 1) {
            if (canTravel(x, y+1, 3)) {
                if (squares_[idx(x, y+1)].getDist() < shortest_dist) {
                    shortest_dist = squares_[idx(x, y+1)].getDist();
                }
            }
        }
        if (curr.getPos() != 0) {
            squares_[idx(x, y)].setDist(shortest_dist+1);
        }
    }
    // find the largest distance to origin and travel from that point to origin
    int largest_dist = -1, largest_x = -1;
    for (int x = 0; x < width_; x++) {
        if (squares_[idx(x, height_-1)].getDist() > largest_dist) {
            largest_dist = squares_[idx(x, height_-1)].getDist();
            largest_x = x;
        }
    }
    int pos = idx(largest_x, height_ - 1); // destination position
    while (pos != 0) {
        int x = pos % width_;
        int y = pos / width_;
        for (int dir = 0; dir < 4; dir++) {
            int next;
            int currDist = squares_[pos].getDist();
            if (dir == 0) next = idx(x+1, y); // right
            if (dir == 1) next = idx(x, y+1); // down
            if (dir == 2) next = idx(x-1, y); // left
            if (dir == 3) next = idx(x, y-1); // up
            if (canTravel(x, y, dir) && squares_[next].getDist() == (currDist - 1)) {
                sol.push_back(dir);
                pos = next;
                break;
            }
        }
    }
    // reverse direction & order of sol
    std::reverse(sol.begin(), sol.end());
    for (unsigned i = 0; i < sol.size(); i++) {
        sol[i] += 2;
        sol[i] %= 4;
    }

    return sol;
}

/* Return a PNG* object specified by makeMaze(). */
PNG* SquareMaze::drawMaze() const {
    PNG* canvas = new PNG(width_*10 + 1, height_*10 + 1);
    // blacken the topmost row
    for (unsigned x = 0; x < canvas->width(); x++) {
        if (x > 9 || x < 1) {
            HSLAPixel & p = canvas->getPixel(x, 0);
            p.l = 0;
        }
    }
    // blacken the leftmost column
    for (unsigned y = 0; y < canvas->height(); y++) {
        HSLAPixel & p = canvas->getPixel(0, y);
        p.l = 0;
    }
    for (int x = 0; x < this->width_; x++) {
        for (int y = 0; y < this->height_; y++) {
            // paint right wall if it exists
            if (this->squares_[idx(x, y)].get(0) == true) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & p = canvas->getPixel((x+1)*10, y*10+k);
                    p.l = 0;
                }
            }
            // paint down wall if it exists
            if (this->squares_[idx(x, y)].get(1) == true) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel & p = canvas->getPixel(x*10+k, (y+1)*10);
                    p.l = 0;
                }
            }
        }
    }
    return canvas;
}

/* Call drawMaze(), call solveMaze() then return the solved maze PNG* object. */
PNG* SquareMaze::drawMazeWithSolution() {
    PNG* canvas = drawMaze();
    vector<int> sol = solveMaze();
    int x = 5, y = 5;
    // paint the path in red
    for (int dir : sol) {
        int start_x = x;
        int start_y = y;
        if (dir == 0) x += 10;
        if (dir == 1) y += 10;
        if (dir == 2) x -= 10;
        if (dir == 3) y -= 10;
        if (x >= start_x) {
            for (int i = start_x; i <= x; i++) {
                if (y >= start_y) {
                    for (int j = start_y; j <= y; j++) {
                        HSLAPixel & p = canvas->getPixel(i, j);
                        p.h = 0;
                        p.s = 1;
                        p.l = 0.5;
                        p.a = 1;
                    }
                } else {
                    for (int j = start_y; j >= y; j--) {
                        HSLAPixel & p = canvas->getPixel(i, j);
                        p.h = 0;
                        p.s = 1;
                        p.l = 0.5;
                        p.a = 1;
                    }
                }
            }
        } else {
            for (int i = start_x; i >= x; i--) {
                if (y >= start_y) {
                    for (int j = start_y; j <= y; j++) {
                        HSLAPixel & p = canvas->getPixel(i, j);
                        p.h = 0;
                        p.s = 1;
                        p.l = 0.5;
                        p.a = 1;
                    }
                } else {
                    for (int j = start_y; j >= y; j--) {
                        HSLAPixel & p = canvas->getPixel(i, j);
                        p.h = 0;
                        p.s = 1;
                        p.l = 0.5;
                        p.a = 1;
                    }
                }
            }
        }
    }
    // whiten the exit
    for (int i = x-4; i < x+5; i++) {
        HSLAPixel & p = canvas->getPixel(i, y+5);
        p.l = 1;
    }
    return canvas;
}

/* Given a (x, y) coordinate, return the index in the 1-d array. */
int SquareMaze::idx(int x, int y) const {
    if (width_ == 0 && height_ == 0) {
        std::cout << "makeMaze() has not been called!" << std::endl;
        return -1;
    }
    if (x >= width_ || y >= height_ || x < 0 || y < 0) {
        return -1;
    }
    return y*width_ + x;
}
