#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include "qap.hpp"




enum Algorithm
{
	randomSearch, randomWalk, localSteepest, localGreedy, heuristics
};

void time_experiment(const std::string filename, QAP &qap, Algorithm algo)
{
	qap.readData("data/"+filename);
	int dim = qap.facilities.size();

	std::pair<Permutation, int> solution;
	std::vector<double> times;
	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	std::string algo_name;

	int l = 0;
	clock_t begin = clock();
	do
	{
		clock_t algo_time = clock();
		if (algo == localSteepest)
		{
			solution = qap.localSteepest(dim);
			algo_name = "steepest";
		}
		else if (algo == localGreedy)
		{
			solution = qap.localGreedy(dim);
			algo_name = "greedy";
		}
		l++;
		steps.push_back(solution.second);
		costs.push_back(qap.getCost(solution.first));
		perms.push_back(solution.first);
		times.push_back(double(clock() - algo_time) / CLOCKS_PER_SEC);
	} while (double(clock() - begin) / CLOCKS_PER_SEC < 120);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	printToFile("results/"+algo_name+"_"+filename, times, func_time, costs, steps, perms);
}

void random_experiment(const std::string filename, QAP &qap, Algorithm algo)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	std::pair<Permutation, int> solution;
	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	std::string algo_name;

	for (int i = 0; i < 200; i++)
	{
		if (algo == randomSearch)
		{
			solution = qap.randomSearch(dim, 0.1);
			algo_name = "r";
		}
		else if (algo == randomWalk)
		{
			solution = qap.randomWalk(dim, 0.1);
			algo_name = "rw";
		}
		steps.push_back(solution.second);
		costs.push_back(qap.getCost(solution.first));
		perms.push_back(solution.first);

	}
	randomPrintToFile("results/random/" +algo_name+"_"+ filename, costs, steps, perms);
}

void heuristics_experiment(const std::string filename, QAP &qap)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	std::pair<Permutation, int> solution;

	clock_t begin = clock();

	solution = qap.heuristics(dim);

	double func_time = double(clock() - begin) / CLOCKS_PER_SEC;

	heuristicsPrintToFile("results/heur/" + filename, func_time, solution.second, solution.first);
}


int main()
{
	srand(time(NULL));

	//std::vector<std::string> files_names = {"chr12a.dat", "chr18a.dat", "bur26a.dat", "esc32e.dat", "lipa50a.dat", "sko100a.dat" };

	std::vector<std::string> files_names = { "esc32e.dat" };

	std::vector<Algorithm> algos = { localGreedy, localSteepest, randomSearch, randomWalk, heuristics };

	for (auto&& algo : algos)
	{
		
		if (algo == localGreedy || algo == localSteepest)
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				time_experiment(filename, qap, algo);


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
				random_experiment(filename, qap, algo);


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
				heuristics_experiment(filename, qap );
				std::cout << ">> Finished Heuristics on " << filename << std::endl;
			}
		}
	}



	std::cout << ">> Finished all experiments" << std::endl;
	getchar();
	return 0;
}
