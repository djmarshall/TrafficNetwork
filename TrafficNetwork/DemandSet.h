
#ifndef DEMANDSET_H
#define DEMANDSET_H

#include "network.h"
#include "Path.h"
#include "OD.h"

class DemandSet {

public:
	DemandSet(Network* net);
	void addOD(int orig, int dest, double demand);

	// Pass the network as a pointer, as in practice the data structure may be large and we don't want to make a new copy.
	Network* net;
	void print();
	void GEA_UO();
	void GEA_SO();
	void setFeasibleFlow();

	int orig;
	int dest;
	double demand;
	vector<OD> ODPairs;

};

#endif