
#ifndef PATH_H
#define PATH_H

using namespace std;

#include <vector>
#include "Link.h"
#include "Path.h"

class Path {

public:
	Path(vector<Link*> links);
	double getUserCost();
	void addLink(Link* link);
	void calculateFlow();
	void print();
	double getMarginalUserCost();
	void changeFlow(double delta);
	bool checkLink(Link* link);

	// store pointers to links, reference original links in the graph
	vector<Link*> links;

	int orig;
	int dest;
	double flow;

};

#endif