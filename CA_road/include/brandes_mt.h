#pragma once

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#include <algorithm>
#include <set>
#include <stack>
#include <thread>
#include <mutex>
#include <vector>
#include "graph.h"

using std::vector;

#ifndef INF
const double INF = 99999999;
#endif

vector<double> brandes_mt(const Graph & g, unsigned int num_of_threads = 6);
void brandes_single_thread(const Graph & g, vector<double> & BC, int start, int end, int size);

inline void printProgress1(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
