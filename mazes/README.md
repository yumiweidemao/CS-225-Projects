# Mazes

## Introduction

This program generates a random maze as well as a solution to it. The start point is always on the top-left corner of the maze. The end point is chosen on the bottom border such that the correct path is the longest possible. 

Cycle detection in maze generation is implemented with a disjoint set. Maze solving utilizes BFS algorithm.

## Instructions

Make sure you have GNU Make installed in your system.

To compile, navigate into the current folder, and type in terminal:

`make`

To run, type in terminal:

`./mazes [width] [height]`

The width & height arguments are not necessary, they are defaulted to 50. The generated mazes will be in the folder *generated_mazes*.
