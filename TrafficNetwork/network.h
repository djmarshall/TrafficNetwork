
#ifndef NETWORK_H
#define NETWORK_H

using namespace std;

#include <vector>
#include "Link.h"

class Network {

public:
	Network();
	Network(int numNodes);
	void reset(int numNodes);
	void addLink(int orig, int dest, double flow, double cost_a, double cost_b, string name);
	void print();
	

	double getTotalCost();

	// Store graph as an adjaceny list for fast edge traversal for each node
	vector<vector<Link>> graph;
	int numNodes;

};

#endif