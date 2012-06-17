Data Skeleton Code
==================

Root folder 
-----------
* GenGraph.m       Generate distance graph from point coordinate  
`function W = GenGraph(points)`

* GridSample.m     Sample points from grid  
`function points = GridSample(binImage, interval)`

* PruneGraph.m     Use threshold to prune graph  
`function G = PruneGraph(W, r)`

* RandSample.m     Sample points from normal distribution  
`function points = RandSample(binImage, num)`

* RunTest.m        Test script

Mex folder
----------
* Floyd.m          Floyd algorithm implemented with MATLAB  
`function [G, next] = Floyd(G1)`

* MexAll.m         Build script

* TestFloyd.m      Verification code for floyd algorithm

* simpleMatrix.h   
* matrixio.h       Inline function for matrix input, output operation
* dlmio.cc         Act like `dlmread` function in MATLAB
* dlmio.h          
* floyd.cc         Floyd algorithm
* floyd.h
* mexFloyd.cc      Mex interface for floyd algorithm

Func folder
-----------
Data skeleton algorithm here