#include "experiments.hpp"

void time_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	double sa_init = qap.findTemp();

	Permutation ending_perm;
	int init_cost;
	int instance_steps;

	std::vector<double> times;
	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	std::vector<int> starting_costs;
	std::string algo_name;

	// EXPERIMENT
	int limit = 600;

	int l = 0;
	clock_t begin = clock();
	do
	{
		if (l > 300) {
			break;
		}

		clock_t algo_time = clock();
		if (algo == localSteepest)
		{
			std::tie(ending_perm, init_cost, instance_steps) = qap.localSteepest(dim);
			algo_name = "steepest";
		}
		else if (algo == localGreedy)
		{
			std::tie(ending_perm, init_cost, instance_steps) = qap.localGreedy(dim);
			algo_name = "greedy";
		}
		else if (algo == simmulatedAnnealing)
		{
			std::tie(ending_perm, init_cost, instance_steps) = qap.simmulatedAnnealing(dim, sa_init);
			algo_name = "sa";
		}
		else if (algo == tabu)
		{
			std::tie(ending_perm, init_cost, instance_steps) = qap.tabu(dim);
			algo_name = "tabu";
		}

		l++;
		steps.push_back(instance_steps);
		costs.push_back(qap.getCost(ending_perm));
		perms.push_back(ending_perm);
		starting_costs.push_back(init_cost);
		times.push_back(double(clock() - algo_time) / CLOCKS_PER_SEC);
	} while (double(clock() - begin) / CLOCKS_PER_SEC < limit);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	printToFile(dirout + "/" + algo_name + "_" + filename, times, func_time, costs, steps, starting_costs, perms);
}

void random_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout, const double algotime)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	Permutation ending_perm;
	int instance_steps;

	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	std::string algo_name;


	int limit = 300;
	int l = 0;
	clock_t begin = clock();
	do
	{
		if (l > 300) {
			break;
		}

		clock_t algo_time = clock();
		if (algo == randomSearch)
		{
			std::tie(ending_perm, instance_steps) = qap.randomSearch(dim, algotime);
			algo_name = "r";
		}
		else if (algo == randomWalk)
		{
			std::tie(ending_perm, instance_steps) = qap.randomWalk(dim, algotime);
			algo_name = "rw";
		}
		l++;
		steps.push_back(instance_steps);
		costs.push_back(qap.getCost(ending_perm));
		perms.push_back(ending_perm);

	} while (double(clock() - begin) / CLOCKS_PER_SEC < limit);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	randomPrintToFile(dirout + "/" + algo_name + "_" + filename, costs, steps, func_time, perms);
}

void heuristics_experiment(const std::string filename, QAP &qap, const std::string dirout)
{
	qap.readData("data/" + filename);
	int dim = qap.facilities.size();

	Permutation solution;

	clock_t begin = clock();

	solution = qap.heuristics(dim);

	double func_time = double(clock() - begin) / CLOCKS_PER_SEC;

	heuristicsPrintToFile(dirout + "/" + "heur_" + filename, func_time, qap.getCost(solution), solution);
}