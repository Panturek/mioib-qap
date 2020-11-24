#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "qap.hpp"


void printToFile(const std::string filename,
	const int time,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const std::vector<Permutation> permutations)
{
	std::ofstream output;
	output.open(filename);
	for (int i = 0; i < costs.size(); i++)
	{
		output << costs[i] << ",\t"
			<< time << ",\t"
			<< steps[i] << ",\t";
		for (auto&& n : permutations[i]) {
			output << n << " ";
		}
		output << "\n";
	}
	output.close();
}


int main()
{
	srand(time(NULL));

	QAP qap;
	qap.readData("data/bur26a.dat");
	int dim = qap.facilities.size();
	std::cout << "Rozmiar: " << dim << std::endl;

	std::pair<Permutation, int> solution;

	clock_t begin = clock();
	std::vector<int> steps;
	std::vector<int> costs;
	std::vector<Permutation> perms;
	int l = 0;
	do
	{
		solution = qap.localSteepest(dim);
		l++;
		steps.push_back(solution.second);
		costs.push_back(qap.getCost(solution.first));
		perms.push_back(solution.first);
	} while (double(clock() - begin) / CLOCKS_PER_SEC < 600);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	printToFile("result.txt", func_time, costs, steps, perms);


	std::cout << "Performance: " << qap.getCost(solution.first) << std::endl;
	std::cout << "Average time: " << func_time << std::endl;
	std::cout << "l " << l << std::endl;

	std::cout << std::endl << "Heuristics" << std::endl;
	Permutation heur = qap.heuristics(dim);
	std::cout << "Performance: " << qap.getCost(heur) << std::endl;

	for (int el = 0; el < heur.size(); el++)
	{
		std::cout << heur[el] << " ";
	}

	getchar();
	return 0;
}
