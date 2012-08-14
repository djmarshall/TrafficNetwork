
// TrafficNetwork.cpp : main project file.

#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "network.h"
#include "DemandSet.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace System;
using namespace std;

bool read_network_file(string filename, Network* file_net, DemandSet* file_demand) {
	
	bool file_ok = true;

	string line;
	fstream network_file(filename);

	// Build network from file
	if (network_file.is_open()) {

		// get number of nodes
		getline(network_file,line);

		// Count number of cells on the line
		int cell_count = count(line.begin(), line.end(), ',');

		if (cell_count == 0) {
			// no cells
			int value = atoi(line.c_str());

			file_net->reset(value);

			while(getline(network_file,line)) {
			
				// Count number of cells on the line
				int cell_count = count(line.begin(), line.end(), ',');

				stringstream lineStream(line);
				string cell;

				if (cell_count == 0) {
					// skip line with no commas
				} else {
					if (cell_count == 5) {
						// link definition line
			
						// read in each field and create the link
						getline(lineStream,cell,',');
						int orig = atoi(cell.c_str());
						getline(lineStream,cell,',');
						int dest = atoi(cell.c_str());
						getline(lineStream,cell,',');
						double flow = atof(cell.c_str());
						getline(lineStream,cell,',');
						double cost_a = atof(cell.c_str());
						getline(lineStream,cell,',');
						double cost_b = atof(cell.c_str());
						getline(lineStream,cell,',');
			
						file_net->addLink(orig, dest, flow, cost_a, cost_b, cell);
					
					} else {
						if (cell_count == 2) {
							// OD demand line

							getline(lineStream,cell,',');
							int orig = atoi(cell.c_str());
							getline(lineStream,cell,',');
							int dest = atoi(cell.c_str());
							getline(lineStream,cell,',');
							double demand = atof(cell.c_str());

							file_demand->addOD(orig, dest, demand);

						} else {
							cout << "Malformed input line: " << line;
						}
					}
				}
			
			}

		} else {

			file_ok = false;
			cout << "First line should be the number of nodes only";
		}

		network_file.close();
	
	} else {
		
		file_ok = false;
		cout << "Unable to open file " << filename << endl;
	}

	return file_ok;
}

int main(int argc, char** argv) {

	Network file_net;
	DemandSet file_demand(&file_net);

	// set default in case no command line argument
	string filename = "network.txt";
	if (argc > 1) {
		filename = argv[1];
	}

	bool ok = read_network_file(filename, &file_net, &file_demand);

	if (ok) {

		// run some algorithms!

		file_net.print();
		file_demand.print();

		file_demand.GEA_UO();
		file_net.print();
		file_demand.print();

		file_demand.GEA_SO();
		file_net.print();
		file_demand.print();

	}

	// Wait until ENTER is pressed
	cout << "\nPress ENTER to continue...";
	cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    return 0;
}
