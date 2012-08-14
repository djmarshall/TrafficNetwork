
using namespace std;

#include "Path.h"
#include "Link.h"
#include <vector>
#include <iostream>

Path::Path(vector<Link*> links) {
	this->links = links;
	this->flow = 0.0;
}

double Path::getUserCost() {

	double userCost = 0;

	for(int i = 0; i < links.size(); i++) {
		userCost = userCost + links[i]->getUserCost();
	}
		
	return userCost;

}

double Path::getMarginalUserCost() {

	double userCost = 0;

	for(int i = 0; i < links.size(); i++) {
		userCost = userCost + links[i]->getMarginalUserCost();
	}
		
	return userCost;

}

void Path::calculateFlow() {
	
	flow = 0;

	// Calculate path flow, which is the sum of the flows of the links
	for(int i = 0; i < links.size(); i++) {
		this->flow = this->flow + links[i]->flow;
	}
	
}

void Path::addLink(Link *link) {
	links.push_back(link);
}

void Path::changeFlow(double delta) {

	// adjust path flow
	flow = flow + delta;

	// change link flows along the path
	for(int i = 0; i < links.size(); i++) {
		links[i]->flow = links[i]->flow + delta;
	}

}

void Path::print() {

	for(int i = 0; i < links.size(); i++) {
		cout << links[i]->name.c_str() << " ";
	}
	cout << flow << " " <<  getUserCost() << " " << getMarginalUserCost() << endl;
}

bool Path::checkLink(Link* link) {

	// check if the link is part of this path

	bool link_here = false;

	for(int i = 0; i < links.size(); i++) {
		if (links[i] == link) {
			link_here = true;
		}
	}

	return link_here;
}