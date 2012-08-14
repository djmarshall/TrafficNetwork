====================================
    APPLICATION : TrafficNetwork
====================================

An implementation of a basic traffic network (nodes, links, flows) with linear user link cost functions. The program will load a network from a file and then perform
a General Equilibrium Algorithm to first optimise user cost (UO) and then to optimise marginal user cost (SO).

The project runs on the console and is written in C++ using Visual Studio 2010. However, the code requires no special tricks, and should compile with any major C++ compiler.

USAGE: The exe file and two txt's files are in the release/ directory.
The program takes one optional command line argument which is the text file that the network is stored in.
If no filename is given, the program will default to loading the "network.txt" file.

The network file has the following format:

<line> number of nodes
<many lines A> origin, destination, starting flow, g, h, name
<many lines B> origin, destination, demand

where A are the links and B are the OD pairs.
The origin and destination are node ids between 0..number of nodes.
g and h are the terms in the linear user cost function g*flow + h.
name can be any string (no quotes!).
starting flow and demand are any number.