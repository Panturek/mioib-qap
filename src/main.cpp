#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include "procedure.hpp"


int main()
{
	srand(time(NULL));
	

	std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "bur26a.dat", "esc32e.dat", "nug22.dat",  "tai30b.dat", "tai40b.dat", "tai64c.dat", "wil100.dat" };

	//std::vector<std::string> files_names = { "chr12a.dat" };

	std::vector<Algorithm> algos = { tabu };

	// Create directory in results/
	Procedure proc(algos, files_names, "experiment2");
	proc.run();
	

	/*
	QAP qap;
	qap.readData("data/bur26a.dat");
	int dim = qap.facilities.size();
	double sa_init = qap.findTemp();

	Permutation ending_perm;
	int init_cost;
	int instance_steps;

	std::tie(ending_perm, init_cost, instance_steps) = qap.tabu(dim);

	std::cout << qap.getCost(ending_perm) << " || " << init_cost << " || " << instance_steps << std::endl;
	*/

	std::cout << "\n>> Finished all experiments" << std::endl;
	getchar();
	return 0;
}
