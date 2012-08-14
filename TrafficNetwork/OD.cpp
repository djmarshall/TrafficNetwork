
#include "OD.h"
#include <algorithm>
#include <iostream>

void OD::getNextLink(vector<Link*> partialPath, vector<int> visited) {

	int linkDest = partialPath.back()->dest;

	if (linkDest == dest) {
		// Path complete
		Path nextPath = partialPath;
		paths.push_back(nextPath);

		paths.back().calculateFlow(); // Assume link flows are feasible

	} else {

		// Keep looking from new node
		
		for(int i = 0; i < net->graph[linkDest].size(); i++) {

			Link* currentLink = &(net->graph[linkDest][i]);

			// If we haven't been to the destination node before, add this link to the partial path
			// This ensures no loops/cycles

			if (!visited[linkDest]) {
				partialPath.push_back(currentLink);
				visited[linkDest] = 1;
		
				getNextLink(partialPath, visited);

				visited[linkDest] = 0;
				partialPath.pop_back();
			}
		}

	}
}

void OD::buildPaths() {
	
	vector<Link*> partialPath = vector<Link*>();
	vector<int> visited = vector<int>(net->numNodes);

	// for each possible start node
	for(int i = 0; i < net->graph[orig].size(); i++) {

		Link* currentLink = &(net->graph[orig].at(i));
		partialPath.push_back(currentLink);
		visited[orig] = 1;
		
		getNextLink(partialPath, visited);

		visited[orig] = 0;
		partialPath.pop_back();
		
	}

}

bool path_less(Path a, Path b) {
	if (a.getUserCost() < b.getUserCost()) {
		return true;
	} else {
		return false;
	}
}

void OD::sortPaths() {

	// Sort the paths into ascending order based on user cost
	sort(paths.begin(), paths.end(), path_less);
}

bool path_marginal_less(Path a, Path b) {
	if (a.getMarginalUserCost() < b.getMarginalUserCost()) {
		return true;
	} else {
		return false;
	}
}

void OD::sortMarginalPaths() {

	// Sort the paths into ascending order based on marginal user cost
	sort(paths.begin(), paths.end(), path_marginal_less);
}


bool OD::atEquilibrium(double epsilon) {

	// all smallest costs equal and every zero flow path with a higher cost

	sortPaths();

	bool paths_finished = true;

	double current_cost = paths.front().getUserCost();

	for(int i = 1; i < paths.size(); i++) {

		if ((abs(paths.at(i).flow) > epsilon) && (abs(paths.at(i).getUserCost() - current_cost)) > epsilon) {
			paths_finished = false;
		}
	}

	return paths_finished;
}

bool OD::atMarginalEquilibrium(double epsilon) {

	// all smallest marginal costs equal and every zero flow path with a higher marginal cost

	sortMarginalPaths();

	bool paths_finished = true;

	double current_cost = paths.front().getMarginalUserCost();

	for(int i = 1; i < paths.size(); i++) {

		if ((abs(paths.at(i).flow) > epsilon) && (abs(paths.at(i).getMarginalUserCost() - current_cost)) > epsilon) {
			paths_finished = false;
		}
	}

	return paths_finished;
}

OD::OD(int orig, int dest, double demand, Network* net) {

	this->orig = orig;
	this->dest = dest;
	this->demand = demand;
	this->net = net;

	buildPaths();

	if (paths.size() == 0) {
		cout << "No valid paths for " << orig << " to " << dest << endl;
		// this behaviour is captured upstream in demand set when checking if ODs are valid
		// there are better way to deals with this, btu this will suffice for now
	}


}

void OD::print() {

	cout << orig << " " << dest << " " << demand << endl;

	for(int i = 0; i < paths.size(); i++) {
		paths[i].print();
	}

}

bool OD::isValid() {
	
	bool valid = true;
	
	if (paths.size() == 0) {
		valid = false;
	}

	return valid;
}