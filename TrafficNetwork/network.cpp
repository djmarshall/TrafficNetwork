
using namespace std;

#include "Network.h"
#include "Link.h"
#include <algorithm>
#include <iostream>

Network::Network(int numNodes) {

	graph.clear();

	// Initialise a vector for each node.
	for(int i = 0; i < numNodes; i++) {
		graph.push_back(vector<Link>());
	}

	this->numNodes = numNodes;
}

void Network::reset(int numNodes) {

	// Initialise a vector for each node.
	for(int i = 0; i < numNodes; i++) {
		graph.push_back(vector<Link>());
	}

	this->numNodes = numNodes;
}


Network::Network() {

	graph.push_back(vector<Link>());
	this->numNodes = 1;
}

void Network::addLink(int orig, int dest, double flow, double cost_a, double cost_b, string name) {
	
	if ((orig < numNodes) && (dest < numNodes)) {
		graph[orig].push_back(Link(dest, flow, cost_a, cost_b, name));
	} else {
		cout << "Origin or destination node doesn't exist\n";
	}
}

double Network::getTotalCost() {

	double total_cost = 0;

	for(int i = 0; i < graph.size(); i++) {
		for(int j = 0; j < graph[i].size(); j++) {
			total_cost = total_cost + graph[i][j].getUserCost() * graph[i][j].flow;
		}
	}

	return total_cost;
}

void Network::print() {

	cout << ("\nNetwork (flow, cost, marginal cost)\n");
	for(int i = 0; i < graph.size(); i++) {
		for(int j = 0; j < graph[i].size(); j++) {
			cout << i << " " << graph[i][j].name.c_str() << "(" << graph[i][j].flow << " " << graph[i][j].getUserCost() << " " << graph[i][j].getMarginalUserCost() << ")" << " " << graph[i][j].dest << endl;
		}
	}

	cout << "Total network cost is " << getTotalCost() << endl << endl;
}