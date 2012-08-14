
#ifndef OD_H
#define OD_H

#include "Path.h"
#include "Link.h"
#include "network.h"

class OD {

public:

	OD(int orig, int dest, double demand, Network* net);

	int orig;
	int dest;
	double demand;
	vector<Path> paths;
	Network* net;
	bool atEquilibrium(double epsilon);
	bool atMarginalEquilibrium(double epsilon);
	void print();
	void sortPaths();
	void sortMarginalPaths();
	bool isValid();

private:
	void buildPaths();
	void getNextLink(vector<Link*> partialPath, vector<int> visited);


};

#endif