
using namespace std;

#include"DemandSet.h"
#include <vector>
#include "Path.h"
#include <algorithm>
#include <iostream>

// tolerance for all calculations in the algorithms
double flow_epsilon = 0.000000001;

void DemandSet::setFeasibleFlow() {

	// clear all flows
	for(int k = 0; k < ODPairs.size(); k++) {
		for(int i = 0; i < ODPairs[k].paths.size(); i++) {
			ODPairs[k].paths[i].flow = 0;
			for(int j = 0; j < ODPairs[k].paths[i].links.size(); j++) {
				ODPairs[k].paths[i].links[j]->flow = 0;
			}
		}
	}

	// basic feasible flow, all flow down the first path of each pair
	for(int k = 0; k < ODPairs.size(); k++) {
		
		// set first path flow
		ODPairs[k].paths[0].flow = ODPairs[k].demand;
		
		// set link flows for the first path
		for(int i = 0; i < ODPairs[k].paths[0].links.size(); i++) {
			ODPairs[k].paths[0].links[i]->flow = ODPairs[k].paths[0].links[i]->flow + ODPairs[k].demand;
		}
	}
}

DemandSet::DemandSet(Network* net) {
	this->net = net;
}

void DemandSet::addOD(int orig, int dest, double demand) {

	this->orig = orig;
	this->dest = dest;
	this->demand = demand;

	ODPairs.push_back(OD(orig, dest, demand, net));

}

void DemandSet::print() {
	
	cout << "Demand Set (orig, dest, demand) then (path, flow, cost, marginal cost)\n";

	// loop through ODs

	for(int i = 0; i < ODPairs.size(); i++) {
		ODPairs[i].print();
		cout << endl;
	}
}

void DemandSet::GEA_UO() {
	
	cout << "U-O Optimisation...\n";

	// remove any non valid ODs before continuing
	for(int k = 0; k < ODPairs.size(); k++ ) {
		if (!ODPairs[k].isValid()) {
			ODPairs.erase(ODPairs.begin()+(k-1));
			k--;
		}
	}

	// Algorithm assumes initial flows are feasible
	setFeasibleFlow();

	bool ods_finished = false;

	while(!ods_finished) {

		// optimise each OD pair in turn
		for(int k = 0; k < ODPairs.size(); k++ ) {

			vector<Path>* paths = &(ODPairs[k].paths);

			bool paths_finished = false;

			// adjust flows in paths until equilibrium is reached
			while(!paths_finished) {
				
				ODPairs[k].sortPaths();

				// set q to path with lowest cost
				Path *q = &(paths->front());
				
				// set r to path with highest cost and positive flow
				int non_zero_index = paths->size() - 1;

				while(abs(paths->at(non_zero_index).flow) < flow_epsilon) {
					non_zero_index--;
				}

				Path *r = &(paths->at(non_zero_index));

				// calculate iterative flow change
				double link_sum = 0.0;

				for(int i = 0; i < q->links.size(); i++) {

					// remove common links from calculation
					if (!r->checkLink(q->links[i])) {
						link_sum = link_sum + q->links[i]->cost_a;
					}
				}
				for(int i = 0; i < r->links.size(); i++) {

					// remove common links from calculation
					if (!q->checkLink(r->links[i])) {
						link_sum = link_sum + r->links[i]->cost_a;
					}
				}

				double delta_prime = (r->getUserCost() - q->getUserCost()) / link_sum;

				double delta = min(delta_prime, r->flow);

				// adjust path flows
				q->changeFlow(delta);
				r->changeFlow(-1.0 * delta);

				// check if all paths for this OD are at equilibrium
				if (ODPairs[k].atEquilibrium(flow_epsilon)) {
					paths_finished = true;
				}

			}

		}

		// check all ods are satisfied
		ods_finished = true;

		for(int k = 0; k < ODPairs.size(); k++) {
			
			if (!ODPairs[k].atEquilibrium(flow_epsilon)) {
				ods_finished = false;
			}
		}

	}
	
}

void DemandSet::GEA_SO() {
	
	cout << "S-O Optimisation...\n";

	// remove any non valid ODs before continuing
	for(int k = 0; k < ODPairs.size(); k++ ) {
		if (!ODPairs[k].isValid()) {
			ODPairs.erase(ODPairs.begin()+(k-1));
			k--;
		}
	}

	// Algorithm assumes initial flows are feasible
	setFeasibleFlow();

	bool ods_finished = false;

	while(!ods_finished) {

		// optimise each OD pair in turn
		for(int k = 0; k < ODPairs.size(); k++ ) {
			
			vector<Path>* paths = &(ODPairs[k].paths);

			bool paths_finished = false;

			// adjust flows in paths until equilibrium is reached
			while(!paths_finished) {

				ODPairs[k].sortMarginalPaths();

				// set q to path with lowest marginal cost
				Path *q = &(paths->front());

				// set r to path with highest marginal cost and positive flow
				int non_zero_index = paths->size() - 1;

				while(abs(paths->at(non_zero_index).flow) < flow_epsilon) {
					non_zero_index--;
				}

				Path *r = &(paths->at(non_zero_index));

				// calculate iterative flow change
				double link_sum = 0.0;

				for(int i = 0; i < q->links.size(); i++) {

					// remove common links from calculation
					if (!r->checkLink(q->links[i])) {
						link_sum = link_sum + q->links[i]->cost_a;
					}
				}
				for(int i = 0; i < r->links.size(); i++) {

					// remove common links from calculation
					if (!q->checkLink(r->links[i])) {
						link_sum = link_sum + r->links[i]->cost_a;
					}
				}

				double delta_prime = (r->getMarginalUserCost() - q->getMarginalUserCost()) / (2 * link_sum);

				double delta = min(delta_prime, r->flow);

				// adjust path flows
				q->changeFlow(delta);
				r->changeFlow(-1.0 * delta);

				// check if all paths for this OD are at equilibrium
				if (ODPairs[k].atMarginalEquilibrium(flow_epsilon)) {
					paths_finished = true;
				}
			}
		
		}

		// check all ods are satisfied
		ods_finished = true;

		for(int k = 0; k < ODPairs.size(); k++) {
			
			if (!ODPairs[k].atMarginalEquilibrium(flow_epsilon)) {
				ods_finished = false;
			}
		}

	}
}