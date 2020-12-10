#include "procedure.hpp"

Procedure::Procedure(const std::vector<Algorithm> algs, const std::vector<std::string> fnames, const std::string out)
{
	algos = algs;
	files_names = fnames;
	dirout = out;
}

void Procedure::run()
{
	for (auto&& algo : algos)
	{

		if (algo == localGreedy || algo == localSteepest)
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				time_experiment(filename, qap, algo, "results/"+dirout);


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
				random_experiment(filename, qap, algo, "results/"+dirout);


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
				heuristics_experiment(filename, qap, "results/"+dirout);
				std::cout << ">> Finished Heuristics on " << filename << std::endl;
			}
		}
	}

}