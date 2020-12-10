#include "experiments.hpp"

class Procedure {
	std::vector<Algorithm> algos;
	std::vector<std::string> files_names;
	std::string dirout;

public:
	Procedure(const std::vector<Algorithm> algs, const std::vector<std::string> fnames, const std::string out);
	void run();
};