# Mosaics

## Introduction

This program generates a mosaic picture that looks like the input picture, using other pictures as its pixels.

A KD-Tree is used to search for the nearest neighbor in color of a picture, reducing the time complexity from O(n) to O(lg(n)).

## Instructions

The input picture should be named **in.png** and put into the current directory.

All pixel pictures should be placed into the folder **png_lib**, and the format should be *.png*. It is suggested that at least 30 pictures with different colors are used.

This program uses GNU Make for compiling. To compile, type in terminal:

`make`

To run, type in terminal:

`./mosaics`

The output image will be saved into the current directory.
