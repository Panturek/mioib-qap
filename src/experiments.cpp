#include "experiments.hpp"

void time_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	std::pair<Permutation, int> solution;
	std::vector<double> times;
	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	std::string algo_name;

	// EXPERIMENT
	int limit = 60;

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
	} while (double(clock() - begin) / CLOCKS_PER_SEC < limit);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	printToFile(dirout + "/" + algo_name + "_" + filename, times, func_time, costs, steps, perms);
}

void random_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout)
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
	randomPrintToFile(dirout + "/" + algo_name + "_" + filename, costs, steps, perms);
}

void heuristics_experiment(const std::string filename, QAP &qap, const std::string dirout)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	std::pair<Permutation, int> solution;

	clock_t begin = clock();

	solution = qap.heuristics(dim);

	double func_time = double(clock() - begin) / CLOCKS_PER_SEC;

	heuristicsPrintToFile(dirout + "/" + filename, func_time, solution.second, solution.first);
}