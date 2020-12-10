#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include "experiments.hpp"


int main()
{
	srand(time(NULL));

	//std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "bur26a.dat", "esc32e.dat", "lipa50a.dat", "sko100a.dat" };

	std::vector<std::string> files_names = { "chr12a.dat" };

	//std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "esc32e.dat", "bur26a.dat", "lipa50a.dat"};

	std::vector<Algorithm> algos = { randomSearch };

	for (auto&& algo : algos)
	{
		
		if (algo == localGreedy || algo == localSteepest)
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				time_experiment(filename, qap, algo, "results");


				if (algo == localGreedy)
				{
					std::cout << ">> Finished Greedy on " << filename << std::endl;
				}
				else
				{
					std::cout << ">> Finished Steepest on " << filename << std::endl;
				}
			}
		}
		
		else if (algo == randomSearch || algo == randomWalk)
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				random_experiment(filename, qap, algo, "results");


				if (algo == randomSearch)
				{
					std::cout << ">> Finished Random on " << filename << std::endl;
				}
				else
				{
					std::cout << ">> Finished RandomWalk on " << filename << std::endl;
				}
			}
		}

		else
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				heuristics_experiment(filename, qap, "results");
				std::cout << ">> Finished Heuristics on " << filename << std::endl;
			}
		}
	}



	std::cout << ">> Finished all experiments" << std::endl;
	getchar();
	return 0;
}
