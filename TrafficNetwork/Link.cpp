
#include "Link.h"

Link::Link(int dest, double flow, double cost_a, double cost_b, string name) {

	this->dest = dest;
	this->flow = flow;
	this->cost_a = cost_a;
	this->cost_b = cost_b;
	this->name = name;
}

double Link::getUserCost() {
		
	return cost_a * flow + cost_b;

}

double Link::getMarginalUserCost() {
		
	return (2 * cost_a * flow) + cost_b;

}