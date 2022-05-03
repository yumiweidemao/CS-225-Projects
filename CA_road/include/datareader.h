#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include "edge.h"
using namespace std;;

vector<Edge> readEdges(string filename, bool generate_log = false);
std::string pad(std::string str, const char paddingChar = '0');
void writeVertices(string filename, vector<int> path, vector<double> weightVector);
vector<vector<double> > readVertices(string filename);
