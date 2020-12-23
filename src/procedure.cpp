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

		if (algo == localGreedy || algo == localSteepest || algo == simmulatedAnnealing || algo == tabu)
		{
			for (auto&& filename : files_names)
			{
				QAP qap;
				time_experiment(filename, qap, algo, "results/"+dirout);


				if (algo == localGreedy)
				{
					std::cout << ">> Finished Greedy on " << filename << std::endl;
				}
				else if (algo == localSteepest)
				{
					std::cout << ">> Finished Steepest on " << filename << std::endl;
				}
				else if(algo == simmulatedAnnealing)
				{
					std::cout << ">> Finished SA on " << filename << std::endl;
				}
				else if (algo == tabu)
				{
					std::cout << ">> Finished Tabu on " << filename << std::endl;
				}
			}
		}

		else if (algo == randomSearch || algo == randomWalk)
		{
			for (auto&& filename : files_names)
			{
				double algotime = 2;

				if (filename == "chr12a.dat") {
					algotime = 0.057;
				}
				else if (filename == "chr18a.dat") {
					algotime = 0.27;
				}
				else if (filename == "bur26a.dat") {
					algotime = 1.87;
				}
				else if (filename == "esc32e.dat") {
					algotime = 0.31;
				}
				else if (filename == "nug22.dat") {
					algotime = 1;
				}
				else if (filename == "tai30b.dat") {
					algotime = 5.11;
				}
				else if (filename == "tai40b.dat") {
					algotime = 28.4;
				}
				else if (filename == "tai64c.dat") {
					algotime = 7.54;
				}
				else {
					algotime = 60;
				}

				QAP qap;
				random_experiment(filename, qap, algo, "results/"+dirout, algotime);


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