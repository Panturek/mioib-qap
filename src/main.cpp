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
		times.push_back(double(clock() - begin) / CLOCKS_PER_SEC);
	} while (double(clock() - begin) / CLOCKS_PER_SEC < 10);

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

	if (algo == randomSearch)
	{
		solution = qap.randomSearch(dim, 1);
	}
	else if (algo == randomWalk)
	{
		solution = qap.randomWalk(dim, 1);
	}

	printToFile("results/random/" + filename, func_time, costs, steps, perms);
}

/*
void heuristics_experiment(const std::string filename, QAP &qap)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	clock_t begin = clock();

	qap.heuristics(dim);

	double func_time = double(clock() - begin) / CLOCKS_PER_SEC;

}
*/

int main()
{
	srand(time(NULL));

	std::vector<std::string> files_names = { "bur26a.dat", "esc16i.dat" };

	std::vector<Algorithm> algos = { localGreedy, localSteepest };

	for (auto&& algo : algos)
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



	std::cout << ">> Finished all experiments" << std::endl;
	getchar();
	return 0;
}
