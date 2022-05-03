#pragma once

#include "graph.h"
#include <iostream>
//drawing tools importing
#include "../drawing/PNG.h"
#include "../drawing/color.h"
#include "../drawing/shape.h"
#include "../drawing/vector2.h"
#include "../drawing/line.h"
#include "../drawing/circle.h"

using cs225::PNG;
using cs225::HSLAPixel;


void drawBC(const vector<vector<double> > &vertices, const vector<double> & BC, const Graph & g, size_t edge_num)
{
  int start = 0;
  queue<int> q;         // create a queue for BFS
  int size = g.getSize();

  const int WIDTH = 1800;
  const int HEIGHT = 2048;
  const char OUTPUT_FILE[] = "BC_graph.png";
  PNG canvas;
  canvas.resize(1820, 2060);

  vector<bool> visited_V(size, false);   // visited[v] records if v has been visited
  vector<int> explored_E(edge_num, 0);   //0: unlabeled, 1: discover, 2: cross
 
  q.push(start);
  visited_V[start] = true;

  while (!q.empty()) {
      // dequeue from queue
      int curr = q.front();
      q.pop();
      vector<Edge> incidEdges = g.incidentEdges(curr);
      vector<int> adjVer = g.adjacentVertices(curr);

      //draw the dot itself:
      int radius_A;
      if(BC[curr] < 0.3){
        radius_A = 1;
      }else if(BC[curr] < 0.6){
        radius_A = 2;
      }else{
        radius_A = 3;
      }
      HSLAPixel currColor(240-240*BC[curr], 1, 0.5, 0.4 + 0.6 * BC[curr]);
      Vector2 currVer_Pos(vertices[0][curr] * WIDTH + 5, vertices[1][curr] * HEIGHT + 5);
      Circle currVer_Circle(currVer_Pos, currColor, radius_A);
      currVer_Circle.draw(&canvas); 
      //uncomment to print current ver
      //cout << "current ver loc:" << vertices[0][curr] * WIDTH <<", " << vertices[1][curr] * HEIGHT<< endl;
      
      for (size_t i = 0; i < incidEdges.size(); i++) {
          int currEdgeIdx = incidEdges[i].getIdx(); 
          int currAdjVerIdx = adjVer[i];         
          if (explored_E[currEdgeIdx]==0) {                          //for edge is not reached
            Vector2 visitingVer_Pos(vertices[0][currAdjVerIdx] * WIDTH + 5, vertices[1][currAdjVerIdx] * HEIGHT + 5);
            HSLAPixel visitingColor(240-240*BC[currAdjVerIdx], 1, 0.5,  0.4 + 0.6 * BC[currAdjVerIdx]);
            int radius_B;
            if(BC[currAdjVerIdx] < 0.3){
              radius_B = 1;
            }else if(BC[currAdjVerIdx] < 0.6){
              radius_B = 2;
            }else{
              radius_B = 3;
            }
            
            if (!visited_V[currAdjVerIdx]){
              explored_E[currEdgeIdx] = 1;
              visited_V[currAdjVerIdx] = true;
              q.push(currAdjVerIdx);
              //draw: unexplored node and edge
              
              Circle unvisitedVer_Circle(visitingVer_Pos, visitingColor, radius_B);
              unvisitedVer_Circle.draw(&canvas);  
              Line unexploredEdge(currVer_Pos, visitingVer_Pos, color::GRAY);
              unexploredEdge.draw(&canvas); 

            }else{
              explored_E[currEdgeIdx] = 2;
              //draw: a cross edge only
              Line exploredEdge(currVer_Pos, visitingVer_Pos, color::GRAY);
              exploredEdge.draw(&canvas); 
            }
          }
      }
  }
  
  canvas.writeToFile(OUTPUT_FILE);

  return;
}
