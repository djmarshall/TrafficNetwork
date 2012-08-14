
#ifndef LINK_H
#define LINK_H

using namespace std;

#include <string>

class Link {

public:
	Link(int dest, double flow, double cost_a, double cost_b, string name);
	double getUserCost();
	double getMarginalUserCost();

	int dest;
	double flow;
	double cost_a;
	double cost_b;
	string name;

};


#endif 