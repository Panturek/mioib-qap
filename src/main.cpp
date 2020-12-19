#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include "procedure.hpp"


int main()
{
	srand(time(NULL));
	
	//std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "bur26a.dat", "esc32e.dat", "lipa50a.dat", "sko100a.dat" };

	std::vector<std::string> files_names = { "chr12a.dat" };

	//std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "esc32e.dat", "bur26a.dat", "lipa50a.dat"};

	std::vector<Algorithm> algos = { randomSearch };

	// Create directory in results/
	Procedure proc(algos, files_names, "experiment1");
	proc.run();
	
	std::cout << "\n>> Finished all experiments" << std::endl;
	getchar();
	return 0;
}
